#include "treino_data.h"

Rede** criarRedes(){
  String keys[5] = {"front","back","left","right","idle"};
  Rede* redes[5];
  for(short i=0;i<5;i++){
    Rede* rede = new Rede();
    rede->CriarRede(keys[i]);
    redes[i] = rede;
  }
  return redes;
}

short definirBleachingDasRedes(Rede** redes){
  short somaBleaching = 0;
  for(short i=0;i<5;i++){
    somaBleaching += redes[i]->definirBleaching();
  }
  return somaBleaching/5;
}

String testarRedes(Rede** redes, short limiteDoBleaching, short* entrada){
  short melhorResultado = -1;
  String labelDoMelhorResultado = "";
  for(short i=0;i<5;i++){
    short resultado = redes[i]->testeDeEntrada(entrada,limiteDoBleaching);
    if(resultado>melhorResultado){
      melhorResultado = resultado;
      labelDoMelhorResultado = redes[i]->label;
    }
  }
  return labelDoMelhorResultado;
}

