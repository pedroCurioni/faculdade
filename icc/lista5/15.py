valorInicial = int(input("Digite o valor incial da PA: "))
razao = int(input("Digite a razão da PA: "))
termo = int(input("Digite o termo que tera seu valor impresso: "))

valorTermo = valorInicial + (termo - 1) * razao

print("O valor do termo na posição", termo, "e igual a", valorTermo)
