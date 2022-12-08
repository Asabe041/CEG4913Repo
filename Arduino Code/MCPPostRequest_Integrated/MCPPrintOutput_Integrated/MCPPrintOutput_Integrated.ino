#include <Adafruit_MCP3008.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h" // not necessary if using MotionApps include file

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

/////// Wifi Settings ///////
char ssid[] = "stingray";
char pass[] = "";

const char serverName[] = "192.168.1.117";  // server name
int port = 8081;

#define LED1 3  // The pin 1st LED is connected to
#define LED2 4  // The pin 2nd LED is connected to
#define LED3 5  // The pin 3rd LED is connected to
#define LED4 6  // The pin 4th LED is connected to
#define LED5 7  // The pin 5th LED is connected to

Adafruit_MCP3008 adc;
static int CURRENT_STATE = 0;

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;  
#define OUTPUT_READABLE_YAWPITCHROLL
#define OUTPUT_READABLE_REALACCEL
#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)

#define LED1 3  // The pin 1st LED is connected to
#define LED2 4  // The pin 2nd LED is connected to
#define LED3 5  // The pin 3rd LED is connected to
#define LED4 6  // The pin 4th LED is connected to
#define LED5 7  // The pin 5th LED is connected to

bool blinkState = false;

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };
float temperature;

enum LED_STATE{
  S0 = 0, //initial state
  S1 = 1,
  S2 = 2,
  S3 = 3,
  S4 = 4,
  S5 = 5
};

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverName, port);
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }
    // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // ---------------------------------------------------
  pinMode(LED1, OUTPUT); // Declare the LED as an output
  pinMode(LED2, OUTPUT); // Declare the LED as an output
  pinMode(LED3, OUTPUT); // Declare the LED as an output
  pinMode(LED4, OUTPUT); // Declare the LED as an output
  pinMode(LED5, OUTPUT); // Declare the LED as an output

  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
      // Calibration Time: generate offsets and calibrate our MPU6050
      mpu.CalibrateAccel(6);
      mpu.CalibrateGyro(6);
      mpu.PrintActiveOffsets();
      // turn on the DMP, now that it's ready
      Serial.println(F("Enabling DMP..."));
      mpu.setDMPEnabled(true);

      // enable Arduino interrupt detection
      Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
      Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
      Serial.println(F(")..."));
      attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();

      // set our DMP Ready flag so the main loop() function knows it's okay to use it
      Serial.println(F("DMP ready! Waiting for first interrupt..."));
      dmpReady = true;

      // get expected DMP packet size for later comparison
      packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      Serial.print(F("DMP Initialization failed (code "));
      Serial.print(devStatus);
      Serial.println(F(")"));
  }

  Serial.println("MCP3008 initialized.");
  adc.begin();
}

