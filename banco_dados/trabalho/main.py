from mysql.connector import connection

from src.interface import (
    adicionar,
    clear_terminal,
    editar,
    remover,
    vizualicacao,
    wait_key,
)
from src.create_tables import create_database


def main():
    clear_terminal()

    host = input("Digite o host do banco de dados: ")
    usuario = input("Digite o usuario do banco de dados: ")
    senha = input("Digite a senha do banco de dados: ")

    create_database(host, usuario, senha)

    config = {
        "host": host,
        "user": usuario,
        "password": senha,
    }

    conexao = connection.MySQLConnection(**config)
    cursor = conexao.cursor()

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
            adicionar(conexao, cursor)
        elif opcao == "2":
            editar(conexao, cursor)
        elif opcao == "3":
            remover(conexao, cursor)
        elif opcao == "4":
            vizualicacao(cursor)
        else:
            print("Número invalido, escolha novamente.")
            wait_key()

    cursor.close()
    conexao.close()


if __name__ == "__main__":
    main()
