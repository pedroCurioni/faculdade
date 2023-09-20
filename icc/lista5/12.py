intervalo = int(input("Digite um intervalo: "))
numPrimos = []

for divisor in range(1, intervalo + 1):
    divisores = 1
    for dividendo in range(1, int(divisor/2) + 1):
        if(divisor%dividendo == 0):
            divisores += 1
    if(divisores == 2):
        numPrimos.append(divisor)

print(numPrimos)
