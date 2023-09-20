def mdc(a, b):
    r = 0;
    while (b != 0):
        r = a%b;
        a = b;
        b = r;
    return a;

a = int(input("Digite um numero: "))
b = int(input("Digite outro numero: "))

print(mdc(a, b))