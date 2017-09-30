import numpy
import random
import math
from process_input import *

class Rede:

    class Neuronio:

        def __init__(self,indicesDeEntradas):
            self.tabelaDeDados = []
            for i in range(2**len(indicesDeEntradas)):
                self.tabelaDeDados.append(0)
            self.indicesDeEntradas = indicesDeEntradas     

    def __init__(self,nTotalDeEntradas,nEntradasPorNeuronio,label):
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
        self.label = label

    def treinarRede(self, entrada):
        for neuronio in self.neuronios:
            coordenadaNaTabela = ""
            for i in range(len(neuronio.indicesDeEntradas)):
                if entrada[neuronio.indicesDeEntradas[i]] > 0:
                    coordenadaNaTabela += '1'
                else:
                    coordenadaNaTabela += '0'   

            indiceNaTabelaDeDados = int(coordenadaNaTabela, 2)
            
            neuronio.tabelaDeDados[indiceNaTabelaDeDados] += 1

    def testeDeEntrada(self,entrada,limiteDoBleaching):

        resultado = 0

        for neuronio in self.neuronios:
            coordenadaNaTabela = ""
            for i in range(len(neuronio.indicesDeEntradas)):
                if entrada[neuronio.indicesDeEntradas[i]] > 0:
                    coordenadaNaTabela += '1'
                else:
                    coordenadaNaTabela += '0' 

            indiceNaTabelaDeDados = int(coordenadaNaTabela, 2)

            if (neuronio.tabelaDeDados[indiceNaTabelaDeDados] > limiteDoBleaching):
                resultado+=1
        
        return resultado

def criarRedes(nTotalDeEntradas,nEntradasPorNeuronio):

    redes = {}
    for i in range (0,10):
        rede = { str(i): Rede(nTotalDeEntradas,nEntradasPorNeuronio,i) }
        redes.update(rede)
    
    return redes

def treinarRedes(redes):

    training_data = list(read(dataset='training',path='.'))

    for k in range(0,len(training_data)):
        label, pixels = training_data[k]
        pixelsArray = []
        for i in range(0,pixels.shape[0]):
            for j in range(0,pixels.shape[1]):
                pixelsArray.append(pixels[i,j])
        redes[str(label)].treinarRede(pixelsArray)
        print 'rede ' + str(label) + ' treinada. n = ' + str(k)

    return redes

def testarRedes(redes,limiteDoBleaching):

    testing_data = list(read(dataset='testing',path='.'))

    numeroDeAnalises = 0
    numeroDeAnalisesCorretas = 0

    for k in range(0,len(testing_data)):
        label, pixels = testing_data[k]
        pixelsArray = []
        for i in range(0,pixels.shape[0]):
            for j in range(0,pixels.shape[1]):
                pixelsArray.append(pixels[i,j])

        melhorResultado = -1
        labelDoMelhorResultado = -1
        piorResultado = 10000000000
        for x in range(0,len(redes)):
            resultado = redes[str(x)].testeDeEntrada(pixelsArray,limiteDoBleaching)
            if resultado > melhorResultado:
                melhorResultado = resultado
                labelDoMelhorResultado = redes[str(x)].label
            if resultado < piorResultado:
                piorResultado = resultado
        
        correto = 'false'
        corretude = 0
        if label == labelDoMelhorResultado:
            correto = 'true'
            corretude = float(melhorResultado-piorResultado)/melhorResultado
            numeroDeAnalisesCorretas+=1
        numeroDeAnalises+=1
        print 'teste n = ' + str(k) + '. Correto = ' + correto + '. Corretude = ' + str(float(corretude)) + '. Label indicada = ' + str(labelDoMelhorResultado) + '. Label real = ' + str(label)
    
    print 'resultado'
    print str(numeroDeAnalisesCorretas) + '/' + str(numeroDeAnalises) + ' = ' + str(float(numeroDeAnalisesCorretas)/numeroDeAnalises)
        
        


redes = criarRedes(784,9)

redes = treinarRedes(redes)

testarRedes(redes,100)
