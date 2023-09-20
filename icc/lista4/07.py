def mediaEntre2(numeros):
    if(numeros[0] > numeros[2] and numeros[1] > numeros[2]):
        return (numeros[0]+numeros[1])/2
    elif(numeros[0] > numeros[1] and numeros[2] > numeros[1]):
        return (numeros[0]+numeros[2])/2
    elif(numeros[1] > numeros[0] and numeros[2] > numeros[0]):
        return (numeros[1]+numeros[2])/2


numeros = []
for i in range(3):
    numero = float(input("Digite um numero: "))
    numeros.append(numero)

print(mediaEntre2(numeros))
