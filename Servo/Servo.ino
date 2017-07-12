include span style="color: #cc6600;">Servo.h>
Servo motor;
Servo motor2;
Servo motor3;
int sensorPin = A1;
int incinerador = 6;
int sensorValue = 0;
int sensorValuePorc
int led1 = 11;
int trigPin = 12;
int echoPing = 13;
void setup() {
 Serial.begin(9600);
 pinMode(sensorPin, INPUT);
 pinMode(incinerador, OUTPUT);
 pinMode(led1, OUTPUT);
 pinMode(echoPing, INPUT);
 pinMode(trigPin, OUTPUT);
  motor.attach(3); 
  motor2.attach(4); 
  motor3.attach(5); 
}

void loop() {

 sensorValue = analogRead(sensorPin);
 sensorValuePorc = map(sensorValue,0,1023,0,100);
 Serial.print(sensorValuePorc);
 Serial.println(" %");

 long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin , LOW);
  duration = pulseIn(echoPing, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print(distance);
  Serial.println("Cm");
  delay (500);
  if ( distance <= 20)
  {
   delay(500);
   motor.write(90);
   motor.write(0);
   motor2.write(180);
   motor2.write(90);
    
  }

    delay(300000);
    
   if (sensorValuePorc <=40 )

   {
    delay(15000)
    digitalWrite(incinerador, HIGH);
    delay(480000);
    digitalWrite(incinerador, LOW);
    motor3.write(90);
    
    
    
    }

}
