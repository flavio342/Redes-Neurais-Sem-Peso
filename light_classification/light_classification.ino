#include <math.h>

#include "treino.h"

short FC = A1; //Sensor Frente Centro
short FD = A0; //Sensor Frente Direira
short FE = A2; //Sensor Frente Esquerda
short TC = A4; //Sensor Trás Centro
short TD = A5; //Sensor Trás Direita
short TE = A3; //Sensor Trás Esquerda



Rede** redes;
short limiteDoBleaching;
short isSetupDone = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando Setup");
  redes = criarRedes();
  Serial.println("Redes Criadas");
  redes = treinarRedesDoArquivo(redes);
  Serial.println("Redes Treinadas");
  limiteDoBleaching = definirBleachingDasRedes(redes);
  Serial.println("Bleaching Definido");
}

void loop() {

  short entrada[IMPUT_SIZE];
  short inputs[6];
  inputs[0] = analogRead(FC);
  inputs[1] = analogRead(FD);
  inputs[2] = analogRead(FE);
  inputs[3] = analogRead(TC);
  inputs[4] = analogRead(TD);
  inputs[5] = analogRead(TE);

  short k = 0;
  for (short i = 0; i < 5; i++) {
    for (short j = 0; j < SIGNAL_SIZE; j++, k++) {
      //SQUARE ROOT OF SIGNAL_SIZE
      if (j < pow(inputs[i], 1.0/4)) {
        entrada[k] = 1;
      } else {
        entrada[k] = 0;
      }
    }
  }

  String resultado = testarRedes(redes, limiteDoBleaching, entrada);
  Serial.print(resultado);
  Serial.println();
  delay(100);
}

