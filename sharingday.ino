#include <WiFi.h>
#include <HTTPClient.h> 

const char* ssid = "Cabo 1113 2.4";
const char* password =  "12121514";
String serverAddress = "http://192.168.0.25:3333/sharing_day";
void setup() {
  pinMode(4, OUTPUT);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  }
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverAddress.c_str());

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);

        if (httpResponseCode == 200) {
          digitalWrite(4, HIGH);
        } else if (httpResponseCode == 202) {
          digitalWrite(4, LOW);
        }
    } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    http.end();
    delay(1000);
  }
}
