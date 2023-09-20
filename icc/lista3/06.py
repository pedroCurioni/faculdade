import math

def grauParaRadiano(angulo):
    return (angulo*math.pi)/180
    
angulo = int(input("Digite um angulo: "))
print(grauParaRadiano(angulo))