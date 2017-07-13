#include <Servo.h>

#define co2Pin A0
#define tempPin A1
#define inicioBtn 2

#define valvulaPin 5
Servo valvula;

#define acendedorEletrico 3

bool estaQueimando;
long inicioQueima;
#define queimaLedPin 6
#define duracaoQueima 30000

void setup() {
  estaQueimando = false;
  inicioQueima = 0;

  pinMode(inicioBtn, INPUT);
  pinMode(acendedorEletrico, OUTPUT);
  pinMode(queimaLedPin, OUTPUT);
  valvula.attach(valvulaPin);
  
  Serial.begin(9600);
}

void MostrarSensores() {
  float co2 = map(analogRead(co2Pin), 0, 1023, 0, 100);
  float temp = (float(analogRead(tempPin))*5/(1023))/0.01;

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" °C\n");

  Serial.print("Nivel de CO2: ");
  Serial.print(co2);
  Serial.println("%\n");
}

//
// Inicia o processo de queima
//
void IniciarProcesso() {
  Serial.println("\n\n------------------------\n");
  Serial.println("> Iniciando a queima!");
  
  // Aciona a valula de gás
  valvula.write(90);
  Serial.println("> Abrindo a valvula!");
  delay(2500);

  // Acender o fogo
  digitalWrite(acendedorEletrico, HIGH);
  delay(1200);
  digitalWrite(acendedorEletrico, LOW);
  Serial.println("> Acendendo o fogo!");
  
  estaQueimando = true;
  inicioQueima = millis();

  digitalWrite(queimaLedPin, HIGH);
  Serial.println("\n>> ATENÇÃO! Forno ligado!");
  Serial.println("\n------------------------");
}

//
// O processo de queima aguarda o fim do processo e deliga o sistema
//
void ProcessoQueima() {
  // Verifica se o tempo de queima já foi atingido
  if(millis() - inicioQueima >= duracaoQueima) {
    Serial.println("\n> QUEIMA FINALIZADA!");
    digitalWrite(queimaLedPin, LOW);
    
    estaQueimando = false;
    inicioQueima = 0;
    
    valvula.write(0);
    delay(2500);
  }
}

void loop() {
  // Mostra os valores dos sensores no Serial
  MostrarSensores();

  // Aguarda o botão para iniciar o processo
  if(digitalRead(inicioBtn) == HIGH && !estaQueimando)
    IniciarProcesso();

  // Verifica se esta queimando
  else if(estaQueimando) {
    ProcessoQueima();
    delay(3000);
  }

  // Os led piscando indica estado de latância
  else {
    digitalWrite(queimaLedPin, HIGH);
    delay(700);
    digitalWrite(queimaLedPin, LOW);
  }
}
