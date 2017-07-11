#define temp 2
#define co2 3

#define fire 5
#define fire_led 6
#define fire_time 30000

void setup() {
  pinMode();
}

void loop() {
  float temp = (5.0 * analogRead(tempPin) * 100.0) / 1024;
  float co2 = map(analogRead(tempPin), 0, 1023, 0, 100);

  Serial.print("Temperatura: ")
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Nivel de CO2: ");
  Serial.print(co2);
  Serial.println("%");

  pulseTime(fire, 300);
  delay(fire_delay);

  // Apagar
}

void pulseTime(int port, int mili) {
  digitalWrite(port, HIGH);
  delay(mili);
  digitalWrite(port, LOW);
}
