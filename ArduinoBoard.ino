//libraries
#include <OneWire.h>           //library for a DS18B20 temperature sensor
#include <DallasTemperature.h> //library for a DS18B20 temperature sensor
#include <ArduinoJson.h>       //for sending JSON data from the transmitter to the receiver side

// objects for onewire and DallasTemperature classes are defined
OneWire oneWire(2);            //output pin of the DS18B20 sensor
DallasTemperature temp_sensor(&oneWire);

// declaration
float calibration_value = 21.34;
int pHvalue = 0;
unsigned long int avgval;
int buffer_arr[10], temp;

void setup()
{
  Serial.begin(9600);
  temp_sensor.begin();
}

// JSON Object is defined
StaticJsonBuffer<1000> jsonBuffer;  
JsonObject& root = jsonBuffer.createObject();

void loop() {
  for (int i = 0; i < 10; i++)            // read 10 sample Analog values and store them in an array.
  {
    buffer_arr[i] = analogRead(A0);              
    delay(30);
  }
  
  // sort the Analog values received in ascending order
  for (int i = 0; i < 9; i++)   
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  
  avgval = 0;
  
  // calculate the average of a 6 centre sample Analog values
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];

  // converted into actual pH value and stored in a variable
  float volt = (float)avgval * 5.0 / 1024 / 6;
  float ph_act = -5.70 * volt + calibration_value;
  
  temp_sensor.requestTemperatures();               // read the temperature values from the sensor
  
  int moisture_analog=analogRead(A1);              // read the soil moisture sensor
  int moist_act=map(moisture_analog,0,1023,100,0);

  // the parameters inserted into JSON objects and to be sent to NodeMCU
  root["a1"] = ph_act;
  root["a2"] = temp_sensor.getTempCByIndex(0);
  root["a3"] = moist_act;
  root.printTo(Serial);
  Serial.println("");
}
