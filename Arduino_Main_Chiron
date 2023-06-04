// Define pins for the alcohol sensor and switches
/* Replace these values with your own readings */

#define Relay 5
#define Sober 150   // Define max value that we consider sober
#define Drunk 300   // Define min value that we consider drunk
#define MQ3pin 7
float sensorValue;  //variable to store sensor value
const int switchPin = 3;
#define LtrigPin1 11 // Define pins for the ultrasonic sensors
#define LechoPin1 12
#define RtrigPin2 9
#define RechoPin2 10
long duration, distance, RightSensor,LeftSensor; // Define variables for the ultrasonic sensors


void setup()
{
Serial.begin(9600);

pinMode(LtrigPin1, OUTPUT);
pinMode(LechoPin1, INPUT);
pinMode(RtrigPin2, OUTPUT);
pinMode(RechoPin2, INPUT);
pinMode(MQ3pin, INPUT);

pinMode(switchPin, INPUT);

pinMode(Relay, OUTPUT);

Serial.println("Chiron is now Active");
}

void loop() {
  
  sensorValue = digitalRead(MQ3pin); 
  
  if (digitalRead(switchPin) == HIGH && sensorValue == HIGH) // Check if switches are pressed and alcohol is not detected
   {
     Serial.println("Helmet is Worn");
    
     Serial.println("Status: Bike starts since rider is SOBER");
    
     digitalWrite(Relay,HIGH);
     
     SonarSensor(LtrigPin1, LechoPin1);
     LeftSensor = distance;
     SonarSensor(RtrigPin2, RechoPin2);
     RightSensor = distance;

     Serial.print("Left Distance - ");
     Serial.print(LeftSensor);
     Serial.print(" | ");
     Serial.print("Right Distance - ");
     Serial.println(RightSensor);

     delay (500);
    }
    
    else if (digitalRead(switchPin) == HIGH && sensorValue == LOW)
    
    {
     Serial.println("Status: Bike wont start since rider is DRUNK");
     digitalWrite(Relay,LOW);
     delay (500);
    }

  else 
  
  {
    Serial.println("Sensors not Detected");
    digitalWrite(Relay,LOW);
    delay(500);
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
