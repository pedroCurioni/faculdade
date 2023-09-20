def PotenciaDe2(numero):
    while numero != 1:
        if numero % 2:
            return False
        numero /= 2
    return True


numero = int(input("Digite um numero: "))
print(PotenciaDe2(numero))