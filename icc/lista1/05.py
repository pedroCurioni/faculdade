def mutiplicacao(num1, num2):
    resultado = num1
    for i in range(num2 - 1):
        resultado += num1
    return resultado


num1 = int(input("Digite um numero: "))
num2 = int(input("Digite outro numero: "))

print(mutiplicacao(num1, num2))
