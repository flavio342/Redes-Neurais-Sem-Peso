import numpy
import random
import math
from process_input import *
import operator
import math

class Rede:

    class Neuronio:

        def __init__(self,indicesDeEntradas):
            """self.tabelaDeDados = []
            for i in range(2**len(indicesDeEntradas)):
                self.tabelaDeDados.append(0)"""
            self.indicesDeEntradas = indicesDeEntradas
            self.tabelaDeDados = {}

        def setTabelaDeDados(self,tabelaDeDados):
            self.tabelaDeDados = tabelaDeDados

        def setIndicesDeEntradas(self,indicesDeEntradas):
            self.indicesDeEntradas = indicesDeEntradas
            

    def __init__(self,nTotalDeEntradas,nEntradasPorNeuronio,label):
        random.seed(1)
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

    def treinarRede(self, entrada,treshHold):

        for neuronio in self.neuronios:
            coordenadaNaTabela = ""
            for i in range(len(neuronio.indicesDeEntradas)):
                if entrada[neuronio.indicesDeEntradas[i]] >= treshHold:
                    coordenadaNaTabela += '1'
                else:
                    coordenadaNaTabela += '0'   

            if coordenadaNaTabela in neuronio.tabelaDeDados:
                neuronio.tabelaDeDados[coordenadaNaTabela] = neuronio.tabelaDeDados[coordenadaNaTabela] + 1
            else:
                hit = { coordenadaNaTabela : 1 }
                neuronio.tabelaDeDados.update(hit)

            """indiceNaTabelaDeDados = int(coordenadaNaTabela, 2)
            
            neuronio.tabelaDeDados[indiceNaTabelaDeDados] += 1"""

    def definirBleaching(self):
        somaHits = 0
        nHits = 0
        for neuronio in self.neuronios:
            for key in neuronio.tabelaDeDados:
                somaHits += neuronio.tabelaDeDados[key]
                if(neuronio.tabelaDeDados[key] > 0):
                    nHits+=1
            
            """for i in range(0,len(neuronio.tabelaDeDados)):
                somaHits += neuronio.tabelaDeDados[i]
                if(neuronio.tabelaDeDados[i] > 0):
                    nHits+=1"""
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


            if coordenadaNaTabela in neuronio.tabelaDeDados:
           
                if neuronio.tabelaDeDados[coordenadaNaTabela] > limiteDoBleaching:
                    resultado+=1

            """indiceNaTabelaDeDados = int(coordenadaNaTabela, 2)

            if (neuronio.tabelaDeDados[indiceNaTabelaDeDados] > limiteDoBleaching):
                resultado+=1"""
        
        return resultado

def criarRedes(nTotalDeEntradas,nEntradasPorNeuronio):

    redes = {}

    keys = ["front","back","left","right","idle"]
    for key in keys:
        rede = { key : Rede(nTotalDeEntradas,nEntradasPorNeuronio,key) }
        redes.update(rede)

    return redes

def treinarRedes(redes, training_data):

    #training_data = list(read(dataset='training',path='.'))

    for k in range(0,len(training_data)):
        label, pixels = training_data[k]

        """pixelsArray = []
        for i in range(0,pixels.shape[0]):
            for j in range(0,pixels.shape[1]):
                pixelsArray.append(pixels[i,j])"""

        pixelsArray = pixels
        
        somaDosPixels = 0
        nOfPixels = 0
        for i in range(0,len(pixelsArray)):
            somaDosPixels+=pixelsArray[i]
            if(pixelsArray[i] >0):
                nOfPixels+=1

        treshHold = math.sqrt(somaDosPixels/nOfPixels)

        redes[str(label)].treinarRede(pixelsArray,treshHold)

        

    f = open("rede_treinada.txt","w") 
    for key in redes:
        j = 0
        for neuronio in redes[key].neuronios:
            f.write(key + "." + str(j) + "\n")
            for i in range(0,len(neuronio.indicesDeEntradas)):
                f.write(str(neuronio.indicesDeEntradas[i]) + ".")
            f.write("\n")
            j+=1
            for tabelaKey in neuronio.tabelaDeDados:
                f.write(tabelaKey + "." + str(neuronio.tabelaDeDados[tabelaKey]) + "\n")
            f.write("-\n")
    f.write("--")
    f.close()

    return redes

