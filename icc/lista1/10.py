import math

x = float(input("Digite um valor: "))

sen = 0
passo = 0

for i in range(1, 21, 2):
    if(passo % 2 == 0):
        sen = sen + x**i/math.factorial(i)
    elif(passo % 2 != 0):
        sen = sen - x**i/math.factorial(i)
    passo += 1

print(sen)