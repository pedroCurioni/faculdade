import PySimpleGUI as sg
from datetime import datetime


def pedidos_por_conta(cursor):
    layout = [
        [sg.Text("Digite o ID da conta: "), sg.Input(key="id_conta")],
        [sg.Button("Buscar Pedidos")],
    ]

    window = sg.Window("Pedidos por Conta", layout)

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Buscar Pedidos":
            id_conta = values["id_conta"]

            if id_conta == "":
                sg.popup("Por favor, preencha as informações.")
                continue

            cursor.execute(
                """
                SELECT *
                FROM Pedido
                WHERE id_conta = %s
            """,
                (id_conta,),
            )

            resultados = cursor.fetchall()

            if resultados:
                formatted_results = [f"ID: {row[0]}, Data: {row[1]}, Status: {row[2]}, Total: {row[3]}" for row in resultados]
                sg.popup(f"Pedidos associados à conta {id_conta}:", *formatted_results)
            else:
                sg.popup(f"Nenhum pedido encontrado para a conta {id_conta}.")

            window.close()
            break


def produtos_em_carrinho(cursor):
    layout = [
        [sg.Text("Digite o ID do carrinho desejado: "), sg.Input(key="id_carrinho")],
        [sg.Button("Buscar Produtos")],
    ]

    window = sg.Window("Produtos em Carrinho", layout)

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Buscar Produtos":
            id_carrinho = values["id_carrinho"]

            if id_carrinho == "":
                sg.popup("Por favor, preencha as informações.")
                continue

            cursor.execute(
                """
                SELECT P.id, P.nome, P.preco, I.quantidade
                FROM Item I
                JOIN Produto P ON I.id_produto = P.id
                WHERE I.id_carrinho = %s
            """,
                (id_carrinho,),
            )

            resultados = cursor.fetchall()

            if resultados:
                formatted_results = [f"ID: {row[0]}, Nome: {row[1]}, Preço: {row[2]}, Quantidade: {row[3]}" for row in resultados]
                sg.popup(f"Produtos no carrinho (id_carrinho {id_carrinho}):", *formatted_results)
            else:
                sg.popup(
                    f"Nenhum produto encontrado no carrinho (id_carrinho {id_carrinho})."
                )

            window.close()
            break


def obter_dados_usuarios(cursor):
    cursor.execute(
        """
        SELECT id, nome, cidade, estado, bairro
        FROM Conta
    """
    )

    resultados = cursor.fetchall()

    if resultados:
        formatted_results = [f"ID: {row[0]}, Nome: {row[1]}, Cidade: {row[2]}, Estado: {row[3]}, Bairro: {row[4]}" for row in resultados]
        sg.popup(f"Quantidade total de usuários cadastrados: {len(resultados)}", "Dados dos usuários:", *formatted_results)

    else:
        sg.popup("Nenhum usuário cadastrado.")


def forma_pagamento_mais_utilizada(cursor):
    query = """
        SELECT forma, COUNT(*) AS quantidade
        FROM Pagamento
        GROUP BY forma
        ORDER BY quantidade DESC
        LIMIT 1
    """
    cursor.execute(query)
    forma_pagamento_mais_utilizada = cursor.fetchone()

    if forma_pagamento_mais_utilizada:
        forma, quantidade = forma_pagamento_mais_utilizada
        sg.popup(
            f"A forma de pagamento mais utilizada é '{forma}' com {quantidade} transações."
        )
        return forma_pagamento_mais_utilizada
    else:
        sg.popup("Nenhuma forma de pagamento encontrada no sistema.")
        return None


def filtrar_usuarios_por_localizacao(cursor):
    layout = [
        [
            sg.Text(
                "Digite o estado desejado (ou deixe em branco para manter a atual): "
            ),
            sg.Input(key="estado"),
        ],
        [
            sg.Text(
                "Digite a cidade desejada (ou deixe em branco para manter a atual): "
            ),
            sg.Input(key="cidade"),
        ],
        [
            sg.Text(
                "Digite o bairro desejado (ou deixe em branco para manter a atual): "
            ),
            sg.Input(key="bairro"),
        ],
        [sg.Button("Filtrar")],
    ]

    window = sg.Window("Filtrar Usuários por Localização", layout)

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Filtrar":
            estado = values["estado"]
            cidade = values["cidade"]
            bairro = values["bairro"]

            query = "SELECT * FROM Conta WHERE 1"
            params_local = []

            if bairro:
                query += " AND bairro = %s"
                params_local.append(bairro)
            if cidade:
                query += " AND cidade = %s"
                params_local.append(cidade)
            if estado:
                query += " AND estado = %s"
                params_local.append(estado)

            cursor.execute(query, params_local)

            usuarios_filtrados = cursor.fetchall()

            if usuarios_filtrados:
                formatted_results = [f"ID: {row[0]}, Nome: {row[1]}, Cidade: {row[2]}, Estado: {row[3]}, Bairro: {row[4]}" for row in usuarios_filtrados]
                sg.popup("Usuários Filtrados:", *formatted_results)
            else:
                sg.popup("Nenhum usuário encontrado com os critérios fornecidos.")

            window.close()
            return usuarios_filtrados


