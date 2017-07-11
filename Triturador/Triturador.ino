// PINS
#define ultra 2
#define ultra_trig 3
#define temp 4
#define co2Sensor A0
#define engine 5
#define eng_led 8

// TIMERS
#define ENGINE 1000
#define MAN_WAIT 1000
#define FIRE 1000

void setup() {
  pinMode(ultra, OUTPUT);
  pinMode(engine, OUTPUT);
  pinMode(ultra_trig, OUTPUT);
  pinMode(ultra, INPUT);
  pinMode(eng_led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(ultra_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(ultra_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultra_trig, LOW);
  
  long s = (pulseIn(ultra, HIGH)/2) / 29.1; // CM
  Serial.print(s);
  Serial.println(" cm");
  
  if(s < 10) {
    digitalWrite(eng_led, HIGH);
    pulseTime(engine, ENGINE);
    digitalWrite(func_led, LOW);
  }
}

void pulseTime(int port, long timeout) {
  digitalWrite(port, HIGH);
  delay(timeout);
  digitalWrite(port, LOW);
}
