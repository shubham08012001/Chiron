#include <WiFi.h>

const char* ssid = "Chiron";          // WiFi SSID
const char* password = "rsss@2023";     // WiFi password

WiFiServer server(80);

int gpioPin = 14;     // GPIO pin to read input from

void setup() {
  pinMode(gpioPin, INPUT);
  
  Serial.begin(115200);
  WiFi.softAP(ssid, password);           // create an access point
  IPAddress apIP = WiFi.softAPIP();      // get IP address of the access point
  Serial.println(" ");
  Serial.println("========================================");
  Serial.println("Access Point Started");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("Access Point IP Address: ");
  Serial.println(apIP);
  Serial.println("========================================");
  Serial.println(" ");
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client Connected");
    while (client.connected()) {
      if (digitalRead(gpioPin) == HIGH) {
        client.write("ON" "/r");
        Serial.println("Sent ON to client");
      } else {
        client.write("OFF""/r");
        Serial.println("Sent OFF to client");
      }
      delay(500);
    }
    Serial.println("Client disconnected");
    client.stop();
  }
}
