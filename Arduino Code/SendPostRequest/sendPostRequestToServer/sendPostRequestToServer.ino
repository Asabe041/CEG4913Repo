#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

/////// Wifi Settings ///////
char ssid[] = "stingray";
char pass[] = "";

const char serverName[] = "192.168.1.131";  // server name
int port = 8081;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverName, port);
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
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
}

void loop() {
  Serial.println("making POST request");

  String contentType = "application/json";
  String postDataMcp = "{\"data\":\"";
  postDataMcp += "Hello MCP World!";
  postDataMcp += "\"}";
  
  String postDataMpu = "{\"data\":\"";
  postDataMpu += "Hello MPU World!";
  postDataMpu += "\"}";

  Serial.println("Posting to MCP");

  client.post("/mcp", contentType, postDataMcp);
  
  int statusCode = client.responseStatusCode();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  String response = client.responseBody();
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("waiting 1.5 Seconds to Post MPU");
  delay(1500);

  Serial.println("Posting to MPI");

  client.post("/mpu", contentType, postDataMpu);

  int statusCode2 = client.responseStatusCode();
  Serial.print("Status code: ");
  Serial.println(statusCode2);
  String response2 = client.responseBody();
  Serial.print("Response: ");
  Serial.println(response2);

  // read the status code and body of the response
  

  Serial.println("Wait 5 seconds");
  delay(5000);
}