void loop() {
  //adc.readADC(0) reads from channel 0 of the mcp chip
  int raw = adc.readADC(1);
  
  Serial.print("Raw ADC value: ");
  Serial.print(raw); 
  Serial.print("\t");

  Serial.print("Voltage (V): ");
  Serial.print(voltage(raw));
  Serial.print("\t");

  Serial.print("Millivolts (mV): " );
  Serial.println(voltage(raw) * 1000);
  
  delay(1000);

  LED_STATE currState = classifySignal(voltage(raw)*1000);
  turnOnLED(currState);

  //MPU Code-------------------------------------
  // if programming failed, don't try to do anything
    if (!dmpReady) return;
    // read a packet from FIFO
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet 
        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("yaw ");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print(",\t");
            Serial.print("pitch ");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print(",\t");
            Serial.print("roll  ");
            Serial.println(ypr[2] * 180/M_PI);
        #endif

        #ifdef OUTPUT_READABLE_REALACCEL
            // display real acceleration, adjusted to remove gravity
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            Serial.print("Acceleration on x axis  ");
            Serial.print(aaReal.x/1000.00);
            Serial.print(",\t");
            Serial.print("Acceleration on y axis  ");
            Serial.print(aaReal.y/1000.00);
            Serial.print(",\t");
            Serial.print("Acceleration on z axis  ");
            Serial.println(aaReal.z/1000.00);
        #endif
        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
    temperature = convertTemperature(mpu.getTemperature());
    Serial.print("temperature\t");
    Serial.print(temperature);
    Serial.print("\n");
  //---------------------------------------------

  // -------------------------------- Send the available Data ----------------------------
  Serial.println("making POST request");

  String contentType = "application/json";
  String postDataMcp = "{\"led_state\":";
  int stateToSend = currState;
  postDataMcp += stateToSend;
  postDataMcp += ",";

  //add voltage
  postDataMcp += "\"raw_adc_data\":";
  postDataMcp += voltage(raw)*1000;
  postDataMcp += ",";
  postDataMcp += "\"password\":fvwaebyiuoafeiwbhlyiyw}"
  
  Serial.println("Posting MCP Data...");
  client.post("/mcp", contentType, postDataMcp);
  
  int statusCode = client.responseStatusCode();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  String response = client.responseBody();
  Serial.print("Response: ");
  Serial.println(response);
  Serial.println();

  String postDataMpu = "{\"x_axis\":";
  postDataMpu += aaReal.x/1000.00;
  postDataMpu += ",";
  postDataMpu += "\"y_axis\":";
  postDataMpu += aaReal.y/1000.00;
  postDataMpu += ",";
  postDataMpu += "\"z_axis\":";
  postDataMpu += aaReal.z/1000.00;
  postDataMpu += ",";
  postDataMpu += "\"yaw\":";
  postDataMpu += (ypr[0] * 180/M_PI);
  postDataMpu += ",";
  postDataMpu += "\"roll\":";
  postDataMpu += (ypr[2] * 180/M_PI);
  postDataMpu += ",";
  postDataMpu += "\"pitch\":";
  postDataMpu += (ypr[1] * 180/M_PI);
  postDataMpu += ",";
  postDataMpu += "\"temperature\":";
  postDataMpu += temperature;
  postDataMcp += ",";
  postDataMcp += "\"password\":fvwaebyiuoafeiwbhlyiyw}"
  Serial.println("Posting MPU Data...");
  client.post("/mpu", contentType, postDataMpu);
  // read the status code and body of the response
  int statusCode2 = client.responseStatusCode();
  Serial.print("Status code: ");
  Serial.println(statusCode2);
  String response2 = client.responseBody();
  Serial.print("Response: ");
  Serial.println(response2);

  Serial.println("Wait 2 seconds");
  Serial.print("\n\n");
  delay(2000);
}

float voltage(int raw){
  return raw / 1023.0 * 3.3;
}

LED_STATE classifySignal(float voltage){
  if(voltage < 200){
    CURRENT_STATE = S1;
    return S1;
  }else if(voltage >= 200 && voltage < 350){
    CURRENT_STATE = S2;
    return S2;
  }else if(voltage >= 350 && voltage < 500){
    CURRENT_STATE = S3;
    return S3;
  }else if(voltage >= 500 && voltage < 650){
    CURRENT_STATE = S4;
    return S4;
  }else if(voltage >= 650){
    CURRENT_STATE = S5;
    return S5;
  }
}

void turnOnLED(LED_STATE state){
    switch(state){
      case S1:
        digitalWrite(LED1, HIGH); // Turn the LED on
        digitalWrite(LED2, LOW); // Turn the LED off
        digitalWrite(LED3, LOW); // Turn the LED off
        digitalWrite(LED4, LOW); // Turn the LED off
        digitalWrite(LED5, LOW); // Turn the LED off
        break;
      case S2:
        digitalWrite(LED1, HIGH); // Turn the LED on
        digitalWrite(LED2, HIGH); // Turn the LED on
        digitalWrite(LED3, LOW); // Turn the LED off
        digitalWrite(LED4, LOW); // Turn the LED off
        digitalWrite(LED5, LOW); // Turn the LED off
        break;
      case S3:
        digitalWrite(LED1, HIGH); // Turn the LED on
        digitalWrite(LED2, HIGH); // Turn the LED on
        digitalWrite(LED3, HIGH); // Turn the LED on
        digitalWrite(LED4, LOW); // Turn the LED off
        digitalWrite(LED5, LOW); // Turn the LED off
        break;
      case S4:
        digitalWrite(LED1, HIGH); // Turn the LED on
        digitalWrite(LED2, HIGH); // Turn the LED on
        digitalWrite(LED3, HIGH); // Turn the LED on
        digitalWrite(LED4, HIGH); // Turn the LED on
        digitalWrite(LED5, LOW); // Turn the LED off
        break;
      case S5:
        digitalWrite(LED1, HIGH); // Turn the LED on
        digitalWrite(LED2, HIGH); // Turn the LED on
        digitalWrite(LED3, HIGH); // Turn the LED on
        digitalWrite(LED4, HIGH); // Turn the LED on
        digitalWrite(LED5, HIGH); // Turn the LED on
        break;
    }
}

int getCurrentState(){
  return CURRENT_STATE;
}

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

float convertTemperature(int16_t rawTemp){
    return ((float) rawTemp / 340.00) + 36.53;
}