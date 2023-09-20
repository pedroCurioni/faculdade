import sys

n = []
menor = sys.maxsize
for i in range(3):
    n.append(float(input('Digite um numero: ')))
    if(menor > n[i]):
        menor = n[i]
print('O menor numero e:', menor)
