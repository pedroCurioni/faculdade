def conversaoTemperatura(temperatura, controle):
    if(controle == 1):
        return (temperatura*1, 8) + 32
    if(controle == 2):
        return temperatura + 273
    if(controle == 3):
        return (temperatura-32)/1.8
    if(controle == 4):
        return (temperatura-32) * (5/9) + 273
    if(controle == 5):
        return temperatura-273
    if(controle == 6):
        return (temperatura-273)*1, 8+32


temperatura = float(input("Digite uma temperatura: "))
controle = int(input("Digite o valor da conversão,\n1:Celsius-Fahrenheit,\n2:Celsius-Kelvin,\n3:Fahrenheit-Celsius,\n4:Fahrenheit-Kelvin,\n5:Kelvin-Celsius,\n6:Kelvin- Fahrenheit"))
print(conversaoTemperatura(temperatura, controle))