def calcular_media_anual_vendas(cursor):
    query = """
        SELECT YEAR(data_pedido) AS ano, AVG(total) AS media_anual
        FROM Pedido
        GROUP BY ano
        ORDER BY ano
    """
    cursor.execute(query)
    medias_anuais_vendas = cursor.fetchall()

    if medias_anuais_vendas:
        formatted_results = [f"Ano: {row[0]}, Média Anual: {row[1]}" for row in medias_anuais_vendas]
        sg.popup("Média Anual de Vendas por Ano:", *formatted_results)
    else:
        sg.popup("Nenhuma venda encontrada para calcular a média anual.")


def mes_ano_com_maior_vendas(cursor):
    cursor.execute(
        """
        SELECT DATE_FORMAT(data_pedido, '%Y-%m') AS mes_ano, COUNT(*) AS total_vendas
        FROM Pedido
        GROUP BY mes_ano
        ORDER BY total_vendas DESC
        LIMIT 1
    """
    )

    resultado = cursor.fetchone()

    if resultado:
        mes_ano, total_vendas = resultado
        sg.popup(
            f"O mês e ano com o maior número de vendas são: {mes_ano}, Total de vendas: {total_vendas}"
        )
    else:
        sg.popup("Nenhuma venda encontrada.")


def usuarios_compras_todos_meses(cursor):
    ano = sg.popup_get_text("Digite o ano desejado:")

    if ano:
        cursor.execute(
            """
            SELECT C.id, C.nome
            FROM Conta C
            WHERE C.id IN (
                SELECT P.id_conta
                FROM Pedido P
                WHERE YEAR(P.data_pedido) = %s
                GROUP BY P.id_conta
                HAVING COUNT(DISTINCT MONTH(P.data_pedido)) = 12
            )
        """,
            (ano,),
        )

        usuarios = cursor.fetchall()

        if usuarios:
            formatted_results = [f"ID da Conta: {usuario[0]}, Nome do Usuário: {usuario[1]}" for usuario in usuarios]
            sg.popup(*formatted_results)
        else:
            sg.popup("Não há usuários que compraram em todos os meses do ano.")



def obter_pedidos_por_periodo(cursor):
    layout = [
        [
            sg.Text("Digite a data de início (no formato DD/MM/YYYY): "),
            sg.Input(key="data_inicio"),
        ],
        [
            sg.Text("Digite a data de fim (no formato DD/MM/YYYY): "),
            sg.Input(key="data_fim"),
        ],
        [sg.Button("Buscar Pedidos")],
    ]

    window = sg.Window("Obter Pedidos por Período", layout)

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Buscar Pedidos":
            data_inicio_str = values["data_inicio"]
            data_fim_str = values["data_fim"]

            try:
                data_inicio = datetime.strptime(data_inicio_str, "%d/%m/%Y")
                data_fim = datetime.strptime(data_fim_str, "%d/%m/%Y")
            except ValueError:
                sg.popup("Data escrita no formato incorreto.")
                continue

            query = "SELECT * FROM Pedido WHERE data_pedido BETWEEN %s AND %s"
            values = (data_inicio, data_fim)
            cursor.execute(query, values)

            resultados = cursor.fetchall()

        if resultados:
            formatted_results = [f"ID: {row[0]}, Data: {row[1]}, Status: {row[2]}, Total: {row[3]}" for row in resultados]
            sg.popup(*formatted_results)
        else:
            sg.popup("Não foram encontrados pedidos.")


            window.close()
            break


def obter_pedidos_maior_que_valor(cursor):
    valor_minimo = sg.popup_get_text("Digite o valor mínimo do pedido:")
    try:
        valor_minimo = float(valor_minimo)
    except:
        sg.popup("Valor inválido.")
        return None

    query = "SELECT * FROM Pedido WHERE total > %s"
    cursor.execute(query, (valor_minimo,))
    resultados = cursor.fetchall()

    if resultados:
        formatted_results = [f"ID: {row[0]}, Data: {row[1]}, Status: {row[2]}, Total: {row[3]}" for row in resultados]
        sg.popup(*formatted_results)
    else:
        sg.popup("Não foram encontrados pedidos.")

