

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;
String shouldOpen;
void setup() {
//shouldOpen = String("{"smart_gate":{"status":"SHOULD_OPEN"}}");

    Serial.begin(115200);
   // Serial.setDebugOutput(true);

    Serial.println();
    Serial.println();
    Serial.println();

    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    WiFiMulti.addAP("VietatoScroccare", "sntrbt010900sntlss270793");

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        http.begin("https://my.milan.maison/api/smart_gates/1/status", "A9 E5 6D E5 9F 55 3E F4 1C F7 1A BC 17 70 24 83 68 26 52 18"); //HTTPS //HTTPS
//http.begin("https://my.milan.maison/api/smart_gates/1/status");
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();
        http.addHeader("Content-Type", "application/json");
        http.addHeader("NULL", "NULL");
        http.writeToStream(&Serial);
       
        
//       if(http.writeToStream().substring(25,36)=="SHOULD_OPEN"){
                //  Serial.println("APRO SUBBBBITO");}
        http.end();
        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("\n[HTTP] GET... code: %d\n", httpCode);
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                payload.toLowerCase();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }

    delay(10000);
}

