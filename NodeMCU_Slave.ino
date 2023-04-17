#include <WiFi.h>

const char* ssid = "Chiron";          // change to your WiFi SSID
const char* password = "rsss@2023";  // change to your WiFi password
const char* serverIP = "192.168.4.1";    // change to IP address of the first board

WiFiClient client;

int relayPin = 14;

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(115200);
  Serial.println(" ");
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.println("Connected to WiFi");
  Serial.println(" ");
}

void loop() {
  if (!client.connected()) {
    Serial.println("Connecting to Server...");
    if (client.connect(serverIP, 80)) {
      Serial.println("Connected to Server");
      Serial.println(" ");
    } 
    else {
      Serial.println("Connection Failed");
      Serial.println(" ");
      delay(5000);
      return;
    }
  }

while (client.connected()) {
        if (client.available()) {
          Serial.println("Server is Active");
          String data = client.readStringUntil('\r');
          Serial.println(data);
          if (data == "ON") {
            digitalWrite(relayPin, HIGH);  
          } 
          else if (data == "OFF") {
            digitalWrite(relayPin, LOW);
          }
        }
        // execute some code every 100 milliseconds
        unsigned long currentMillis = millis();
        static unsigned long previousMillis = 0;
        if (currentMillis - previousMillis >= 100) {
          previousMillis = currentMillis;
          // execute some code here
        }
      }
      Serial.println("Disconnected from server");
      client.stop();
  
  // delay before trying to connect again
  delay (1000);
}
