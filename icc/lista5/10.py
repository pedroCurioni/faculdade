def main():
    numero = int(input("Digite um numero para que seja calculado seu fatorial: "))
    print("O fatorial de", numero, "e5", fatorial(numero))

def fatorial(numero):
    if (numero == 1):
        return numero
    else:
        return numero * fatorial(numero - 1)

main()

