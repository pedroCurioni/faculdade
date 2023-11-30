import os

from src.carrinho import (
    adicionar_produto_carrinho,
    editar_carrinho,
    remover_produto_carrinho,
)
from src.conta import adicionar_conta, editar_conta, remover_conta
from src.produto import adicionar_produto, editar_produto, remover_produto
from src.pedido import realizar_pedido, editar_pedido
from src.queries import (
    pedidos_por_conta,
    produtos_em_carrinho,
    obter_dados_usuarios,
    forma_pagamento_mais_utilizada,
    filtrar_usuarios_por_localizacao,
    calcular_media_anual_vendas,
    mes_ano_com_maior_vendas,
    usuarios_compras_todos_meses,
    obter_pedidos_por_periodo,
    obter_pedidos_maior_que_valor
)


def wait_key():
    input("Pressione enter para continuar.")


def clear_terminal():
    if os.name == "nt":
        # Widows
        os.system("cls")
    else:
        # Linux / Mac
        os.system("clear")


def adicionar(conexao, cursor, is_atendente):
    while True:
        clear_terminal()

        print(
            "-----Adicionar dados------\n1 - Conta\n2 - Produto\n3 - Item no carrinho\n4 - Realizar pedido\n0 - Sair"
        )
        opcao = input("Digite o número da escolha: ")

        if opcao == "0":
            break
        elif opcao == "1":
            adicionar_conta(conexao, cursor)
            wait_key()
        elif opcao == "2":
            if is_atendente:
                print("Você não possui permissão para adicionar um produto.")
                wait_key()
            else:
                adicionar_produto(conexao, cursor)
                wait_key()
        elif opcao == "3":
            adicionar_produto_carrinho(conexao, cursor)
            wait_key()
        elif opcao == "4":
            realizar_pedido(conexao, cursor)
            wait_key()
        else:
            print("Número invalido, escolha novamente.")
            wait_key()


def editar(conexao, cursor, is_atendente):
    while True:
        clear_terminal()

        print(
            "-----Alterar dados------\n1 - Conta\n2 - Produto\n3 - Editar quantidade de produto no carrinho\n4 - Editar pedido\n0 - Sair"
        )
        opcao = input("Digite o número da escolha: ")

        if opcao == "0":
            break
        elif opcao == "1":
            editar_conta(conexao, cursor)
            wait_key()
        elif opcao == "2":
            if is_atendente:
                print("Você não possui permissão para alterar dados de um produto.")
                wait_key()
            else:
                editar_produto(conexao, cursor)
                wait_key()
        elif opcao == "3":
            editar_carrinho(conexao, cursor)
            wait_key()
        elif opcao == "4":
            editar_pedido(conexao, cursor)
            wait_key()
        else:
            print("Número invalido, escolha novamente.")
            wait_key()


def remover(conexao, cursor, is_atendente):
    while True:
        clear_terminal()

        print(
            "-----Adicionar dados------\n1 - Conta\n2 - Produto\n3 - Item do carrinho\n0 - Sair"
        )
        opcao = input("Digite o número da escolha: ")

        if opcao == "0":
            break
        elif opcao == "1":
            if is_atendente:
                print("Você não possui permissão para remover uma conta.")
                wait_key()
            else:
                remover_conta(conexao, cursor)
                wait_key()
        elif opcao == "2":
            if is_atendente:
                print("Você não possui permissão para remover um produto.")
                wait_key()
            else:
                remover_produto(conexao, cursor)
                wait_key()
        elif opcao == "3":
            remover_produto_carrinho(conexao, cursor)
            wait_key()
        else:
            print("Número invalido, escolha novamente.")


def vizualicacao(cursor):
    while True:
        clear_terminal()

        print("-----Vizualizações------")
        print("1 - Todos os pedidos associados a uma conta")
        print("2 - Todos os produtos contidos em um determinado carrinho de compras")
        print("3 - Dados (e a quantidade) dos usuários cadastrados no sistema")
        print("4 - Forma de pagamento mais utilizada")
        print("5 - Filtrar usuarios por bairro, cidade e estado")
        print("6 - Media anual de vendas")
        print("7 - Mês e ano com maior número de vendas")
        print(
            "8 - Usuarios que realizaram compras em todos os meses de um determinado ano"
        )
        print(
            "9 - Obter vendas entre o periodo especificado"
        )
        print(
            "10 - Obter vendas maiores que algum valor especificado"
        )
        print("0 - Sair")

        opcao = input("Digite o número da escolha: ")

        if opcao == "0":
            break
        elif opcao == "1":
            pedidos_por_conta(cursor)
            wait_key()
        elif opcao == "2":
            produtos_em_carrinho(cursor)
            wait_key()
        elif opcao == "3":
            obter_dados_usuarios(cursor)
            wait_key()
        elif opcao == "4":
            forma_pagamento_mais_utilizada(cursor)
            wait_key()
        elif opcao == "5":
            filtrar_usuarios_por_localizacao(cursor)
            wait_key()
        elif opcao == "6":
            calcular_media_anual_vendas(cursor)
            wait_key()
        elif opcao == "7":
            mes_ano_com_maior_vendas(cursor)
            wait_key()
        elif opcao == "8":
            usuarios_compras_todos_meses(cursor)
            wait_key()
        elif opcao == "8":
            usuarios_compras_todos_meses(cursor)
            wait_key()
        elif opcao == "9":
            obter_pedidos_por_periodo(cursor)
            wait_key()
        elif opcao == "10":
            obter_pedidos_maior_que_valor(cursor)
            wait_key()
        else:
            print("Número invalido, escolha novamente.")
