def fahrenheitParaCelsius(temperaturaFahrenheit):
    return (temperaturaFahrenheit-32)/1.8
    
temperaturaFahrenheit = int(input("Digite uma temperatura em fahrenheit: "))
print(fahrenheitParaCelsius(temperaturaFahrenheit))