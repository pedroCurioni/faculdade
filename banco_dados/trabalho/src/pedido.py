from datetime import datetime
from src.carrinho import buscar_carrinho_por_conta


def get_status_pedido():
    while True:
        print("Escolha uma opção para o novo status do pedido:")
        print("1 - Em Processamento")
        print("2 - Cancelado")
        print("3 - Confirmado")
        print("4 - Pago")
        print("5 - Enviado")
        print("6 - Em Transito")
        print("7 - Não alterar")

        opcao = input("Digite o número da opção desejada: ")

        if opcao == "1":
            return "Em Processamento"
        elif opcao == "2":
            return "Cancelado"
        elif opcao == "3":
            return "Confirmado"
        elif opcao == "4":
            return "Pago"
        elif opcao == "5":
            return "Enviado"
        elif opcao == "6":
            return "Em Transito"
        elif opcao == "7":
            return None
        else:
            print("Escolha invalida.")


def buscar_pedido_por_id(cursor):
    try:
        id_pedido = int(input("Digite o ID do pedido que deseja buscar: "))
    except ValueError:
        print("Por favor, digite um número inteiro para o ID do pedido.")
        return None

    cursor.execute("SELECT * FROM Pedido WHERE id = %s", (id_pedido,))
    pedido = cursor.fetchone()

    if pedido:
        return id_pedido
    else:
        # Produto não encontrado
        return None


def atualizar_id_pedido_em_items(cursor, id_pedido, itens_carrinho):
    # Atualizar o ID do pedido nos itens
    for item in itens_carrinho:
        query_atualizar_item = "UPDATE Item SET id_pedido = %s, id_carrinho = NULL WHERE id = %s"
        values_atualizar_item = (id_pedido, item[0])
        cursor.execute(query_atualizar_item, values_atualizar_item)


def atualizar_total_pedido(cursor, id_pedido):
    # Calcular o total do pedido
    query_total_pedido = "SELECT SUM(quantidade * preco) FROM Item JOIN Produto ON Item.id_produto = Produto.id WHERE id_pedido = %s"
    cursor.execute(query_total_pedido, (id_pedido,))
    total_pedido = cursor.fetchone()[0]

    # Atualizar o total do pedido
    print(id_pedido)
    query_atualizar_total_pedido = "UPDATE Pedido SET total = %s WHERE id = %s"
    values_atualizar_total_pedido = (total_pedido, id_pedido)
    cursor.execute(query_atualizar_total_pedido, values_atualizar_total_pedido)


def realizar_pagamento(cursor, id_pedido):
    forma_pagamento = input("Informe a forma de pagamento: ")

    while True:
        try:
            vezes_pagamento = int(input("Informe a quantidade de vezes para o pagamento: "))
            if vezes_pagamento < 1:
                print("Quantidade de vezes para o pagamento inválida.")
            else:
                break
        except ValueError:
            print("Valor invalido. Digite um número.")

    if forma_pagamento == "":
        print("Por favor, preencha todas as informações.")
        return None


    # Criar a entidade de pagamento
    query_pagamento = "INSERT INTO Pagamento (id_pedido, forma) VALUES (%s, %s)"
    values_pagamento = (id_pedido, forma_pagamento)
    cursor.execute(query_pagamento, values_pagamento)

    # Se necessário, replicar a entidade de pagamento de acordo com a quantidade de vezes
    for i in range(vezes_pagamento - 1):
        cursor.execute(query_pagamento, values_pagamento)


def realizar_pedido(connection, cursor):
    # Obter a data atual
    data_pedido = datetime.now()

    try:
        id_conta = int(input("Digite o ID da conta para realizar o pedido: "))
    except ValueError:
        print("Por favor, digite um número inteiro para o ID da conta.")
        return None

    # Criar o pedido
    query_pedido = "INSERT INTO Pedido (data_pedido, status_pedido, total, id_conta) VALUES (%s, %s, %s, %s)"
    values_pedido = (data_pedido, "Em Processamento", 0, id_conta)
    cursor.execute(query_pedido, values_pedido)

    # Obter o ID do pedido recém-criado
    id_pedido = cursor.lastrowid

    id_carrinho = buscar_carrinho_por_conta(cursor, id_conta)
    if not id_carrinho:
        print("Conta não possui um carrinho, adicione itens primeiro.")
        return None

    # Obter os itens do carrinho
    query_itens = "SELECT * FROM Item WHERE id_carrinho = %s"
    cursor.execute(query_itens, (id_carrinho,))
    itens_carrinho = cursor.fetchall()
    if not itens_carrinho:
        print("Carrinho vazio. Não é possível realizar o pedido.")
        return None

    atualizar_id_pedido_em_items(cursor, id_pedido, itens_carrinho)

    atualizar_total_pedido(cursor, id_pedido)

    realizar_pagamento(cursor, id_pedido)

    connection.commit()
    print("Pedido realizado com sucesso!")


def editar_pedido(connection, cursor):
    id_pedido = buscar_pedido_por_id(cursor)
    if not id_pedido:
        print("Pedido não encontrado.")
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
        print("Status do pedido atualizado com sucesso.")
