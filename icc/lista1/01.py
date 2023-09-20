def main():
    valor = float(input("Digite o valor da conta: "))
    numPessoas = int(input("Digie a quantidade de pessoas: "))
    
    print(conta(numPessoas, valor))

def conta(numPessoas, valor):
    return (valor*1.10)/10

main();