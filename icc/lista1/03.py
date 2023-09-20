from math import sqrt

def raizQuadrada(numero):
    if(numero > 0):
        return sqrt(numero)
    elif(numero < 0):
        return complex(0, sqrt(-numero))
    
numero = int(input("Digite um numero: "))
print(raizQuadrada(numero))