def treinarRedesArduino(redes, training_data):

    #training_data = list(read(dataset='training',path='.'))

    for k in range(0,len(training_data)):
        label, pixels = training_data[k]

        """pixelsArray = []
        for i in range(0,pixels.shape[0]):
            for j in range(0,pixels.shape[1]):
                pixelsArray.append(pixels[i,j])"""

        pixelsArray = pixels
        
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
            
    keys = {"front" : 0,"back":1,"left":2,"right":3,"idle":4}
    
    f = open("rede_treinada_arduino.txt","w")
    f.write("const PROGMEM String labels[5] = {\"front\",\"back\",\"left\",\"right\",\"idle\"};\n")
    f.write("const PROGMEM int nNeuronios[] = {" + str(nNeuronios) + "};\n")
    f.write("const PROGMEM int nIndicesDeEntradas[] = {" + str(nIndicesDeEntradas) + "};\n")
    
    indicesDeEntradas = "const PROGMEM int indicesDeEntradas[5][" + str(nNeuronios) + "][" + str(nIndicesDeEntradas) + "] = {"
    nDados = "const PROGMEM int nDados[5][" + str(nNeuronios) + "] = {"

    bigNTabelaDeDados = -1
    for key in redes:
        for neuronio in redes[key].neuronios:
            if len(neuronio.tabelaDeDados) > bigNTabelaDeDados:
                bigNTabelaDeDados = len(neuronio.tabelaDeDados)
    
    tabelaDeDadosKeys = "const PROGMEM long long int tabelaDeDadosKeys[5][" + str(nNeuronios) + "][" + str(bigNTabelaDeDados) + "] = {"
    tabelaDeDadosValues = "const PROGMEM int tabelaDeDadosValues[5][" + str(nNeuronios) + "][" + str(bigNTabelaDeDados) + "]= {"
    
    for r, key in enumerate(redes):
        j = 0
        indicesDeEntradas+="{"
        nDados+="{"
        tabelaDeDadosKeys+="{"
        tabelaDeDadosValues+="{"
        for neuronio in redes[key].neuronios:
            
            indicesDeEntradas+="{"
            for i in range(0,len(neuronio.indicesDeEntradas)):
                indicesDeEntradas+= str(neuronio.indicesDeEntradas[i])
                if(i<len(neuronio.indicesDeEntradas)-1):
                    indicesDeEntradas+=","
            indicesDeEntradas+="}"
            if j < len(redes[key].neuronios)-1:
                indicesDeEntradas+=","

            nDados+= str(len(neuronio.tabelaDeDados))
            if j < len(redes[key].neuronios)-1:
                nDados+=","
            
            k=0
            tabelaDeDadosKeys+="{"
            for tabelaKey in neuronio.tabelaDeDados:
                tabelaDeDadosKeys+= str(int(tabelaKey, 2))
                if(k<bigNTabelaDeDados-1):
                    tabelaDeDadosKeys+=","
                k+=1   
            for x in range(k,bigNTabelaDeDados):
                tabelaDeDadosKeys+="0"
                if(x<bigNTabelaDeDados-1):
                    tabelaDeDadosKeys+=","
            k=0

            tabelaDeDadosKeys+="}"
            if j < len(redes[key].neuronios)-1:
                tabelaDeDadosKeys+=","
            
            tabelaDeDadosValues+="{"
            for tabelaKey in neuronio.tabelaDeDados:
                tabelaDeDadosValues+= str(neuronio.tabelaDeDados[tabelaKey])
                if(k<bigNTabelaDeDados-1):
                    tabelaDeDadosValues+=","
                k+=1
            for x in range(k,bigNTabelaDeDados):
                tabelaDeDadosValues+="0"
                if(x<bigNTabelaDeDados-1):
                    tabelaDeDadosValues+=","

            tabelaDeDadosValues+="}"
            if j < len(redes[key].neuronios)-1:
                tabelaDeDadosValues+=","
          
            j+=1

        nDados+="}"    
        indicesDeEntradas+="}"
        tabelaDeDadosKeys+="}"
        tabelaDeDadosValues+="}"
        if r < 4:
            nDados+=","
            indicesDeEntradas+=","
            tabelaDeDadosKeys+=","
            tabelaDeDadosValues+=","

     
    indicesDeEntradas+="};\n"
    nDados+="};\n"
    tabelaDeDadosKeys+="};\n"
    tabelaDeDadosValues+="};\n"
    f.write(indicesDeEntradas)
    f.write(nDados)
    f.write(tabelaDeDadosKeys)
    f.write(tabelaDeDadosValues)
    f.close()

    return redes
    
    

def definirBleachingDasRedes(redes):

    somaBleaching = 0
    keys = ["front","back","left","right","idle"]
    for key in keys:
        somaBleaching += redes[key].definirBleaching()
    print 'bleaching = ' + str(somaBleaching/len(redes))
    return somaBleaching/len(redes)

