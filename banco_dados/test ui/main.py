import PySimpleGUI as sg
from mysql.connector import connection
from src.interface import adicionar, editar, remover, visualizacao
from src.create_tables import create_if_not_exists


def main():
    sg.theme("DefaultNoMoreNagging")

    layout_db_config = [
        [sg.Text("Host do banco de dados:"), sg.InputText(key="host")],
        [sg.Text("Usuário do banco de dados:"), sg.InputText(key="usuario")],
        [
            sg.Text("Senha do banco de dados:"),
            sg.InputText(key="senha", password_char="*"),
        ],
        [sg.Button("Conectar")],
    ]

    window_db_config = sg.Window("Configuração do Banco de Dados", layout_db_config)

    while True:
        event_db_config, values_db_config = window_db_config.read()

        if event_db_config == sg.WINDOW_CLOSED:
            break

        if event_db_config == "Conectar":
            host = values_db_config["host"]
            usuario = values_db_config["usuario"]
            senha = values_db_config["senha"]

            config = {
                "host": host,
                "user": usuario,
                "password": senha,
                # "raise_on_warnings": True,
            }

            try:
                conexao = connection.MySQLConnection(**config)
                cursor = conexao.cursor()
                create_if_not_exists(conexao, cursor)
                break
            except connection.Error as e:
                sg.popup_error(f"Erro ao conectar ao banco de dados: {str(e)}")

    window_db_config.close()

    is_atendente = False

    while True:
        layout_menu = [
            [sg.Text("Deseja logar como atendente:")],
            [sg.Button("Sim", key="sim"), sg.Button("Não", key="nao")],
        ]

        window_menu = sg.Window("Login", layout_menu)

        event_menu, values_menu = window_menu.read()

        if event_menu == sg.WINDOW_CLOSED:
            break

        if event_menu == "sim":
            is_atendente = True
            break
        elif event_menu == "nao":
            is_atendente = False
            break

    window_menu.close()

    while True:
        layout_main = [
            [sg.Text("Menu Principal")],
            [sg.Button("Adicionar dados", key="adicionar")],
            [sg.Button("Alterar dados", key="alterar")],
            [sg.Button("Remover dados", key="remover")],
            [sg.Button("Vizualizações", key="vizualizacoes")],
            [sg.Button("Sair", key="sair")],
        ]

        window_main = sg.Window("Menu Principal", layout_main, margins=(50,50))

        event_main, values_main = window_main.read()

        if event_main == sg.WINDOW_CLOSED or event_main == "sair":
            print("Fechando programa")
            break
        if event_main == "adicionar":
            window_main.close()
            adicionar(
                conexao,
                cursor,
                is_atendente,
            )
        elif event_main == "alterar":
            window_main.close()
            editar(conexao, cursor, is_atendente)
        elif event_main == "remover":
            window_main.close()
            remover(conexao, cursor, is_atendente)
        elif event_main == "vizualizacoes":
            window_main.close()
            visualizacao(cursor)

    cursor.close()
    conexao.close()


if __name__ == "__main__":
    main()
