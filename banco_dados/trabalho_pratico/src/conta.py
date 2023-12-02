import PySimpleGUI as sg
import hashlib


def get_status_usuario_web():
    layout = [
        [sg.Text("Escolha uma opção para o novo status do usuário:")],
        [
            sg.Radio("Novo", "RADIO1", key="Novo"),
            sg.Radio("Ativo", "RADIO1", key="Ativo"),
            sg.Radio("Bloqueado", "RADIO1", key="Bloqueado"),
            sg.Radio("Banido Temporariamente", "RADIO1", key="Banido Temporariamente"),
            sg.Radio("Não alterar", "RADIO1", key="Não alterar"),
        ],
        [sg.Button("OK")],
    ]

    window = sg.Window("Escolha o Status do Usuário", layout, margins=(50, 50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None
        if event == "OK":
            selected_option = None
            for key in ["Novo", "Ativo", "Bloqueado", "Banido Temporariamente"]:
                if values[key]:
                    selected_option = key
                    break
            window.close()
            return selected_option


def buscar_conta_por_id(cursor):
    layout = [
        [sg.Text("Digite o ID da conta: "), sg.Input(key="id_conta")],
        [sg.Button("Buscar")],
    ]

    window = sg.Window("Buscar Conta por ID", layout, margins=(50, 50))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            window.close()
            return None

        if event == "Buscar":
            try:
                id_conta = int(values["id_conta"])
                cursor.execute("SELECT * FROM Conta WHERE id = %s", (id_conta,))
                detalhes_conta = cursor.fetchone()
                window.close()
                print(id_conta)
                print(detalhes_conta)
                if detalhes_conta:
                    # Se a conta for encontrada, retorna o id
                    return id_conta
                else:
                    # Se a conta não for encontrada, retorna False
                    return None
            except ValueError:
                sg.popup("O ID da conta deve ser um número inteiro.")


def adicionar_usuario_web(cursor, id_conta):
    layout_web = [
        [sg.Text("Login do Usuário Web: "), sg.Input(key="login_web")],
        [
            sg.Text("Senha do Usuário Web: "),
            sg.Input(key="senha_web", password_char="*"),
        ],
        [sg.Button("OK")],
    ]

    window_web = sg.Window("Adicionar Usuário Web", layout_web, margins=(50, 50))

    event_web, values_web = window_web.read()

    login_web = values_web.get("login_web")
    senha_web = values_web.get("senha_web")

    senha_hash = hashlib.sha256(senha_web.encode()).hexdigest()

    status_web = "Novo"
    cursor.execute(
        "INSERT INTO Usuario_Web (id_conta, login, senha, status) VALUES (%s, %s, %s, %s)",
        (id_conta, login_web, senha_hash, status_web),
    )
    window_web.close()


def adicionar_conta(conexao, cursor):
    layout = [
        [sg.Text("E um usuario web (S ou N): "), sg.Input(key="tipo_conta")],
        [sg.Text("Nome do Cliente: "), sg.Input(key="nome")],
        [sg.Text("Cidade do Cliente: "), sg.Input(key="cidade")],
        [sg.Text("Estado do Cliente: "), sg.Input(key="estado")],
        [sg.Text("Bairro do Cliente: "), sg.Input(key="bairro")],
        [
            sg.Text("Telefone do Cliente: "),
            sg.Input(key="telefone"),
        ],  # Adicionado campo para telefone
        [
            sg.Text("Email do Cliente: "),
            sg.Input(key="email"),
        ],  # Adicionado campo para email
        [sg.Button("Adicionar")],
    ]

    window = sg.Window("Adicionar Conta", layout, margins=(50, 50))

    event, values = window.read()

    tipo_conta = values.get("tipo_conta")
    nome = values.get("nome")
    cidade = values.get("cidade")
    estado = values.get("estado")
    bairro = values.get("bairro")
    telefone = values.get("telefone")
    email = values.get("email")

    if not all([tipo_conta, nome, cidade, estado, bairro, telefone, email]):
        sg.popup("Por favor, preencha todas as informações do cliente.")
        window.close()
        return None

    cursor.execute(
        "INSERT INTO Conta (nome, cidade, estado, bairro, telefone, email) VALUES (%s, %s, %s, %s, %s, %s)",
        (nome, cidade, estado, bairro, telefone, email),
    )
    id_conta_inserido = cursor.lastrowid

    if tipo_conta.lower() == "s":
        adicionar_usuario_web(cursor, id_conta_inserido)
    else:
        cursor.execute(
            "INSERT INTO Usuario_Telefone (id) VALUES (%s)", (id_conta_inserido,)
        )

    conexao.commit()
    sg.popup("Conta criada com sucesso.")
    window.close()


def editar_conta(conexao, cursor):
    id_conta = buscar_conta_por_id(cursor)

    if not id_conta:
        sg.popup("Conta não encontrada.")
        return None

    conta_att = atualizar_detalhes_conta(cursor, id_conta)
    user_web_att = atualizar_detalhes_usuario_web(cursor, id_conta)

    conexao.commit()
    if conta_att == 0 or user_web_att == 0:
        sg.popup(f"Dados da conta com ID {id_conta} atualizados com sucesso.")


def atualizar_detalhes_conta(cursor, id_conta):
    layout = [
        [
            sg.Text("Novo nome (ou deixe em branco para manter o atual): "),
            sg.Input(key="novo_nome"),
        ],
        [
            sg.Text("Nova cidade (ou deixe em branco para manter a atual): "),
            sg.Input(key="nova_cidade"),
        ],
        [
            sg.Text("Novo estado (ou deixe em branco para manter o atual): "),
            sg.Input(key="novo_estado"),
        ],
        [
            sg.Text("Novo bairro (ou deixe em branco para manter o atual): "),
            sg.Input(key="novo_bairro"),
        ],
        [
            sg.Text("Novo email (ou deixe em branco para manter o atual): "),
            sg.Input(key="novo_email"),
        ],
        [
            sg.Text("Novo telefone (ou deixe em branco para manter o atual): "),
            sg.Input(key="novo_telefone"),
        ],
        [sg.Button("Atualizar")],
    ]

    window = sg.Window("Atualizar Detalhes da Conta", layout, margins=(50, 50))

    event, values = window.read()

    novo_nome = values.get("novo_nome")
    nova_cidade = values.get("nova_cidade")
    novo_estado = values.get("novo_estado")
    novo_bairro = values.get("novo_bairro")
    novo_email = values.get("novo_email")
    novo_telefone = values.get("novo_telefone")

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
    if novo_email:
        query_conta += "email = %s, "
        params_conta.append(novo_email)
    if novo_telefone:
        query_conta += "telefone = %s, "
        params_conta.append(novo_telefone)

    query_conta = query_conta.rstrip(", ") + " WHERE id = %s"
    params_conta.append(id_conta)

    if len(params_conta) > 1:
        cursor.execute(query_conta, tuple(params_conta))
        window.close()
        return 0
    else:
        window.close()
        return None


def atualizar_detalhes_usuario_web(cursor, id_conta):
    cursor.execute("SELECT * FROM Usuario_Web WHERE id_conta = %s", (id_conta,))
    resultado_usuario_web = cursor.fetchone()

    if not resultado_usuario_web:
        return None

    layout = [
        [
            sg.Text("Novo login do usuário (ou deixe em branco para manter o atual): "),
            sg.Input(key="novo_login"),
        ],
        [
            sg.Text("Nova senha do usuário (ou deixe em branco para manter o atual): "),
            sg.Input(key="nova_senha", password_char="*"),
        ],
        [sg.Button("Atualizar")],
    ]

    window = sg.Window("Atualizar Detalhes do Usuário Web", layout, margins=(50, 50))

    event, values = window.read()

    novo_login = values.get("novo_login")
    nova_senha = values.get("nova_senha")
    status = get_status_usuario_web()

    query_usuario_web = "UPDATE Usuario_Web SET "
    params_usuario_web = []

    if novo_login:
        query_usuario_web += f"login = %s, "
        params_usuario_web.append(novo_login)
    if nova_senha:
        senha_antiga = sg.popup_get_text(
            "Para alterar a senha é necessário digitar a senha anterior:",
            password_char="*",
        )
        senha_antiga_hash = hashlib.sha256(senha_antiga.encode()).hexdigest()
        if senha_antiga_hash != resultado_usuario_web[2]:
            sg.popup("Senha inválida, a senha não será alterada.")
            window.close()
            return None
        else:
            query_usuario_web += f"senha = %s, "
            params_usuario_web.append(hashlib.sha256(nova_senha.encode()).hexdigest())
    if status:
        query_usuario_web += f"status = %s, "
        params_usuario_web.append(status)

    query_usuario_web = query_usuario_web.rstrip(", ") + " WHERE id_conta = %s"
    params_usuario_web.append(id_conta)

    if len(params_usuario_web) > 1:
        cursor.execute(query_usuario_web, tuple(params_usuario_web))
        window.close()
        return 0
    else:
        window.close()
        return 1


def remover_conta(conexao, cursor):
    id_conta = buscar_conta_por_id(cursor)
    if not id_conta:
        sg.popup("Conta não encontrada.")
        return None

    cursor.execute("SET foreign_key_checks = 0")

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

    cursor.execute("DELETE FROM Conta WHERE id = %s", (id_conta,))

    conexao.commit()
    cursor.execute("SET foreign_key_checks = 1")
    sg.popup(f"Conta com ID {id_conta} removida com sucesso.")
