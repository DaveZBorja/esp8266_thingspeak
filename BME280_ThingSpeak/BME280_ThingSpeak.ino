// By Dave Borja
// 24/05/2023
#include "ThingSpeak.h" //install library for thing speak
#include <ESP8266WiFi.h>
#include <BME280I2C.h>
#include <Wire.h>

char ssid[] = "MGT";        // your network SSID (name) 
char pass[] = "";    // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
BME280I2C bme;

unsigned long myChannelNumber = 2161015;
const char * myWriteAPIKey = "XGJBIZXHO07ELRO6";

// Initialize our values
String myStatus = "";

float temp(NAN), hum(NAN), pres(NAN);


void setup() {
  Serial.begin(115200);  //Initialize serial

  //WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  Wire.begin();

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  // bme.chipID(); // Deprecated. See chipModel().
  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  bme.read(pres, temp, hum, tempUnit, presUnit);

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("°"+ String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));
  Serial.print("\t\tHumidity: ");
  Serial.print(hum);
  Serial.print("% RH");
  Serial.print("\t\tPressure: ");
  Serial.print(pres);
  Serial.println(" Pa");

  // set the fields with the values
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, hum);
  ThingSpeak.setField(3, pres);

  
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  // for button power
  
  delay(20000); // Wait 20 seconds to update the channel again
}
