
#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
WiFiManager wifiManager;
ESP8266WebServer server(80);


int mosfet = 14;

void setup(void){

  // preparing GPIOs

  pinMode(mosfet, OUTPUT);
  digitalWrite(mosfet, LOW);
  delay(1000);
  Serial.begin(115200);
  
  Serial.printf(" ESP8266 Chip id = %08X\n", ESP.getChipId());
  
     if (!wifiManager.autoConnect("ConfigDomotics", "12345678")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  Serial.println("local ip");
  Serial.println(WiFi.localIP());

 
}
 
void loop(void){

  
} 
