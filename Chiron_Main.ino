// Define pins for the alcohol sensor and switches
/* Replace these values with your own readings */

#define Relay 5
#define Sober 299   // Define max value that we consider sober
#define Drunk 300   // Define min value that we consider drunk
#define MQ3pin A0
float sensorValue;  //variable to store sensor value
const int switch1Pin = 2;
const int switch2Pin = 3;
#define LtrigPin1 11// Define pins for the ultrasonic sensors
#define LechoPin1 12
#define RtrigPin2 9
#define RechoPin2 10
long duration, distance, RightSensor,LeftSensor;// Define variables for the ultrasonic sensors
// Define variables for the alcohol sensor


void setup()
{
Serial.begin(9600);

pinMode(LtrigPin1, OUTPUT);
pinMode(LechoPin1, INPUT);
pinMode(RtrigPin2, OUTPUT);
pinMode(RechoPin2, INPUT);

// Set the switch pins as inputs
pinMode(switch1Pin, INPUT_PULLUP);
pinMode(switch2Pin, INPUT_PULLUP);

pinMode(Relay, OUTPUT);
}

void loop() {
  sensorValue = analogRead(MQ3pin); 
  // Check if both switches are pressed and alcohol is not detected
  if (digitalRead(switch1Pin) == LOW && digitalRead(switch2Pin) == LOW && sensorValue < 300) 
   {
      if (sensorValue >= Sober && sensorValue < Drunk)
   {
    
     Serial.println("  |  Status: Bike starts since rider is SOBER");

     digitalWrite(Relay,HIGH);
     
     SonarSensor(LtrigPin1, LechoPin1);
     LeftSensor = distance;
     SonarSensor(RtrigPin2, RechoPin2);
     RightSensor = distance;

     Serial.print(LeftSensor);
     Serial.print(" - ");
     Serial.println(RightSensor);
     Serial.print(" - ");

   }
   else 
  {
     Serial.println("  |  Status: Bike wont start since rider is DRUNK");
  }

  }
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
}
