import PySimpleGUI as sg
from src.conta import buscar_conta_por_id
from src.produto import buscar_produto_por_id


def buscar_carrinho_por_conta(cursor, id_conta):
    cursor.execute("SELECT * FROM Carrinho WHERE id_conta = %s", (id_conta,))
    detalhes_carrinho = cursor.fetchone()

    if detalhes_carrinho:
        return detalhes_carrinho[0]
    else:
        return None


def busca_item_carrinho(cursor, id_carrinho, id_produto):
    cursor.execute(
        "SELECT id, quantidade FROM Item WHERE id_carrinho = %s AND id_produto = %s",
        (id_carrinho, id_produto),
    )
    item = cursor.fetchone()
    if item:
        return item[0]
    else:
        return None


def criar_carrinho(connection, cursor, id_conta):
    cursor.execute("SELECT id FROM Carrinho WHERE id_conta = %s", (id_conta,))
    carrinho = cursor.fetchone()

    if carrinho:
        id_carrinho = carrinho[0]
    else:
        cursor.execute("INSERT INTO Carrinho (id_conta) VALUES (%s)", (id_conta,))
        connection.commit()

        cursor.execute("SELECT id FROM Carrinho WHERE id_conta = %s", (id_conta,))
        id_carrinho = cursor.fetchone()[0]
    return id_carrinho


def adicionar_produto_carrinho(connection, cursor):
    id_conta = buscar_conta_por_id(cursor)
    if not id_conta:
        sg.popup("Conta não encontrada.")
        return None

    id_produto = buscar_produto_por_id(cursor)
    if not id_produto:
        sg.popup("Produto não encontrado.")
        return None

    layout = [
        [sg.Text("Digite a quantidade que deseja adicionar ao carrinho: ")],
        [sg.Input(key="quantidade")],
        [sg.Button("Adicionar"), sg.Button("Cancelar")],
    ]

    window = sg.Window("Adicionar Produto ao Carrinho", layout, margins=(50,50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED or event == "Cancelar":
            window.close()
            return None

        try:
            quantidade = int(values["quantidade"])
        except ValueError:
            sg.popup("Por favor, digite um número inteiro para a quantidade.")
            continue

        break

    id_carrinho = criar_carrinho(connection, cursor, id_conta)

    id_item = busca_item_carrinho(cursor, id_carrinho, id_produto)
    if id_item:
        cursor.execute(
            "UPDATE Item SET quantidade = quantidade + %s WHERE id_carrinho = %s AND id_produto = %s",
            (quantidade, id_carrinho, id_produto),
        )
        sg.popup("Produto já estava no carrinho, sua quantidade foi aumentada.")
    else:
        cursor.execute(
            "INSERT INTO Item (quantidade, id_produto, id_carrinho) VALUES (%s, %s, %s)",
            (quantidade, id_produto, id_carrinho),
        )
        sg.popup("Produto adicionado ao carrinho com sucesso!")

    connection.commit()
    window.close()


def editar_carrinho(connection, cursor):
    id_conta = buscar_conta_por_id(cursor)
    if not id_conta:
        sg.popup("Conta não encontrada.")
        return None

    id_produto = buscar_produto_por_id(cursor)
    if not id_produto:
        sg.popup("Produto não encontrado.")
        return None

    layout = [
        [sg.Text("Digite a nova quantidade para o produto no carrinho: ")],
        [sg.Input(key="nova_quantidade")],
        [sg.Button("Editar"), sg.Button("Cancelar")],
    ]

    window = sg.Window("Editar Quantidade no Carrinho", layout, margins=(50,50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED or event == "Cancelar":
            window.close()
            return None

        try:
            nova_quantidade = int(values["nova_quantidade"])
        except ValueError:
            sg.popup("Por favor, digite um número inteiro para a nova quantidade.")
            continue

        break

    id_carrinho = criar_carrinho(connection, cursor, id_conta)
    id_item = busca_item_carrinho(cursor, id_carrinho, id_produto)

    if not id_item:
        sg.popup("Produto não está no carrinho.")
        return None

    if nova_quantidade > 0:
        cursor.execute(
            "UPDATE Item SET quantidade = %s WHERE id = %s", (nova_quantidade, id_item)
        )
        connection.commit()
        sg.popup("Quantidade do item no carrinho atualizada com sucesso!")
    else:
        remover_produto_carrinho(connection, cursor, id_conta, id_produto)
        sg.popup("Item removido do carrinho, pois a quantidade foi ajustada para zero.")

    window.close()


def remover_produto_carrinho(connection, cursor):
    id_conta = buscar_conta_por_id(cursor)
    if not id_conta:
        sg.popup("Conta não encontrada.")
        return None

    id_produto = buscar_produto_por_id(cursor)
    if not id_produto:
        sg.popup("Produto não encontrado.")
        return None

    id_carrinho = criar_carrinho(connection, cursor, id_conta)
    id_item = busca_item_carrinho(cursor, id_carrinho, id_produto)

    if not id_item:
        sg.popup("Produto não está no carrinho.")
        return None

    cursor.execute("DELETE FROM Item WHERE id = %s", (id_item,))
    connection.commit()
    sg.popup("Produto removido do carrinho!")
