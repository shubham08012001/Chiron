#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// Replace with your network credentials
const char* ssid = "Chiron";
const char* password = "rsss@2023";

// Replace with the IP address and port of the client ESP32
IPAddress clientIP(192, 168, 4, 2);
const int clientPort = 80;

// GPIO pin for input
const int inputPin = 14;

// Create a server object
WiFiServer server(80);

void setup() {
  // Start serial communication
  Serial.begin(115200);
  delay(1000);

  // Set GPIO pin mode
  pinMode(inputPin, INPUT);

  // Start AP
  WiFi.softAP(ssid, password);

  // Get AP IP address and Port
  IPAddress apIP = WiFi.softAPIP();
  const int apPort = WiFi.softAPgetStationNum();
  
// Print SSID, AP IP address & Port
  Serial.println("");
  Serial.print("Wi-Fi access point created with SSID: ");
  Serial.println(ssid);
  Serial.print("Access Point IP address: ");
  Serial.println(apIP);
  Serial.print("Access Point Port: ");
  Serial.println(apPort);
  

  // Start server
  server.begin();
}

void loop() {
  // Wait for a client to connect
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client Connected");
    
    // Read input value
    int inputValue = digitalRead(inputPin);

    // Send input value to client
    client.println(inputValue);

    // Wait for client to read input value
    delay(10);

    // Close connection
    client.stop();
    
  }
}
