import numpy
import random

hOne = [1,0,0,1,
        1,1,1,1,
        1,0,0,1,
        1,0,0,1]

hTwo = [1,0,0,1,
        1,0,0,1,
        1,1,1,1,
        1,0,0,1]

hThree = [1,0,0,1,
          1,1,1,1,
          1,1,1,1,
          1,0,0,1]

teste = [1,0,0,1,
         1,1,0,1,
         1,0,1,1,
         1,0,0,1]

class Rede:

    class Neuronio:

        def __init__(self,indicesDeEntradas):
            self.tabelaDeDados = []
            for i in range(2**len(indicesDeEntradas)):
                self.tabelaDeDados.append(0)
            self.indicesDeEntradas = indicesDeEntradas     

    def __init__(self,nTotalDeEntradas,nEntradasPorNeuronio):
        entradas = []
        for i in range(nTotalDeEntradas):
            entradas.append(i)
        neuronios = []
        for i in range(nTotalDeEntradas/nEntradasPorNeuronio):
            indicesDeEntradasDoNeuronio = []
            for j in range(nEntradasPorNeuronio):
                r = random.choice(entradas)
                entradas.remove(r)
                indicesDeEntradasDoNeuronio.append(r)
            neuronio = self.Neuronio(indicesDeEntradasDoNeuronio)
            neuronios.append(neuronio)
        self.neuronios = neuronios

    def treinarRede(self, entrada):
        for neuronio in self.neuronios:
            coordenadaNaTabela = ""
            for i in range(len(neuronio.indicesDeEntradas)):
                coordenadaNaTabela += str(entrada[neuronio.indicesDeEntradas[i]])

            indiceNaTabelaDeDados = int(coordenadaNaTabela, 2)
            
            neuronio.tabelaDeDados[indiceNaTabelaDeDados] += 1

    def testeDeEntrada(self,entrada,limiteDoBleaching):

        resultado = 0

        for neuronio in self.neuronios:
            coordenadaNaTabela = ""
            for i in range(len(neuronio.indicesDeEntradas)):
                coordenadaNaTabela += str(entrada[neuronio.indicesDeEntradas[i]])

            indiceNaTabelaDeDados = int(coordenadaNaTabela, 2)

            if (neuronio.tabelaDeDados[indiceNaTabelaDeDados] > limiteDoBleaching):
                resultado+=1
        
        print resultado
        print "\nTire suas proprias conclusoes, humano.\n\n"




rede = Rede(16,2)
rede.treinarRede(hOne)
rede.treinarRede(hTwo)
rede.treinarRede(hThree)

rede.testeDeEntrada(hOne,0)
rede.testeDeEntrada(hTwo,0)
rede.testeDeEntrada(hThree,0)
rede.testeDeEntrada(teste,0)



