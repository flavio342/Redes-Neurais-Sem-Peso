import numpy
import random
import math
from process_input import *
import operator

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
                #random.seed(a=42)
                r = random.choice(entradas)
                entradas.remove(r)
                indicesDeEntradasDoNeuronio.append(r)
            neuronio = self.Neuronio(indicesDeEntradasDoNeuronio)
            neuronios.append(neuronio)
        self.neuronios = neuronios
        self.label = label

    def treinarRede(self, entrada,treshHold):

        for neuronio in self.neuronios:
            coordenadaNaTabela = ""
            for i in range(len(neuronio.indicesDeEntradas)):
                if entrada[neuronio.indicesDeEntradas[i]] >= treshHold:
                    coordenadaNaTabela += '1'
                else:
                    coordenadaNaTabela += '0'   

            indiceNaTabelaDeDados = int(coordenadaNaTabela, 2)
            
            neuronio.tabelaDeDados[indiceNaTabelaDeDados] += 1

    def definirBleaching(self):
        somaHits = 0
        nHits = 0
        for neuronio in self.neuronios:
            for i in range(0,len(neuronio.tabelaDeDados)):
                somaHits += neuronio.tabelaDeDados[i]
                if(neuronio.tabelaDeDados[i] > 0):
                    nHits+=1
        return somaHits/nHits

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

        
        somaDosPixels = 0
        nOfPixels = 0
        for i in range(0,len(pixelsArray)):
            somaDosPixels+=pixelsArray[i]
            if(pixelsArray[i] >0):
                nOfPixels+=1

        treshHold = math.sqrt(somaDosPixels/nOfPixels)

        redes[str(label)].treinarRede(pixelsArray,treshHold)

        if(k%1000==0):
            print 'rede ' + str(label) + ' treinada. n = ' + str(k)

    return redes

def definirBleachingDasRedes(redes):

    somaBleaching = 0
    for x in range(0,len(redes)):
        somaBleaching += redes[str(x)].definirBleaching()
    print 'bleaching = ' + str(somaBleaching/len(redes))
    return somaBleaching/len(redes)

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
        segundoMelhorResultado = -2
        labelDoSegundoMelhorResultado = -2

        resultadosDic = {}
        for x in range(0,len(redes)):
            resultado = redes[str(x)].testeDeEntrada(pixelsArray,limiteDoBleaching)
            resultadoDic = { str(x): resultado }
            resultadosDic.update(resultadoDic)
            if resultado > melhorResultado:
                segundoMelhorResultado = melhorResultado
                labelDoSegundoMelhorResultado = labelDoMelhorResultado
                melhorResultado = resultado
                labelDoMelhorResultado = redes[str(x)].label
            elif resultado > segundoMelhorResultado:
                segundoMelhorResultado = resultado
                labelDoSegundoMelhorResultado = redes[str(x)].label
        error = float(segundoMelhorResultado)/melhorResultado

        resultadosDic = sorted(resultadosDic.items(), key=operator.itemgetter(1))
        
        correto = 'false'
        corretude = 0
        if label == labelDoMelhorResultado:
            correto = 'true'
            numeroDeAnalisesCorretas+=1
        corretude = 1. - float(segundoMelhorResultado)/melhorResultado
        numeroDeAnalises+=1
        if(k%100==0):
            print resultadosDic
            print  str(k) + ' - Correto = ' + correto + '. probabilidade = ' + str(corretude) + '.  (' + str(labelDoMelhorResultado) + '/' + str(label) + '/' + str(labelDoSegundoMelhorResultado) + ')'
            print '\n'
    
    print 'resultado'
    print str(numeroDeAnalisesCorretas) + '/' + str(numeroDeAnalises) + ' = ' + str(float(numeroDeAnalisesCorretas)/numeroDeAnalises)
        
        

"""testing_data = list(read(dataset='testing',path='.'))
r = random.randint(0,len(testing_data))
label, pixels = testing_data[r]
show(pixels)"""


redes = criarRedes(784,17)

redes = treinarRedes(redes)

limiteDoBleaching = definirBleachingDasRedes(redes)

testarRedes(redes,limiteDoBleaching)



