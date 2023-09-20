n = []
for i in range(3):
    n.append(input('Digite um numero: '))
if(n[0] == n[1] == n[2]):
    print('3 Numeros iguais')
elif (n[0] == n[1] or n[1] == n[2] or n[0] == n[2]):
    print('2 Numeros iguais')
else:
    print('Nenhum numero igual')