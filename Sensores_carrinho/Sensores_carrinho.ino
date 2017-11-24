
int FC = A1; //Sensor Frente Centro
int FD = A0; //Sensor Frente Direira
int FE = A2; //Sensor Frente Esquerda
int TC = A4; //Sensor Trás Centro
int TD = A5; //Sensor Trás Direita
int TE = A3; //Sensor Trás Esquerda

int calibrando = 1;

int avgFC = 0;
int avgFD = 0;
int avgFE = 0;
int avgTC = 0;
int avgTD = 0;
int avgTE = 0;
int nCalibracoes = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Calibrando");
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
    Serial.print("back.");
    Serial.print(analogRead(FC) - avgFC);
    Serial.print(",");
    Serial.print(analogRead(FD) - avgFD);
    Serial.print(",");
    Serial.print(analogRead(FE) - avgFE);
    Serial.print(",");
    Serial.print(analogRead(TC) - avgTC);
    Serial.print(",");
    Serial.print(analogRead(TD) - avgTD);
    Serial.print(",");
    Serial.print(analogRead(TE) - avgTE);
    Serial.println();
    delay(100);
  }
}

void printTermometro(int input) {
  for (int i = 0; i < 1024; i++) {
    if (i < input) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }
    if (i < 1023) {
      Serial.print(",");
    }
  }
}

