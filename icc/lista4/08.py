def lideranca(vitorias, empates, gols):
    pontuacao = []
    for i in range(2):
        pontuacao.append(vitorias[i]*3 + empates[i]*1)
    if(pontuacao[0] > pontuacao[1]):
        return 1
    elif(pontuacao[1] > pontuacao[0]):
        return 2
    elif(pontuacao[0] == pontuacao[1]):
        if(gols[0] > gols[1]):
            return 1
        elif(gols[1] > gols[0]):
            return 2
        else:
            return 1

vitorias =[]
empates = []
gols = []

for i in range(2):
    vitoria  = int(input('Digite a quantidade de vitorias to time ' + str(i)+ ": "))
    vitorias.append(vitoria)

    empate = int(input('Digite a quantidade de empates to time ' + str(i) + ": "))
    empates.append(empate)

    gol = int(input('Digite a quantidade de gols to time ' + str(i) + ": "))
    gols.append(gol)
    

print(lideranca(vitorias, empates, gols))