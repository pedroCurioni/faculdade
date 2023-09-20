import math

x = float(input("Digite um valor: "))

sen = x - x**3/math.factorial(3) + x**5/math.factorial(5) +x**7/math.factorial(7) +x**9/math.factorial(9) +x**11/math.factorial(11) +x**13/math.factorial(13) + x**15/math.factorial(15) + x**17/math.factorial(17) + x**21/math.factorial(21)

print(sen)