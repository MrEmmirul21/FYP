// Libraries
#include <Ethernet.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SHA3.h>

// Objects for both classes are defined
OneWire oneWire(5); // Data wire is plugged into pin 2 on the Arduino 
DallasTemperature temp_sensor(&oneWire);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "169.254.180.25";
IPAddress ip(169, 254, 180, 26);  // Set the static IP address

EthernetClient client;

// Declaration
float temperature, acidity;
int turbidity;
String postdata;
String hashvalue;
long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000; // READING INTERVAL
///////////////////////////////////// Setup Function /////////////////////////////////////
void setup() {
  
  Serial.begin(9600);
  Ethernet.init(10);

	if (Ethernet.begin(mac) == 0) {
		Serial.println("Failed to configure Ethernet using DHCP"); 
    Ethernet.begin(mac,ip);
    Serial.print("Static IPv4 Address : ");
    Serial.println(Ethernet.localIP());
	}

  temp_sensor.begin();   // temperature sensor
  pinMode(A0,INPUT);     // turbidity sensor
  pinMode(A1,INPUT);     // pH sensor
}
/////////////////////////////// Temperature Sensor Reading ///////////////////////////////
float readTemperature()  // read temperature
{
  temp_sensor.requestTemperatures(); // to send a command to get the temperature values from the sensor
  temperature = temp_sensor.getTempCByIndex(0); // read temperature value

  return temperature;
}
//////////////////////////////// Turbidity Sensor Reading ////////////////////////////////
int detectTurbidity()    // detect turbidity
{
  int read_ADC = analogRead(A0);

  if (read_ADC > 208) {
    read_ADC = 208;
  }
  turbidity = map(read_ADC, 0, 208, 300, 0);

  return turbidity;
}
/////////////////////////////////// pH Sensor Reading ///////////////////////////////////
float readpHvalue()
{
  float pHvalue;
  unsigned long int avgValue;  // Store the average value of the sensor feedback
  int buf[10], temp;

  for (int i = 0; i < 10; i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i] = analogRead(A1);
    delay(10);
  }
  for (int i = 0; i < 9; i++)   //sort the analog from small to large
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)               //take the average value of 6 center sample
    avgValue += buf[i];

  float phValue = (float)avgValue * 5.0 / 1024 / 6; //convert the analog into millivolt
  acidity = 3.5 * phValue;                  //convert the millivolt into pH value

  return acidity;
}

////////////////////////////// send HTTP request to server //////////////////////////////
void sendHTTPrequest(String postdata)
{
  // connect to web server the server and post data to add.php
  if (client.connect(server,80))
  {
    Serial.println("Web Server connected :)");
    // Make a HTTP request
    client.println("POST /webserver/add.php HTTP/1.1");
	  client.println("Host: 169.254.180.25"); 
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: "); 
	  client.println(postdata.length()); 
	  client.println(); 
	  client.print(postdata);
  }
  else { Serial.println("Failed connection :("); }

  // get reply from the server if server receive the postdata
  Serial.println("Server Response :");  
  while(client.connected())
  {
    if (client.available()) {
      char byte = client.read();
      Serial.print(byte);
    }
  }
  Serial.println("\n");
  delay(1000);
  
  // Disconnect from the server
  if (client.connected()) { 
		client.stop();	
	}
}
/////////////////////////////////////// Main loop ///////////////////////////////////////
void loop() {

	currentMillis = millis();
	if(currentMillis - previousMillis > interval) { // READ ONLY ONCE PER INTERVAL
		previousMillis = currentMillis;

    temperature = readTemperature();  // call readtemperature() function
    turbidity = detectTurbidity();    // call detectTurbidity() function
    acidity = readpHvalue();          // call readpHvalue() function
    //hashvalue = "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678900";
    hashvalue = "0123456789";
  }
  postdata = "api_key=tPmAT5Ab3j7F9";
  postdata += "&temperature="+ String(temperature);
  postdata += "&turbidity="+ String(turbidity);
  postdata += "&acidity="+ String(acidity);
  postdata += "&hash="+ String(hashvalue);
  
  sendHTTPrequest(postdata);

	delay(3000); 
}
