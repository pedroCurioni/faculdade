import PySimpleGUI as sg
from datetime import datetime
from src.carrinho import buscar_carrinho_por_conta


def get_status_pedido():
    layout = [
        [sg.Text("Escolha uma opção para o novo status do pedido:")],
        [
            sg.Radio("Em Processamento", "RADIO1", key="Em Processamento"),
            sg.Radio("Cancelado", "RADIO1", key="Cancelado"),
            sg.Radio("Confirmado", "RADIO1", key="Confirmado"),
            sg.Radio("Pago", "RADIO1", key="Pago"),
            sg.Radio("Enviado", "RADIO1", key="Enviado"),
            sg.Radio("Em Trânsito", "RADIO1", key="Em Trânsito"),
            sg.Radio("Não alterar", "RADIO1", key="Não alterar"),
        ],
        [sg.Button("OK")],
    ]

    window = sg.Window("Escolha o Status do Pedido", layout, margins=(50,50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "OK":
            selected_option = None
            for key in ["Em Processamento", "Cancelado", "Confirmado", "Pago", "Enviado", "Em Trânsito", "Não alterar"]:
                if values[key]:
                    selected_option = key
                    break
            window.close()
            return selected_option


def buscar_pedido_por_id(cursor):
    layout = [
        [
            sg.Text("Digite o ID do pedido que deseja buscar: "),
            sg.Input(key="id_pedido"),
        ],
        [sg.Button("Buscar")],
    ]

    window = sg.Window("Buscar Pedido por ID", layout, margins=(50,50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Buscar":
            try:
                id_pedido = int(values["id_pedido"])
                window.close()
                cursor.execute("SELECT * FROM Pedido WHERE id = %s", (id_pedido,))
                pedido = cursor.fetchone()

                if pedido:
                    return id_pedido
                else:
                    # Pedido não encontrado
                    return None
            except ValueError:
                sg.popup("Por favor, digite um número inteiro para o ID do pedido.")


def atualizar_id_pedido_em_items(cursor, id_pedido, itens_carrinho):
    for item in itens_carrinho:
        query_atualizar_item = (
            "UPDATE Item SET id_pedido = %s, id_carrinho = NULL WHERE id = %s"
        )
        values_atualizar_item = (id_pedido, item[0])
        cursor.execute(query_atualizar_item, values_atualizar_item)


def atualizar_total_pedido(cursor, id_pedido):
    query_total_pedido = "SELECT SUM(quantidade * preco) FROM Item JOIN Produto ON Item.id_produto = Produto.id WHERE id_pedido = %s"
    cursor.execute(query_total_pedido, (id_pedido,))
    total_pedido = cursor.fetchone()[0]

    query_atualizar_total_pedido = "UPDATE Pedido SET total = %s WHERE id = %s"
    values_atualizar_total_pedido = (total_pedido, id_pedido)
    cursor.execute(query_atualizar_total_pedido, values_atualizar_total_pedido)


def realizar_pagamento(cursor, id_pedido):
    layout = [
        [sg.Text("Informe a forma de pagamento: "), sg.Input(key="forma_pagamento")],
        [
            sg.Text("Informe a quantidade de vezes para o pagamento: "),
            sg.Input(key="vezes_pagamento"),
        ],
        [sg.Button("OK")],
    ]

    window = sg.Window("Realizar Pagamento", layout, margins=(50,50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "OK":
            forma_pagamento = values.get("forma_pagamento", "")
            vezes_pagamento = values.get("vezes_pagamento", "")

            if (
                not forma_pagamento
                or not vezes_pagamento.isdigit()
                or int(vezes_pagamento) < 1
            ):
                sg.popup("Por favor, preencha todas as informações corretamente.")
                continue

            break

    query_pagamento = "INSERT INTO Pagamento (id_pedido, forma) VALUES (%s, %s)"
    values_pagamento = (id_pedido, forma_pagamento)
    cursor.execute(query_pagamento, values_pagamento)

    for i in range(int(vezes_pagamento) - 1):
        cursor.execute(query_pagamento, values_pagamento)
    
    window.close()


def realizar_pedido(connection, cursor):
    data_pedido = datetime.now()

    layout = [
        [
            sg.Text("Digite o ID da conta para realizar o pedido: "),
            sg.Input(key="id_conta"),
        ],
        [sg.Button("Realizar Pedido")],
    ]

    window = sg.Window("Realizar Pedido", layout, margins=(50,50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Realizar Pedido":
            try:
                id_conta = int(values["id_conta"])
            except ValueError:
                sg.popup("Por favor, digite um número inteiro para o ID da conta.")
                continue

            break

    query_pedido = "INSERT INTO Pedido (data_pedido, status_pedido, total, id_conta) VALUES (%s, %s, %s, %s)"
    values_pedido = (data_pedido, "Em Processamento", 0, id_conta)
    cursor.execute(query_pedido, values_pedido)

    id_pedido = cursor.lastrowid

    id_carrinho = buscar_carrinho_por_conta(cursor, id_conta)
    if not id_carrinho:
        sg.popup("Conta não possui um carrinho, adicione itens primeiro.")
        return None

    query_itens = "SELECT * FROM Item WHERE id_carrinho = %s"
    cursor.execute(query_itens, (id_carrinho,))
    itens_carrinho = cursor.fetchall()
    if not itens_carrinho:
        sg.popup("Carrinho vazio. Não é possível realizar o pedido.")
        return None

    atualizar_id_pedido_em_items(cursor, id_pedido, itens_carrinho)
    atualizar_total_pedido(cursor, id_pedido)
    realizar_pagamento(cursor, id_pedido)

    connection.commit()
    sg.popup("Pedido realizado com sucesso!")
    window.close()


def editar_pedido(connection, cursor):
    id_pedido = buscar_pedido_por_id(cursor)
    if not id_pedido:
        sg.popup("Pedido não encontrado.")
        return None

    novo_status = get_status_pedido()

    query_pedido = "UPDATE Pedido SET "
    params_pedido = []

    if novo_status:
        query_pedido += "status_pedido = %s"
        params_pedido.append(novo_status)

    query_pedido = query_pedido.rstrip(", ") + " WHERE id = %s"
    params_pedido.append(id_pedido)

    if len(params_pedido) > 1:
        cursor.execute(query_pedido, tuple(params_pedido))
        connection.commit()
        sg.popup("Status do pedido atualizado com sucesso.")
