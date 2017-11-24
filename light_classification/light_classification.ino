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

int* limiteDoBleaching;

int entrada[INPUT_SIZE];

int calibrando = 1;

int avgFC = 0;
int avgFD = 0;
int avgFE = 0;
int avgTC = 0;
int avgTD = 0;
int avgTE = 0;
int nCalibracoes = 0;

//Carrinho
int pinoMotorEsquerdo_IN3 = 6;
int pinoMotorEsquerdo_IN4 = 7;
int pinoMotorDireito_IN1 = 8;
int pinoMotorDireito_IN2 = 9;
int pinoEnableMotorEsquerdo = 11;
int pinoEnableMotorDireito = 10;


int n = 0;
int nGap = 5;

void setup() {
  Serial.begin(9600);
  //Carrinho
  pinMode(pinoMotorEsquerdo_IN3, OUTPUT);
  pinMode(pinoMotorEsquerdo_IN4, OUTPUT);
  pinMode(pinoMotorDireito_IN1, OUTPUT);
  pinMode(pinoMotorDireito_IN2, OUTPUT);
  pinMode(pinoEnableMotorEsquerdo, OUTPUT);
  pinMode(pinoEnableMotorDireito, OUTPUT);
  //habilita e definie a velocidade dos dois motores do carrinho
  analogWrite(pinoEnableMotorEsquerdo, 5);
  analogWrite(pinoEnableMotorDireito, 250);

  limiteDoBleaching = definirBleachingDasRedes();
  Serial.print("Bleaching definido - ");
  for (int i = 0; i < 5; i++) {
    Serial.print(limiteDoBleaching[i]);
    Serial.print(" - ");
  }
  Serial.println();
  Serial.println("Calibrando");
  Serial.flush();
}

void loop() {

  if (calibrando) {

    avgFC += analogRead(FC);
    avgFD += analogRead(FD);
    avgFE += analogRead(FE);
    avgTC += analogRead(TC);
    avgTD += analogRead(TD);
    avgTE += analogRead(TE);
    nCalibracoes++;

    if (nCalibracoes >= 20) {
      avgFC = avgFC / nCalibracoes;
      avgFD = avgFD / nCalibracoes;
      avgFE = avgFE / nCalibracoes;
      avgTC = avgTC / nCalibracoes;
      avgTD = avgTD / nCalibracoes;
      avgTE = avgTE / nCalibracoes;
      calibrando = 0;
    }

  } else {
    int inputs[6];
    inputs[0] = analogRead(FC) - avgFC;
    inputs[1] = analogRead(FD) - avgFD;
    inputs[2] = analogRead(FE) - avgFE;
    inputs[3] = analogRead(TC) - avgTC;
    inputs[4] = analogRead(TD) - avgTD;
    inputs[5] = analogRead(TE) - avgTE;


    int k = 0;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < SIGNAL_SIZE; j++, k++) {
        //SQUARE ROOT OF SIGNAL_SIZE
        if (j < inputs[i] / INPUT_FACTOR) {
          entrada[k] = 1;
        } else {
          entrada[k] = 0;
        }
      }
    }

    
    String resultado = testarRedes(limiteDoBleaching, entrada);
    Serial.println(n);
    n++;
    if (resultado == "idle" && n>=nGap) {
      n=0;
      pararCarrinho();
      Serial.println("idle");
      delay(100);
    } else if (resultado == "right" && n>=nGap) {
      n=0;
      moverCarrinhoParaDireita ();
      Serial.println("direita");
      delay (800);
    } else if (resultado == "left" && n>=nGap) {
      n=0;
      moverCarrinhoParaEsquerda();
      Serial.println("esquerda");
      delay (800);
    } else if (resultado == "back" && n>=nGap){
      n=0;
      moverCarrinhoParaDireita ();
      Serial.println("tras");
      delay (2000);
    } else if (resultado == "front" && n>=nGap){
      n=0;
      moverCarrinhoParaFrente ();
      Serial.println("frente");
      delay(100);
    }
  }
}

void girarRodaDireitaParaDireita()
{
  digitalWrite(pinoMotorDireito_IN1, HIGH);
  digitalWrite(pinoMotorDireito_IN2, LOW);
}

void girarRodaDireitaParaEsquerda()
{
  digitalWrite(pinoMotorDireito_IN1, LOW);
  digitalWrite(pinoMotorDireito_IN2, HIGH);
}

void girarRodaEsquerdaParaDireita()
{
  digitalWrite(pinoMotorEsquerdo_IN3, LOW);
  digitalWrite(pinoMotorEsquerdo_IN4, HIGH);
}

void girarRodaEsquerdaParaEsquerda()
{
  digitalWrite(pinoMotorEsquerdo_IN3, HIGH);
  digitalWrite(pinoMotorEsquerdo_IN4, LOW);
}

void pararCarrinho()
{
  digitalWrite(pinoMotorDireito_IN1, HIGH);
  digitalWrite(pinoMotorDireito_IN2, HIGH);
  digitalWrite(pinoMotorEsquerdo_IN3, HIGH);
  digitalWrite(pinoMotorEsquerdo_IN4, HIGH);
}


void moverCarrinhoParaFrente()
{
  girarRodaDireitaParaDireita();
  girarRodaEsquerdaParaEsquerda();
}

void moverCarrinhoParaTras()
{
  girarRodaDireitaParaEsquerda();
  girarRodaEsquerdaParaDireita();
}

void moverCarrinhoParaDireita()
{
  girarRodaDireitaParaEsquerda();
  girarRodaEsquerdaParaEsquerda();
}

void moverCarrinhoParaEsquerda()
{
  girarRodaEsquerdaParaDireita();
  girarRodaDireitaParaDireita();
}

