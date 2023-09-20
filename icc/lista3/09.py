def erroPercentual(raio):
    compReal = 2*3.14159265*raio
    compAprox = 2*3*raior
    resultado = ((compReal - compAprox)/compReal) * 100
    return resultado


raio = int(input('Digite o valor do raio: '))
print(f'O erro percentual e: {erroPercentual(raio)}')