def testarRedes(redes,limiteDoBleaching,testing_data):

    #testing_data = list(read(dataset='testing',path='.'))

    numeroDeAnalises = 0
    numeroDeAnalisesCorretas = 0

    for k in range(0,len(testing_data)):
        label, pixels = testing_data[k]
        """pixelsArray = []
        for i in range(0,pixels.shape[0]):
            for j in range(0,pixels.shape[1]):
                pixelsArray.append(pixels[i,j])"""

        pixelsArray = pixels

        melhorResultado = -1
        labelDoMelhorResultado = -1
        segundoMelhorResultado = -2
        labelDoSegundoMelhorResultado = -2

        resultadosDic = {}
        keys = ["front","back","left","right","idle"]
        for key in keys:
            resultado = redes[key].testeDeEntrada(pixelsArray,limiteDoBleaching)
           
            resultadoDic = { key: resultado }
            resultadosDic.update(resultadoDic)
            if resultado > melhorResultado:
                segundoMelhorResultado = melhorResultado
                labelDoSegundoMelhorResultado = labelDoMelhorResultado
                melhorResultado = resultado
                labelDoMelhorResultado = redes[key].label
            elif resultado > segundoMelhorResultado:
                segundoMelhorResultado = resultado
                labelDoSegundoMelhorResultado = redes[key].label
        if melhorResultado != 0:
            error = float(segundoMelhorResultado)/melhorResultado
        else:
            error = 1

        resultadosDic = sorted(resultadosDic.items(), key=operator.itemgetter(1))
        
        correto = 'false'
        corretude = 0
        if label == labelDoMelhorResultado:
            correto = 'true'
            numeroDeAnalisesCorretas+=1
        if melhorResultado != 0:
            corretude = 1. - float(segundoMelhorResultado)/melhorResultado
        else:
            corretude = 1
        numeroDeAnalises+=1
      
    
    print 'resultado'
    print str(numeroDeAnalisesCorretas) + '/' + str(numeroDeAnalises) + ' = ' + str(float(numeroDeAnalisesCorretas)/numeroDeAnalises)
        
def treinarRedesDoArquivo(redes):
    f = open("rede_treinada.txt", "r")
    line = f.readline()
    while(line != "--"):
        data = line.split(".")
        rede = data[0]
        neuronio = int(data[1].split("\n")[0])
        line = f.readline()
        data = line.split(".")
        indicesDeEntradas = []
        for i in range(0,len(data)):
            if data[i] != "" and data[i] != "\n" :
                indicesDeEntradas.append(int(data[i]))
        
        line = f.readline()
        tabelaDeDados = {}
        while(line!="-\n"):
            data = line.split(".")
            indice = data[0]
            hits = int(data[1].split("\n")[0])
            dado = { indice : hits }
            tabelaDeDados.update(dado)
            line = f.readline()
   
        redes[rede].neuronios[neuronio].setIndicesDeEntradas(indicesDeEntradas)
        redes[rede].neuronios[neuronio].setTabelaDeDados(tabelaDeDados)
        line = f.readline()
    
    return redes

def lerInput(name):
    f = open(name + ".txt","r")
    line = f.readline()
    inputArray = []
    count = 0
    while(line != "-"):
        data = line.split(".")
     
        label = data[0]
        values = data[1]
        values = values.split(",")
        v = []
        for i in range(0,len(values)):
            for j in range(0,rawInputSize):
                if j < int(values[i])/rawInputFactor:
                    v.append(1)
                else:
                    v.append(0)
        inputArray.append((label,v))
        count+=1
        line = f.readline()
    return inputArray        
        
def inputTest():
    values = [405,679,763,486,759,789]
    v = []
    inputArray = []
    for i in range(0,len(values)):
        for j in range(0,rawInputSize):
            if j < int(values[i])/rawInputFactor:
                v.append(1)
            else:
                v.append(0)
    inputArray.append(("back",v))
    vs = ""
    for i in range(0,len(v)):
        vs += str(v[i])
    return inputArray
    
    

"""testing_data = list(read(dataset='testing',path='.'))
r = random.randint(0,len(testing_data))
label, pixels = testing_data[r]
show(pixels)"""

rawInputSize = 32
rawInputFactor = 32
nTotalEntradas = rawInputSize*6    
nIndicesDeEntradas = 25
nNeuronios = nTotalEntradas/nIndicesDeEntradas


mode = "a"



redes = criarRedes(nTotalEntradas,nIndicesDeEntradas)

if mode == "debug":
    inputArray = inputTest()
    redes = treinarRedesDoArquivo(redes)
    limiteDoBleaching = definirBleachingDasRedes(redes)
    testarRedes(redes,limiteDoBleaching,inputArray)
elif mode == "a":
    inputArray = lerInput("treina")
    redes = treinarRedesArduino(redes,inputArray)
elif mode != "test":
    inputArray = lerInput("treina")
    redes = treinarRedes(redes,inputArray)
    limiteDoBleaching = definirBleachingDasRedes(redes)
    testarRedes(redes,limiteDoBleaching,inputArray)
else:
    inputArray = lerInput("teste")
    redes = treinarRedesDoArquivo(redes)
    limiteDoBleaching = definirBleachingDasRedes(redes)
    testarRedes(redes,limiteDoBleaching,inputArray)





