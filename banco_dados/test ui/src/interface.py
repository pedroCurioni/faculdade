import PySimpleGUI as sg

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
    obter_pedidos_maior_que_valor,
)


def adicionar(conexao, cursor, is_atendente):
    while True:
        layout = [
            [sg.Text("Adicionar dados")],
            [sg.Button("Conta")],
            [
                sg.Button("Produto")
                if not is_atendente
                else sg.Text("Você não possui permissão para adicionar um produto.")
            ],
            [sg.Button("Item no carrinho")],
            [sg.Button("Realizar pedido")],
            [sg.Button("Sair")],
        ]

        window = sg.Window("Adicionar Dados", layout)

        event, values = window.read()

        if event == sg.WIN_CLOSED or event == "Sair":
            window.close()
            break
        elif event == "Conta":
            window.close()
            adicionar_conta(conexao, cursor)
        elif event == "Produto":
            window.close()
            adicionar_produto(conexao, cursor)
        elif event == "Item no carrinho":
            window.close()
            adicionar_produto_carrinho(conexao, cursor)
        elif event == "Realizar pedido":
            window.close()
            realizar_pedido(conexao, cursor)
        else:
            print("Número invalido, escolha novamente.")


def editar(conexao, cursor, is_atendente):
    while True:
        layout = [
            [sg.Text("Alterar dados")],
            [sg.Button("Conta")],
            [
                sg.Button("Produto")
                if not is_atendente
                else sg.Text(
                    "Você não possui permissão para alterar dados de um produto."
                )
            ],
            [sg.Button("Editar quantidade de produto no carrinho")],
            [sg.Button("Editar pedido")],
            [sg.Button("Sair")],
        ]

        window = sg.Window("Alterar Dados", layout)

        event, values = window.read()

        if event == sg.WIN_CLOSED or event == "Sair":
            window.close()
            break
        elif event == "Conta":
            window.close()
            editar_conta(conexao, cursor)
        elif event == "Produto":
            window.close()
            editar_produto(conexao, cursor)
        elif event == "Editar quantidade de produto no carrinho":
            window.close()
            editar_carrinho(conexao, cursor)
        elif event == "Editar pedido":
            window.close()
            editar_pedido(conexao, cursor)
        else:
            print("Número invalido, escolha novamente.")


def remover(conexao, cursor, is_atendente):
    while True:
        layout = [
            [sg.Text("Remover dados")],
            [
                sg.Button("Conta")
                if not is_atendente
                else sg.Text("Você não possui permissão para remover uma conta.")
            ],
            [
                sg.Button("Produto")
                if not is_atendente
                else sg.Text("Você não possui permissão para remover um produto.")
            ],
            [sg.Button("Item do carrinho")],
            [sg.Button("Sair")],
        ]

        window = sg.Window("Remover Dados", layout)

        event, values = window.read()

        if event == sg.WIN_CLOSED or event == "Sair":
            window.close()
            break
        elif event == "Conta":
            window.close()
            remover_conta(conexao, cursor)
        elif event == "Produto":
            window.close()
            remover_produto(conexao, cursor)
        elif event == "Item do carrinho":
            window.close()
            remover_produto_carrinho(conexao, cursor)
        else:
            print("Número invalido, escolha novamente.")


def visualizacao(cursor):
    while True:
        layout = [
            [sg.Text("Vizualizações")],
            [sg.Button("Todos os pedidos associados a uma conta")],
            [
                sg.Button(
                    "Todos os produtos contidos em um determinado carrinho de compras"
                )
            ],
            [sg.Button("Dados (e a quantidade) dos usuários cadastrados no sistema")],
            [sg.Button("Forma de pagamento mais utilizada")],
            [sg.Button("Filtrar usuarios por bairro, cidade e estado")],
            [sg.Button("Media anual de vendas")],
            [sg.Button("Mês e ano com maior número de vendas")],
            [
                sg.Button(
                    "Usuarios que realizaram compras em todos os meses de um determinado ano"
                )
            ],
            [sg.Button("Obter vendas entre o periodo especificado")],
            [sg.Button("Obter vendas maiores que algum valor especificado")],
            [sg.Button("Sair")],
        ]

        window = sg.Window("Vizualizações", layout)

        event, values = window.read()

        if event == sg.WIN_CLOSED or event == "Sair":
            window.close()
            break
        elif event == "Todos os pedidos associados a uma conta":
            window.close()
            pedidos_por_conta(cursor)
        elif (
            event == "Todos os produtos contidos em um determinado carrinho de compras"
        ):
            window.close()
            produtos_em_carrinho(cursor)
        elif event == "Dados (e a quantidade) dos usuários cadastrados no sistema":
            window.close()
            obter_dados_usuarios(cursor)
        elif event == "Forma de pagamento mais utilizada":
            window.close()
            forma_pagamento_mais_utilizada(cursor)
        elif event == "Filtrar usuarios por bairro, cidade e estado":
            window.close()
            filtrar_usuarios_por_localizacao(cursor)
        elif event == "Media anual de vendas":
            window.close()
            calcular_media_anual_vendas(cursor)
        elif event == "Mês e ano com maior número de vendas":
            window.close()
            mes_ano_com_maior_vendas(cursor)
        elif (
            event
            == "Usuarios que realizaram compras em todos os meses de um determinado ano"
        ):
            window.close()
            usuarios_compras_todos_meses(cursor)
        elif event == "Obter vendas entre o periodo especificado":
            window.close()
            obter_pedidos_por_periodo(cursor)
        elif event == "Obter vendas maiores que algum valor especificado":
            window.close()
            obter_pedidos_maior_que_valor(cursor)
        else:
            print("Número invalido, escolha novamente.")
