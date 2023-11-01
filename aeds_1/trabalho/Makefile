CC = gcc
CFLAGS = -I./include
MAIN = ./src/main.c
CLIENTE = ./src/cliente.c
INTERFACE = ./src/interface.c
PRODUTO = ./src/produto.c
UTILS = ./src/utils.c

all: loja

loja: $(MAIN) $(CLIENTE) $(INTERFACE) $(PRODUTO) $(UTILS)
	$(CC) $(CFLAGS) -o loja $^

clean:
	rm -f loja
