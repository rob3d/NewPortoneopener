
#include <FS.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <SPI.h>
#include "RestClient.h"

WiFiManager wifiManager;
ESP8266WebServer server(80);

const String shouldOpen ="SHOULD_OPEN";
RestClient client = RestClient("my.milan.maison",443, "A9 E5 6D E5 9F 55 3E F4 1C F7 1A BC 17 70 24 83 68 26 52 18");
int mosfet = 12;
char path[50];
String response;

void setup(void) { 
  Serial.begin(115200);
  pinMode(mosfet, OUTPUT);
  digitalWrite(mosfet, LOW);
  delay(1000);  
  if (!wifiManager.autoConnect("ConfigDomotics", "12345678")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  Serial.println("connected...yeey :)");
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
  sprintf(path, "/api/smart_gates/%08X/status", ESP.getChipId());
}

void loop(void){
  Serial.print("The path is: ");
  Serial.println(path);
  client.setHeader("X-Secret-Token: ffab1234abab");
  response = "";
  int statusCode = client.get(path, &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  if(response.indexOf(shouldOpen)!=-1){
         Serial.println("APRO SUBBBBITO");
         digitalWrite(mosfet,HIGH);
         delay(5000);
         digitalWrite(mosfet,LOW);
    }
  delay(1000);
}
