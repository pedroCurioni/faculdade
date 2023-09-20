def corDaCasa(linhas, colunas):
    if(linhas % 2 == 0 and colunas % 2 == 0):
        return 1
    elif(linhas % 2 != 0 and colunas % 2 != 0):
        return 1
    else:
        return 0


linhas = int(input("Digite a quantidade de linhas: "))
colunas = int(input("Digite a quantidade de colunas: "))

print(corDaCasa(linhas, colunas))
