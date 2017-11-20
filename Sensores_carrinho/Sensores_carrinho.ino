
int FC = A1; //Sensor Frente Centro
int FD = A0; //Sensor Frente Direira
int FE = A2; //Sensor Frente Esquerda
int TC = A4; //Sensor Trás Centro
int TD = A5; //Sensor Trás Direita
int TE = A3; //Sensor Trás Esquerda

void setup() {
Serial.begin(9600);
}

void loop() {
  Serial.print("idle.");
  Serial.print(analogRead(FC));
  Serial.print(",");
  Serial.print(analogRead(FD));
  Serial.print(",");
  Serial.print(analogRead(FE));
  Serial.print(",");
  Serial.print(analogRead(TC));
  Serial.print(",");
  Serial.print(analogRead(TD));
  Serial.print(",");
  Serial.print(analogRead(TE));
  Serial.println();
  delay(100);
} 

void printTermometro(int input){
  for (int i =0; i<1024;i++){
    if (i<input){
      Serial.print("1");
    }else{
      Serial.print("0");
    }
    if(i<1023){
      Serial.print(",");
    }
  }
}
 
