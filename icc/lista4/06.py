def mediaParcial(n1,n2,n3):
    if(n1 > 10 or n1 < 0 or n2 > 10 or n2 < 0 or n3 > 10 or n3 < 0):
        return -1
    media = ((0.85*(n1+n2))/2) + 0.15 * n3
    if(media >= 7):
        return 2
    if(media >= 3 and media <= 7):
        return 1
    if(media <= 3):
        return 0

n1 = float(input("Digite um numero: "))
n2 = float(input("Digite outro numero: "))
n3 = float(input("Digite outro numero: "))

print(mediaParcial(n1,n2,n3))