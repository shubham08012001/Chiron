#include <WiFi.h>

// Replace with the SSID and password of the host ESP32's access point
const char* ssid = "Chiron";
const char* password = "rsss@2023";

// Replace with the IP address of the host ESP32
IPAddress hostIP(192, 168, 4, 1);

// Replace with the port number used by the host ESP32
const int hostPort = 0;

// GPIO pin for relay
const int relayPin = 15;

// Create a WiFiClient object
WiFiClient client;

void setup() {
  // Start serial communication
  Serial.begin(115200);
  delay(1000);

  // Set GPIO pin mode
  pinMode(relayPin, OUTPUT);

  // Connect to access point
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  // Print client IP address
  Serial.print("Client IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Connect to host
  if (!client.connected()) {
    Serial.println("Connecting to host");
    if (client.connect(hostIP, hostPort)) {
      Serial.println("Connected to host");
    }
  }

  // Read input value from host
  if (client.available()) {
    int inputValue = client.parseInt();
    Serial.print("Input value: ");
    Serial.println(inputValue);

    // Turn on/off relay based on input value
    digitalWrite(relayPin, inputValue);
  }

  // Wait for some time
  delay(100);
}
