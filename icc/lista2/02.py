def tabuada(numero):
    multiplicador = 1
    while(multiplicador <= 9):
        print(numero, "*", multiplicador, "=", numero * multiplicador)
        multiplicador += 1

numero = int(input("Digite um numero: "))

tabuada(numero)