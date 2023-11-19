def pedidos_por_conta(cursor):
    id_conta = input("Digite o ID da conta: ")

    # Consulta para obter todos os pedidos associados a uma conta
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
        print(f"Pedidos associados à conta {id_conta}:")
        for resultado in resultados:
            print(
                f"ID: {resultado[0]}, Data: {resultado[1].strftime('%d/%m/%y')}, Status: {resultado[2]}, Valor total: {resultado[3]:.2f}, ID Conta: {resultado[4]}"
            )
    else:
        print(f"Nenhum pedido encontrado para a conta {id_conta}.")
        return None


def produtos_em_carrinho(cursor):
    id_carrinho = input("Digite o ID do carrinho desejado: ")

    # Obter todos os produtos no carrinho
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
        print(f"Produtos no carrinho (id_carrinho {id_carrinho}):")
        for resultado in resultados:
            print(
                f"ID: {resultado[0]}, Nome: {resultado[1]}, Preço Unitario: {resultado[2]}, Quantidade: {resultado[3]}"
            )
    else:
        print(f"Nenhum produto encontrado no carrinho (id_carrinho {id_carrinho}).")
        return None


def obter_dados_usuarios(cursor):
    # Consulta para obter dados e a quantidade de usuários
    cursor.execute(
        """
        SELECT id, nome, cidade, estado, bairro
        FROM Conta
    """
    )

    resultados = cursor.fetchall()

    if resultados:
        print(f"Quantidade total de usuários cadastrados: {len(resultados)}")
        print("\nDados dos usuários:")
        for resultado in resultados:
            print(
                f"ID: {resultado[0]}, Nome: {resultado[1]}, Cidade: {resultado[2]}, Estado {resultado[3]}, Bairro: {resultado[4]}"
            )
    else:
        print("Nenhum usuário cadastrado.")
        return None


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

    if not forma_pagamento_mais_utilizada:
        print("Nenhuma forma de pagamento encontrada no sistema.")
        return None

    forma, quantidade = forma_pagamento_mais_utilizada
    print(
        f"A forma de pagamento mais utilizada é '{forma}' com {quantidade} transações."
    )

    return forma_pagamento_mais_utilizada


def filtrar_usuarios_por_localizacao(cursor):
    estado = input(
        "Digite o estado desejado (ou pressione Enter para manter a atual): "
    )
    cidade = input(
        "Digite a cidade desejada (ou pressione Enter para manter a atual): "
    )
    bairro = input(
        "Digite o bairro desejado (ou pressione Enter para manter a atual): "
    )

    query = "SELECT * FROM Conta WHERE 1"
    params_local = []

    # Adicionar condições ao WHERE conforme necessário
    if bairro:
        query += " AND bairro = %s"
        params_local.append(bairro)
    if cidade:
        query += " AND cidade = %s"
        params_local.append(cidade)
    if estado:
        query += " AND estado = %s"
        params_local.append(estado)

    # Executar a query
    cursor.execute(query, params_local)

    usuarios_filtrados = cursor.fetchall()

    if not usuarios_filtrados:
        print("Nenhum usuário encontrado com os critérios fornecidos.")
        return None

    print("Usuários Filtrados:")
    for usuario in usuarios_filtrados:
        print(
            f"ID: {usuario[0]}, Nome: {usuario[1]}, Cidade: {usuario[2]}, Estado: {usuario[3]}, Bairro: {usuario[4]}"
        )

    return usuarios_filtrados


def calcular_media_anual_vendas(cursor):
    # Calcular a média anual de vendas para cada ano
    query = """
        SELECT YEAR(data_pedido) AS ano, AVG(total) AS media_anual
        FROM Pedido
        GROUP BY ano
        ORDER BY ano
    """
    cursor.execute(query)
    medias_anuais_vendas = cursor.fetchall()

    if not medias_anuais_vendas:
        print("Nenhuma venda encontrada para calcular a média anual.")
        return None

    print("Média Anual de Vendas por Ano:")
    for media_anual in medias_anuais_vendas:
        print(f"Ano: {media_anual[0]}, Média Anual: R$ {media_anual[1]:.2f}")


def mes_ano_com_maior_vendas(cursor):
    # Consulta para obter o mês e ano com o maior número de vendas
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
        print(
            f"O mês e ano com o maior número de vendas são: {mes_ano}, Total de vendas: {total_vendas}"
        )
    else:
        print("Nenhuma venda encontrada.")
        return None


def usuarios_compras_todos_meses(cursor):
    ano = input("Digite o ano desejado: ")

    # Obter todos os usuários que realizaram compras em cada mês do ano
    cursor.execute(
        """
        SELECT id_conta
        FROM Pedido
        WHERE YEAR(data_pedido) = %s
        GROUP BY id_conta
        HAVING COUNT(DISTINCT MONTH(data_pedido)) = 12
    """,
        (ano,),
    )

    usuarios = cursor.fetchall()

    if not usuarios:
        print("Não há usuarios que compraram em todos os meses do ano.")
        return None

    for usuario in usuarios:
        print(f"ID da Conta: {usuario[0]}")
