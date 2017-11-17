//#include <MemoryFree.h>

#include <math.h>
#include "teste.h"
#include <avr/pgmspace.h>

const PROGMEM int FC = A1; //Sensor Frente Centro
const PROGMEM int FD = A0; //Sensor Frente Direira
const PROGMEM int FE = A2; //Sensor Frente Esquerda
const PROGMEM int TC = A4; //Sensor Trás Centro
const PROGMEM int TD = A5; //Sensor Trás Direita
const PROGMEM int TE = A3; //Sensor Trás Esquerda

int limiteDoBleaching;

void setup() {
  Serial.begin(9600);
  limiteDoBleaching = definirBleachingDasRedes();
  Serial.println("Bleaching definido");
  Serial.println(limiteDoBleaching);
  Serial.flush();
}

void loop() {
  
  Serial.println("Loop");
  int entrada[IMPUT_SIZE];
  int inputs[6];
  inputs[0] = analogRead(FC);
  inputs[1] = analogRead(FD);
  inputs[2] = analogRead(FE);
  inputs[3] = analogRead(TC);
  inputs[4] = analogRead(TD);
  inputs[5] = analogRead(TE);

  int k = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < SIGNAL_SIZE[0]; j++, k++) {
      //SQUARE ROOT OF SIGNAL_SIZE
      if (j < inputs[i]/INPUT_FACTOR) {
        entrada[k] = 1;
      } else {
        entrada[k] = 0;
      }
    }
  }

  Serial.println("Testando");
  String resultado = testarRedes(limiteDoBleaching, entrada);
  Serial.print(resultado);
  Serial.println();
  delay(500);
}

