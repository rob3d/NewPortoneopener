
#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
MDNSResponder mdns;
WiFiManager wifiManager;

// the IP address for the shield:
 //IPAddress _ip = IPAddress(192, 168, 1, 250);//If you want a static ip.
 //IPAddress _gw = IPAddress(192, 168, 1, 1);//If you want a static ip.
 //IPAddress _sn = IPAddress(255, 255, 255, 0);//If you want a static ip.
  


ESP8266WebServer server(80);

String webPage = "";

int gpio2_pin = 14;
int connectiontime=0;

void setup(void){
  webPage += "<h1>ApriPortone IoT</h1>";
  webPage += "<p>Portone 1 <a href=\"apri\"><button>Apri</button></a></p>";
  
  // preparing GPIOs

  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  
  delay(1000);
  Serial.begin(115200);
  Serial.printf(" ESP8266 Chip id = %08X\n", ESP.getChipId());
  
 // wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);//If you want a static ip.

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

  /*
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  
  server.on("/apri", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
    digitalWrite(gpio2_pin, LOW);
    delay(1000); 
  });
  
  
  server.begin();
  Serial.println("HTTP server started");*/
}
 
void loop(void){
//  server.handleClient();
  
} 
