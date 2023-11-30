def buscar_produto_por_id(cursor):
    try:
        id_produto = int(input("Digite o ID do produto que deseja buscar: "))
    except ValueError:
        print("Por favor, digite um número inteiro para o ID do produto.")
        return None

    cursor.execute("SELECT * FROM Produto WHERE id = %s", (id_produto,))
    produto = cursor.fetchone()

    if produto:
        return id_produto
    else:
        # Produto não encontrado
        return None


def adicionar_produto(conexao, cursor):
    nome = input("Digite o nome do produto: ")
    preco = input("Digite o preço do produto: ")
    estoque = input("Digite a quantidade em estoque: ")

    query = "INSERT INTO Produto (preco, nome, estoque) VALUES (%s, %s, %s)"
    values = (float(preco), nome, int(estoque))

    cursor.execute(query, values)
    conexao.commit()

    print("Produto adicionado com sucesso!")


def editar_produto(conexao, cursor):
    id_produto = buscar_produto_por_id(cursor)
    if not id_produto:
        print("Produto não encontrado")
        return None

    novo_nome = input(
        "Digite o novo nome do produto (ou pressione Enter para manter a atual): "
    )
    novo_preco = input(
        "Digite o novo preço do produto (ou pressione Enter para manter a atual): "
    )
    novo_estoque = input(
        "Digite a nova quantidade em estoque (ou pressione Enter para manter a atual): "
    )

    query_conta = "UPDATE Produto SET "
    params_produto = []

    if novo_nome:
        query_conta += "nome = %s, "
        params_produto.append(novo_nome)
    if novo_preco:
        query_conta += "preco = %s, "
        params_produto.append(float(novo_preco))
    if novo_estoque:
        query_conta += "estoque = %s, "
        params_produto.append(int(novo_estoque))

    query_conta = query_conta.rstrip(", ") + " WHERE id = %s"
    params_produto.append(id_produto)

    if len(params_produto) > 1:
        cursor.execute(query_conta, tuple(params_produto))
        conexao.commit()
        print("Produto editado com sucesso!")


def remover_produto(conexao, cursor):
    id_produto = buscar_produto_por_id(cursor)
    if not id_produto:
        print("Produto não encontrado.")
        return None

    # Antes de excluir o produto, remova os itens associados a ele na tabela 'Item'
    cursor.execute("DELETE FROM Item WHERE id_produto = %s", (id_produto,))

    # Agora, exclua o produto da tabela 'Produto'
    cursor.execute("DELETE FROM Produto WHERE id = %s", (id_produto,))

    conexao.commit()
    print("Produto removido com sucesso!")
