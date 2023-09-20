import math


def areaSecaoCircular(raio, angulo):
    return (angulo * math.pi * (raio**2))/360

raio = float(input("Digite o raio do circulo: "))
angulo = int(input("Digite o angulo do circulo: "))

print(areaSecaoCircular(raio, angulo))