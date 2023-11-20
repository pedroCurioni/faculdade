from src.conta import buscar_conta_por_id
from src.produto import buscar_produto_por_id


def buscar_carrinho_por_conta(cursor, id_conta):
    # Buscar detalhes da carrinho na tabela Carrinho
    cursor.execute("SELECT * FROM Carrinho WHERE id = %s", (id_conta,))
    detalhes_carrinho = cursor.fetchone()

    if detalhes_carrinho:
        # Se o carrinho for encontrada, retorna o id
        return detalhes_carrinho[0]
    else:
        # Se o carrinho não for encontrada, retorna False
        return None


def busca_item_carrinho(cursor, id_carrinho, id_produto):
    cursor.execute(
        "SELECT id, quantidade FROM Item WHERE id_carrinho = %s AND id_produto = %s",
        (id_carrinho, id_produto),
    )
    item = cursor.fetchone()
    if item:
        # ID do item
        return item[0]
    else:
        return None


def criar_carrinho(connection, cursor, id_conta):
    # Verificar se o usuário possui um carrinho
    cursor.execute("SELECT id FROM Carrinho WHERE id_conta = %s", (id_conta,))
    carrinho = cursor.fetchone()

    if carrinho:
        id_carrinho = carrinho[0]
    else:
        # Se o usuário não tiver um carrinho, crie um carrinho para o usuário
        cursor.execute("INSERT INTO Carrinho (id_conta) VALUES (%s)", (id_conta,))
        connection.commit()

        # Recupere o ID do carrinho recém-criado
        cursor.execute("SELECT id FROM Carrinho WHERE id_conta = %s", (id_conta,))
        id_carrinho = cursor.fetchone()[0]
    return id_carrinho


def adicionar_produto_carrinho(connection, cursor):
    id_conta = buscar_conta_por_id(cursor)
    if not id_conta:
        print("Conta não encontrada.")
        return None

    id_produto = buscar_produto_por_id(cursor)
    if not id_produto:
        print("Produto não encontrado.")
        return None

    quantidade = int(input("Digite a quantidade que deseja adicionar ao carrinho: "))

    id_carrinho = criar_carrinho(connection, cursor, id_conta)

    id_item = busca_item_carrinho(cursor, id_carrinho, id_produto)
    if id_item:
        # Se o produto já estiver no carrinho, atualize a quantidade
        cursor.execute(
            "UPDATE Item SET quantidade = quantidade + %s WHERE id_carrinho = %s AND id_produto = %s",
            (quantidade, id_carrinho, id_produto),
        )
        print("Produto ja estava no carrinho, sua quantidade foi aumentada.")
    else:
        # Se o produto não estiver no carrinho, adicione um novo item
        cursor.execute(
            "INSERT INTO Item (quantidade, id_produto, id_carrinho) VALUES (%s, %s, %s)",
            (quantidade, id_produto, id_carrinho),
        )
        print("Produto adicionado ao carrinho com sucesso!")

    connection.commit()


def editar_carrinho(connection, cursor):
    id_conta = buscar_conta_por_id(cursor)
    if not id_conta:
        print("Conta não encontrada.")
        return None

    id_produto = buscar_produto_por_id(cursor)
    if not id_produto:
        print("Produto não encontrado.")
        return None

    nova_quantidade = int(
        input("Digite a nova quantidade para o produto no carrinho: ")
    )

    id_carrinho = criar_carrinho(connection, cursor, id_conta)

    # Verificar se o produto está no carrinho
    id_item = busca_item_carrinho(cursor, id_carrinho, id_produto)
    if not id_item:
        print("Produto não está no carrinho.")
        return None

    if nova_quantidade > 0:
        cursor.execute(
            "UPDATE Item SET quantidade = %s WHERE id = %s", (nova_quantidade, id_item)
        )
        connection.commit()
        print("Quantidade do item no carrinho atualizada com sucesso!")
    else:
        # Se a nova quantidade for menor ou igual a zero, remova o item do carrinho
        remover_produto_carrinho(connection, cursor, id_conta, id_produto)
        print("Item removido do carrinho, pois a quantidade foi ajustada para zero.")


def remover_produto_carrinho(connection, cursor, id_conta, id_produto):
    id_conta = buscar_conta_por_id(cursor)
    if id_conta is False:
        print("Conta não encontrada.")
        return False

    id_produto = buscar_produto_por_id(cursor)
    if id_produto is False:
        print("Produto não encontrado.")
        return False

    id_carrinho = criar_carrinho(connection, cursor, id_conta)

    # Verificar se o produto está no carrinho
    id_item = busca_item_carrinho(cursor, id_carrinho, id_produto)
    if not id_item:
        print("Produto não está no carrinho.")
        return None

    # Remover o produto do carrinho
    cursor.execute(
        "DELETE FROM Item WHERE id = %s",
        (id_item,),
    )
    connection.commit()
    print("Produto removido do carrinho!.")
