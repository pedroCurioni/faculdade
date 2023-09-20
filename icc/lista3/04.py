from cmath import sqrt

def calculoHipotenusa(cateto1, cateto2):
    return sqrt(cateto1**2 + cateto2**2)

cateto1 = float(input("Digite um cateto do triangulo: "))
cateto2 = float(input("Digite o outro cateto do triangulo: "))

print(calculoHipotenusa(cateto1, cateto2))