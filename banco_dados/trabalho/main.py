from mysql.connector import connection

from src.interface import (
    adicionar,
    clear_terminal,
    editar,
    remover,
    vizualicacao,
    wait_key,
)
from src.create_tables import create_if_not_exists


def main():
    clear_terminal()

    host = input("Digite o host do banco de dados: ")
    usuario = input("Digite o usuario do banco de dados: ")
    senha = input("Digite a senha do banco de dados: ")

    config = {
        "host": host,
        "user": usuario,
        "password": senha,
        # "raise_on_warnings": True,
    }
    conexao = connection.MySQLConnection(**config)
    cursor = conexao.cursor()

    create_if_not_exists(conexao, cursor)

    while True:
        print("\nDeseja logar como atendente:")
        print("1 - Sim")
        print("2 - Não")
        opcao = input("Digite o número da opção desejada: ")

        if opcao == "1":
            is_atendente = True
            break
        elif opcao == "2":
            is_atendente = False
            break
        else:
            print("Escolha invalida.")

    while True:
        clear_terminal()

        print(
            "-----Menu Principal------\n1 - Adicionar dados\n2 - Alterar dados\n3 - Remover dados\n4 - Vizualizações\n0 - Sair"
        )
        opcao = input("Digite o número da escolha: ")

        if opcao == "0":
            print("Fechando programa")
            break
        if opcao == "1":
            adicionar(conexao, cursor, is_atendente)
        elif opcao == "2":
            editar(conexao, cursor, is_atendente)
        elif opcao == "3":
            remover(conexao, cursor, is_atendente)
        elif opcao == "4":
            vizualicacao(cursor)
        else:
            print("Número invalido, escolha novamente.")
            wait_key()

    cursor.close()
    conexao.close()


if __name__ == "__main__":
    main()
