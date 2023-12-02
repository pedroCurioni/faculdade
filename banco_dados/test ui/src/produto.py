import PySimpleGUI as sg


def buscar_produto_por_id(cursor):
    layout = [
        [
            sg.Text("Digite o ID do produto que deseja buscar: "),
            sg.Input(key="id_produto"),
        ],
        [sg.Button("Buscar")],
    ]

    window = sg.Window("Buscar Produto por ID", layout, margins=(50,50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Buscar":
            try:
                id_produto = int(values["id_produto"])
                window.close()
                cursor.execute("SELECT * FROM Produto WHERE id = %s", (id_produto,))
                produto = cursor.fetchone()

                if produto:
                    return id_produto
                else:
                    # Produto não encontrado
                    return None
            except ValueError:
                sg.popup("Por favor, digite um número inteiro para o ID do produto.")


def adicionar_produto(conexao, cursor):
    layout = [
        [sg.Text("Digite o nome do produto: "), sg.Input(key="nome")],
        [sg.Text("Digite o preço do produto: "), sg.Input(key="preco")],
        [sg.Text("Digite a quantidade em estoque: "), sg.Input(key="estoque")],
        [sg.Button("Adicionar")],
    ]

    window = sg.Window("Adicionar Produto", layout, margins=(50,50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Adicionar":
            nome = values["nome"]
            preco = values["preco"]
            estoque = values["estoque"]

            if not nome or not preco or not estoque:
                sg.popup("Por favor, preencha todas as informações.")
                continue

            query = "INSERT INTO Produto (preco, nome, estoque) VALUES (%s, %s, %s)"
            values = (float(preco), nome, int(estoque))

            cursor.execute(query, values)
            conexao.commit()

            sg.popup("Produto adicionado com sucesso!")
            window.close()
            break


def editar_produto(conexao, cursor):
    id_produto = buscar_produto_por_id(cursor)
    if not id_produto:
        sg.popup("Produto não encontrado.")
        return None

    layout = [
        [sg.Text(f"ID do Produto: {id_produto}")],
        [
            sg.Text(
                "Digite o novo nome do produto (ou deixe em branco para manter o atual): "
            ),
            sg.Input(key="novo_nome"),
        ],
        [
            sg.Text(
                "Digite o novo preço do produto (ou deixe em branco para manter o atual): "
            ),
            sg.Input(key="novo_preco"),
        ],
        [
            sg.Text(
                "Digite a nova quantidade em estoque (ou deixe em branco para manter a atual): "
            ),
            sg.Input(key="novo_estoque"),
        ],
        [sg.Button("Editar")],
    ]

    window = sg.Window("Editar Produto", layout, margins=(50,50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Editar":
            novo_nome = values["novo_nome"]
            novo_preco = values["novo_preco"]
            novo_estoque = values["novo_estoque"]

            query_produto = "UPDATE Produto SET "
            params_produto = []

            if novo_nome:
                query_produto += "nome = %s, "
                params_produto.append(novo_nome)
            if novo_preco:
                query_produto += "preco = %s, "
                params_produto.append(float(novo_preco))
            if novo_estoque:
                query_produto += "estoque = %s, "
                params_produto.append(int(novo_estoque))

            query_produto = query_produto.rstrip(", ") + " WHERE id = %s"
            params_produto.append(id_produto)

            if len(params_produto) > 1:
                cursor.execute(query_produto, tuple(params_produto))
                conexao.commit()
                sg.popup("Produto editado com sucesso!")
                window.close()
                break


def remover_produto(conexao, cursor):
    id_produto = buscar_produto_por_id(cursor)
    if not id_produto:
        sg.popup("Produto não encontrado.")
        return None

    # Antes de excluir o produto, remova os itens associados a ele na tabela 'Item'
    cursor.execute("DELETE FROM Item WHERE id_produto = %s", (id_produto,))

    # Agora, exclua o produto da tabela 'Produto'
    cursor.execute("DELETE FROM Produto WHERE id = %s", (id_produto,))

    conexao.commit()
    sg.popup("Produto removido com sucesso!")
