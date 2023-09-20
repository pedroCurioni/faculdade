import sys

numeros = []
maior = -sys.maxsize
menor = sys.maxsize
for i in range(30):
    numeros.append(float(input('Digite um numero: ')))
    if(maior < numeros[i]):
        maior = numeros[i]
    elif(menor > numeros[i]):
        menor = numeros[i]
print('Maior: ', maior)
print('Menor: ', menor)