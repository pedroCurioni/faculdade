import math


def calcularRaio(raio):
    return math.pi * (raio**2)

raio = float(input("Digite o raio do circulo: "))

print(calcularRaio(raio))