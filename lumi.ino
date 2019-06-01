//TODO
/*
 * 7 - AUTO fazendo override na barra de luz
 * 8 - Bluetooth exibindo mensagem conectado mesmo quando desconecta
 * 12 - App crasha se mexer na barra de luz antes de conectar o bluetooth
 */
 
 
#include "Dimmer.h"

Dimmer lamp(3);
int ldrPin = A0;
int relePin = 7;
int readBluetooth;
boolean flagLigado = false;
boolean flagAuto = false;
 
 
void ligar() {
  digitalWrite(relePin, !digitalRead(relePin));
  flagLigado = !flagLigado;
}
 
void barraLuz() {
  if (flagAuto == false && flagLigado == true) {
    int valorBarra = Serial.read();
  lamp.set(valorBarra);  
  }
}
 
// LUZ DO CELULAR: 68
// NORMAL SALA: 85
// DEDO NO LDR: 98
 
void autoBtn (){
  flagAuto = !flagAuto;    
  if (flagAuto == true) {
      int saida = map(analogRead(ldrPin), 0, 1023, 0, 100);
      Serial.println(saida);
      lamp.set(saida);
      delay(10);
  }    
}
 
void setup() {
  lamp.begin();
  Serial.begin(9600);
  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, HIGH);  // O relé é acionado em LOW
}
 
void loop() {
  barraLuz();
  autoBtn();
 
  if (Serial.available()) {
    char data = Serial.read(); // reading the data received from the bluetooth module
    if (data == 'a') {
      ligar();  // ligar ou desligar
    }
    else if (data == 'b') {
      if (flagAuto = true) {
        flagAuto = false;
      }
    }
      flagAuto = true; //  auto
    }
  }
