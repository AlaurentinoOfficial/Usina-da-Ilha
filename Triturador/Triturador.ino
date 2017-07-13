#define ultraPin 2
#define ultraTrigPin 3

#define inicioBtn 4

#define motor 5
#define motorLedPin 6

bool estaTriturando;
long inicioProcesso;
#define tempoTrituracao 30000

void setup() {
  Serial.begin(9600);
  Serial.println("> Iniciando Maquina Trituradora ...");
  
  pinMode(ultraPin, OUTPUT);
  pinMode(ultraTrigPin, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(motorLedPin, OUTPUT);

  estaTriturando = false;

  delay(1000);
  Serial.println("> Maquina iniciada!");
}

float Ultrassonico() {
  digitalWrite(ultraTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultraTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraTrigPin, LOW);
  
  float ultra = (pulseIn(ultraPin, HIGH)/2) / 29.1; // CM
  Serial.println("\n> Volume: " + String(ultra) + " cm");

  return ultra;
}

void IniciarProcesso() {
  Serial.println("\n\n-----------------------\n");
  Serial.println("> Iniciando trituração!");

  // Liga o led
  digitalWrite(motorLedPin, HIGH);

  // Liga o motor
  digitalWrite(motor, HIGH);
  delay(500);
  Serial.println("> Motor ligado!");

  estaTriturando = true;
  inicioProcesso = millis();
  Serial.println("\n> ATECAO, TRITURADOR ESTA LIGADO!");
  Serial.println("\n-----------------------\n");
}

void ProcessoMotor() {
  if(millis() - inicioProcesso >= tempoTrituracao) {
    Serial.println("\n> FINALIZANDO TRITURACAO!");
    // Reinicia o processo
    inicioProcesso = 0;
    estaTriturando = false;

    // Desliga o motor
    digitalWrite(motor, LOW);

    // Desliga o led
    digitalWrite(motorLedPin, LOW);
  }
}

void loop() {
  // Agurda o botão para inciar o processo
  if(digitalRead(inicioBtn) == HIGH && Ultrassonico() < 10 && estaTriturando)
    IniciarProcesso();

  // Verifica se esta triturando
  else if (estaTriturando)
    ProcessoMotor();

  else {
    digitalWrite(motorLedPin, HIGH);
    delay(700);
    digitalWrite(motorLedPin, LOW);
  }
}
