#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <typeinfo>


const char* ssid = "";
const char* password = "";

int bluePin = 12;
int redPin = 13;
 
void setup () {
 
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
 
}

void loop() {
 
  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http; 
 
    int beginResult = http.begin("http://192.168.0.103:3000/leds");
    int httpCode = http.GET();   
          
    Serial.println(httpCode);
    if (httpCode > 0) {

      
      const size_t bufferSize = JSON_ARRAY_SIZE(2) + 2*JSON_OBJECT_SIZE(5) + 140;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonArray& root = jsonBuffer.parseArray(http.getString());

      // Parameters
      if (root[0]["status"] == true) {
        digitalWrite(bluePin, HIGH);
      } else {
        digitalWrite(bluePin, LOW);
      }

      if (root[1]["status"] == true) {
        digitalWrite(redPin, HIGH);
      } else {
        digitalWrite(redPin, LOW);
      }

    }
 
    http.end();
 
  }
  delay(200);
 
}
