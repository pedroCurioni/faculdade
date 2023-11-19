import hashlib


def get_status_usuario_web():
    while True:
        print("Escolha uma opção para o novo status do usuario:")
        print("1 - Novo")
        print("2 - Ativo")
        print("3 - Bloqueado")
        print("4 - Banido Temporariamente")
        print("5 - Não alterar")

        opcao = input("Digite o número da opção desejada: ")

        if opcao == "1":
            return "Novo"
        elif opcao == "2":
            return "Ativo"
        elif opcao == "3":
            return "Bloqueado"
        elif opcao == "4":
            return "Banido Temporariamente"
        elif opcao == "5":
            return None
        else:
            print("Escolha invalida.")


def buscar_conta_por_id(cursor):
    id_conta = int(input("Digite o ID da conta: "))

    # Buscar detalhes da conta na tabela Conta
    cursor.execute("SELECT * FROM Conta WHERE id = %s", (id_conta,))
    detalhes_conta = cursor.fetchone()

    if detalhes_conta:
        # Se a conta for encontrada, retorna o id
        return id_conta
    else:
        # Se a conta não for encontrada, retorna False
        return None


def adicionar_conta(conexao, cursor):
    tipo_conta = input("Digite 'web' para usuário web ou 'cliente' para cliente: ")

    nome = input("Digite o nome do cliente: ")
    cidade = input("Digite a cidade do cliente: ")
    estado = input("Digite o estado do cliente: ")
    bairro = input("Digite o bairro do cliente: ")

    # Inserir uma nova conta no banco de dados
    cursor.execute(
        "INSERT INTO Conta (nome, cidade, estado, bairro) VALUES (%s, %s, %s, %s)",
        (nome, cidade, estado, bairro),
    )
    id_conta_inserido = cursor.lastrowid  # Obtém o ID da conta recém-inserida

    if tipo_conta == "web":
        login_web = input("Digite o login do usuário web: ")
        senha_web = input("Digite a senha do usuário web: ")

        senha_hash = hashlib.sha256(senha_web.encode()).hexdigest()

        status_web = "Novo"
        # Inserir um novo usuário web
        cursor.execute(
            "INSERT INTO Usuario_Web (id_conta, login, senha, status) VALUES (%s, %s, %s, %s)",
            (id_conta_inserido, login_web, senha_hash, status_web),
        )
    elif tipo_conta == "cliente":
        # Inserir um novo usuario telefone
        cursor.execute(
            "INSERT INTO Usuario_Telefone (id) VALUES (%s)", (id_conta_inserido,)
        )

    conexao.commit()
    print("Conta criada com sucesso.")


def editar_conta(conexao, cursor):
    id_conta = buscar_conta_por_id(cursor)

    if not id_conta:
        print("Conta não encontrada.")
        return None

    atualizar_detalhes_conta(cursor, id_conta)
    atualizar_detalhes_usuario_web(cursor, id_conta)

    conexao.commit()
    print(f"Dados da conta com ID {id_conta} atualizados com sucesso.")


def atualizar_detalhes_conta(cursor, id_conta):
    novo_nome = input("Novo nome (ou pressione Enter para manter o atual): ")
    nova_cidade = input("Nova cidade (ou pressione Enter para manter a atual): ")
    novo_estado = input("Novo estado (ou pressione Enter para manter o atual): ")
    novo_bairro = input("Novo bairro (ou pressione Enter para manter o atual): ")

    query_conta = "UPDATE Conta SET "
    params_conta = []

    if novo_nome:
        query_conta += "nome = %s, "
        params_conta.append(novo_nome)
    if nova_cidade:
        query_conta += "cidade = %s, "
        params_conta.append(nova_cidade)
    if novo_estado:
        query_conta += "estado = %s, "
        params_conta.append(novo_estado)
    if novo_bairro:
        query_conta += "bairro = %s, "
        params_conta.append(novo_bairro)

    query_conta = query_conta.rstrip(", ") + " WHERE id = %s"
    params_conta.append(id_conta)

    if len(params_conta) > 1:
        cursor.execute(query_conta, tuple(params_conta))


def atualizar_detalhes_usuario_web(cursor, id_conta):
    cursor.execute("SELECT * FROM Usuario_Web WHERE id_conta = %s", (id_conta,))
    resultado_usuario_web = cursor.fetchone()

    if not resultado_usuario_web:
        return None

    novo_login = input(
        "Novo login do usuário (ou pressione Enter para manter o atual): "
    )
    nova_senha = input(
        "Nova senha do usuário (ou pressione Enter para manter a atual): "
    )
    novo_status = get_status_usuario_web()

    query_usuario_web = "UPDATE Usuario_Web SET "
    params_usuario_web = []

    if novo_login:
        query_usuario_web += f"login = %s, "
        params_usuario_web.append(novo_login)
    if nova_senha:
        senha_antiga = input(
            "Para alterar a senha e necessario digitar sua senha anterior: "
        )
        senha_antiga_hash = hashlib.sha256(senha_antiga.encode()).hexdigest()
        if senha_antiga_hash != resultado_usuario_web[2]:
            print("Senha invalida, a senha não sera alterada.")
        else:
            query_usuario_web += f"senha = %s, "
            params_usuario_web.append(nova_senha)
    if novo_status:
        query_usuario_web += f"status = %s, "
        params_usuario_web.append(novo_status)

    query_usuario_web = query_usuario_web.rstrip(", ") + " WHERE id_conta = %s"
    params_usuario_web.append(id_conta)

    if len(params_usuario_web) > 1:
        cursor.execute(query_usuario_web, tuple(params_usuario_web))


def remover_conta(conexao, cursor):
    id_conta = buscar_conta_por_id(cursor)
    if not id_conta:
        print("Conta não encontrada.")
        return None

    # Desativar as restrições de chave estrangeira temporariamente
    cursor.execute("SET foreign_key_checks = 0")

    # Excluir registros associados nas tabelas relacionadas
    cursor.execute("DELETE FROM Usuario_Web WHERE id_conta = %s", (id_conta,))
    cursor.execute("DELETE FROM Usuario_Telefone WHERE id = %s", (id_conta,))
    cursor.execute("DELETE FROM Pedido WHERE id_conta = %s", (id_conta,))
    cursor.execute(
        "DELETE FROM Pagamento WHERE id_pedido IN (SELECT id FROM Pedido WHERE id_conta = %s)",
        (id_conta,),
    )
    cursor.execute("DELETE FROM Carrinho WHERE id_conta = %s", (id_conta,))
    cursor.execute(
        "DELETE FROM Item WHERE id_pedido IN (SELECT id FROM Pedido WHERE id_conta = %s)",
        (id_conta,),
    )

    # Excluir a conta na tabela Conta
    cursor.execute("DELETE FROM Conta WHERE id = %s", (id_conta,))

    # Commit das alterações e reativar as restrições de chave estrangeira
    conexao.commit()
    cursor.execute("SET foreign_key_checks = 1")
    print(f"Conta com ID {id_conta} removida com sucesso.")
