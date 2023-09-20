def funcaoMultipla(x):
	if 0 < x <= 1:
		y = 4*x
		equacao = 'y = 4x'
	elif 1 < x <= 2:
		y = (8*(x**2)) - (20*x) + 16
		equacao = 'y = 8x^2 - 20x + 16'
	elif 2 < x < 5:
		y = (x**3) - (10*(x**2)) + (32.25*x) - 24.5
		equacao = 'y = x^3 - 10x^2 + 32.25x - 24.5'
	elif 5 <= x < 7:
		y = 13
		equacao = 'y = 13'
	elif x >= 7:
		y = -x + 20
		equacao = '-x + 20'
	return equacao, y


x = float(input('Digite um valor: '))
print(funcaomultipla(x))
