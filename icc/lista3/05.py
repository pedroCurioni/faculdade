from cmath import sqrt

def calculoAreaTriangulo(hipotenusa, base):
   altura = sqrt((hipotenusa**2) - (base**2))
   return (base*altura.real)/2


hipotenusa = float(input("Digite a hipotenusa do triangulo: "))
cateto = float(input("Digite um cateto do triangulo: "))

print(calculoAreaTriangulo(hipotenusa, cateto))