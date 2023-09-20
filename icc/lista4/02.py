def numeroParImpar(numero):
    if(numero == 0):
        return 0
    elif(numero%2 != 0):
        return 1
    elif(numero%2 == 0):
        return 2

numero = float(input("Digite um numero: "))

print(numeroParImpar(numero))
