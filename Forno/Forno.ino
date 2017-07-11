#define temp 2
#define co2 3

#define vela 5
#define queima_led 6
#define duracao_queima 30000

void setup() {
  pinMode(vela, OUTPUT);
  pinMode(queima_led, OUTPUT);
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

  pulseTime(queima, 300);
  digitalWrite(queima_led, HIGH);
  delay(duracao_queima);
  digitalWrite(queima_led, LOW);

  // Apagar()
}

void pulseTime(int port, int mili) {
  digitalWrite(port, HIGH);
  delay(mili);
  digitalWrite(port, LOW);
}
