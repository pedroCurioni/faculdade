def tabuada(numero):
    multiplicador = 1
    tabuadaList = []
    while(multiplicador <= 9):
        tabuadaList.append(numero, "*", multiplicador, "=", numero * multiplicador)
        multiplicador += 1
    return tabuadaList

numero = int(input("Digite um numero: "))

tabuadaDoNumero = tabuada(numero)