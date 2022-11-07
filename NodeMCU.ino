#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include <ArduinoJson.h>

// declare network credentials to connect our NodeMCU to the internet
const char* ssid = "admin";        // Replace with your network SSID
const char* password = "12345678"; // Replace with your network password

// object for ESP8266WebServer class is defined
ESP8266WebServer server(80);       
String page = "";
int data1, data2, data3;

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);            // pass network credentials
while (WiFi.status() != WL_CONNECTED)    // check for the successful network connection
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println(WiFi.localIP());        // print a IP address in the Serial Monitor

  // HTML page for Water Quality Monitoring System
  server.on("/", []()
  {
    page = "<html><head><title>IoT Design</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  green ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Aquaculture Monitoring using IoT</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>Parameters</th><th>Value</th><th>Units</th></tr><tr><td>PH Value</td><td>"+String(data1)+"</td><td>N/A</td></tr>";
    page += "<tr><td>Temperature</td><td>"+String(data2)+"</td><td>Centigrade</td></tr><tr><td>Moisture</td><td>"+String(data3)+"</td><td>%</td>";
    page += "<meta http-equiv=\"refresh\" content=\"3\">";
    server.send(200, "text/html", page);
  });
  server.begin();
}
void loop()
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(Serial);

  if (root == JsonObject::invalid())           // check for valid JSON data reception, from the Transmitter side
  {
    return;
    Serial.println("invalid");
  }
  
  // data received are assigned to individual variables and appended in the HTML webpage for real-time display
  data1 = root["a1"];
  data2 = root["a2"];
  data3 = root["a3"];
  Serial.println(data1);
  Serial.println(data2);
  Serial.println(data3);

  // to handle the client request
  server.handleClient();
}
Video
