

/*
 * Inclui a biblioteca "Dimmer.h" necessária para
 * o controle da intensidade luminosa
 */

#include "Dimmer.h"

/*
 * Seta os pinos e flags utilizados
 */

Dimmer lamp(3);
int ldrPin = A0;
int relePin = 7;
int readBluetooth;
boolean flagLigado = false;
boolean flagAuto = false;


//--------------FUNCÕES---------------//


/*
 * Função que liga a luminária
 */

void ligar() {
  digitalWrite(relePin, !digitalRead(relePin));
  flagLigado = !flagLigado;
}


/*
 * Função que ajusta o valor da luminária
 * de acordo com a barra de luz
 */
 
void barraLuz() {
  if (flagAuto == false && flagLigado == true) {
    int valorBarra = Serial.read();
    lamp.set(valorBarra);  
  }
}


/*
 * Função que controla automaticamente a intensidade
 * da luminária baseado no valor de leitura do LDR
 */

void autoBtn (){
  flagAuto = !flagAuto;    
  if (flagAuto == true) {
      int saida = map(analogRead(ldrPin), 0, 1023, 0, 100);
      Serial.println(saida);
      lamp.set(saida);
      delay(10);
  }    
}


//----------FIM DAS FUNÇÕES-----------//

/*
 * Setup que inicializa as variáveis necessárias
 */
 
void setup() {
  lamp.begin();
  Serial.begin(9600);
  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, HIGH);  // O relé inicia desligado
}

/*
 * Loop responsável pelo funcionamento do código 
 */
 
void loop() {
 
  if (Serial.available()) {               // Se receber dados do bluetooth
    char data = Serial.read();           // lê o dado enviado pelo bluetooth
    if (data == 'a') {                  // Se dado for 'a'
      ligar();                         // chama a função 'ligar()' que liga ou desliga a luminária
    }
    else if (data == 'b') {           // Se dado for 'b'
      autoBtn();                     // Chama a função 'autoBtn()' que 
                                    // deixa a lumiária em modo automático       
    }

  else if (data == 'c') {         // Se dado for 'c'
     barraLuz();                 // Chama a função 'barraLuz()' que
                                //  Atualiza a intensidade da luminária para o valor da barra
  }
 }
  delay(10);
}
