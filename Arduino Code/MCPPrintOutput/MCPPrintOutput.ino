#include <Adafruit_MCP3008.h>

#define LED1 3  // The pin 1st LED is connected to
#define LED2 4  // The pin 2nd LED is connected to
#define LED3 5  // The pin 3rd LED is connected to
#define LED4 6  // The pin 4th LED is connected to
#define LED5 7  // The pin 5th LED is connected to

Adafruit_MCP3008 adc;

enum LED_STATE{
  S0 = 0, //initial state
  S1 = 1,
  S2 = 2,
  S3 = 3,
  S4 = 4,
  S5 = 5
};

void setup() {
  pinMode(LED1, OUTPUT); // Declare the LED as an output
  pinMode(LED2, OUTPUT); // Declare the LED as an output
  pinMode(LED3, OUTPUT); // Declare the LED as an output
  pinMode(LED4, OUTPUT); // Declare the LED as an output
  pinMode(LED5, OUTPUT); // Declare the LED as an output
  
  Serial.begin(9600);
  while (!Serial);

  Serial.println("MCP3008 simple test.");
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
    switch(currState){
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
    delay(2000);
}


float voltage(int raw){
  return raw / 1023.0 * 3.3;
}

LED_STATE classifySignal(float voltage){
  if(voltage < 200){
    return S1;
  }else if(voltage >= 200 && voltage < 350){
    return S2;
  }else if(voltage >= 350 && voltage < 500){
    return S3;
  }else if(voltage >= 500 && voltage < 650){
    return S4;
  }else if(voltage >= 650){
    return S5;
  }
}