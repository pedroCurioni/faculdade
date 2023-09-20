def modulo(numero):
    if(numero >= 0):
        return numero
    elif(numero<0):
        return -numero

numero = float(input("Digite um numero: "))

print(modulo(numero))