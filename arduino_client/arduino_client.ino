#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ArduinoJson.h>

#include <SocketIoClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

int bluePin = 12;
int redPin = 13;
int switchPin = 0;

void event(const char payload[], size_t length) {
  DynamicJsonBuffer jsonBuffer(length);
  JsonArray& root = jsonBuffer.parseArray(payload);

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

void setup() {
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);


    USE_SERIAL.begin(115200);

    WiFi.begin("Hemoglobina", "zxasqw12");

    while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

  HTTPClient http;

    int beginResult = http.begin("http://192.168.0.101:3000/leds");
    int httpCode = http.GET();
    if (httpCode > 0) {
      const size_t bufferSize = JSON_ARRAY_SIZE(2) + 2 * JSON_OBJECT_SIZE(5) + 140;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonArray& root = jsonBuffer.parseArray(http.getString());

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

    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }

    WiFiMulti.addAP("ssid", "pass");

    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }




    webSocket.on("event", event);
    webSocket.begin("192.168.0.101", 3000);

}

void loop() {
    webSocket.loop();

    if (digitalRead(0) == LOW) {
      webSocket.emit("button 0");

    }

}