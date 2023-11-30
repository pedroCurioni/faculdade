CC = gcc
CFLAGS = -I./include -g
MAIN = ./src/main.c
ARQUIVO = ./src/arquivo.c
CAIXA = ./src/caixa.c
CARRINHO = ./src/carrinho.c
CLIENTE = ./src/cliente.c
CRIPTOGRAFIA = ./src/criptografia.c
INTERFACE = ./src/interface.c
PRODUTO = ./src/produto.c
UTILS = ./src/utils.c

all: loja

loja: $(MAIN) $(ARQUIVO) $(CAIXA) $(CARRINHO) $(CLIENTE) $(CRIPTOGRAFIA) $(INTERFACE) $(PRODUTO) $(UTILS)
	$(CC) $(CFLAGS) -o loja.exe $^

clean:
	rm -f loja
