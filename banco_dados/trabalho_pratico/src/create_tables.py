import mysql.connector
from mysql.connector import errorcode

DB_NAME = "gerenciador_compra"

TABLES = {}

TABLES["Conta"] = """
    CREATE TABLE IF NOT EXISTS Conta (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        nome VARCHAR(255),
        email VARCHAR(255),
        telefone VARCHAR(255),
        cidade VARCHAR(255),
        estado VARCHAR(255),
        bairro VARCHAR(255)
    );"""

TABLES["Usuario_Web"] = """
    CREATE TABLE IF NOT EXISTS Usuario_Web (
        id_conta INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        login VARCHAR(255),
        senha VARCHAR(255),
        status VARCHAR(20),
        UNIQUE(login),
        FOREIGN KEY (id_conta) REFERENCES Conta(id)
    );"""

TABLES["Usuario_Telefone"] = """
    CREATE TABLE IF NOT EXISTS Usuario_Telefone (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        FOREIGN KEY (id) REFERENCES Conta(id)
    );"""

TABLES["Pedido"] = """
    CREATE TABLE IF NOT EXISTS Pedido (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        data_pedido DATETIME,
        status_pedido VARCHAR(255),
        total DECIMAL(10, 2),
        id_conta INT,
        FOREIGN KEY (id_conta) REFERENCES Conta(id)
    );"""

TABLES["Pagamento"] = """
    CREATE TABLE IF NOT EXISTS Pagamento (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        id_pedido INT,
        forma VARCHAR(255),
        FOREIGN KEY (id_pedido) REFERENCES Pedido(id)
    );"""

TABLES["Carrinho"] = """
    CREATE TABLE IF NOT EXISTS Carrinho (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        id_conta INT,
        FOREIGN KEY (id_conta) REFERENCES Conta(id)
    );"""

TABLES["Produto"] = """
    CREATE TABLE IF NOT EXISTS Produto (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        preco DECIMAL(10, 2),
        nome VARCHAR(255),
        estoque INT
    );"""

TABLES["Item"] = """
    CREATE TABLE IF NOT EXISTS Item (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        quantidade INT,
        id_produto INT,
        id_pedido INT,
        id_carrinho INT,
        FOREIGN KEY (id_produto) REFERENCES Produto(id),
        FOREIGN KEY (id_pedido) REFERENCES Pedido(id),
        FOREIGN KEY (id_carrinho) REFERENCES Carrinho(id)
    );"""

TRIGGER = """
    CREATE TRIGGER IF NOT EXISTS after_update_pedido_status
    AFTER UPDATE ON Pedido FOR EACH ROW
    BEGIN
        DECLARE id_pedido INT;
        DECLARE novo_status VARCHAR(255);

        SET id_pedido = NEW.id;
        SET novo_status = NEW.status_pedido;

        IF novo_status = 'confirmado' THEN
            UPDATE Item
            SET quantidade = quantidade * -1
            WHERE id_pedido = id_pedido;

            UPDATE Produto p
            JOIN Item i ON p.id = i.id_produto
            SET p.estoque = p.estoque + i.quantidade
            WHERE i.id_pedido = id_pedido;

        ELSEIF novo_status = 'cancelado' THEN
            UPDATE Item
            SET quantidade = quantidade * -1
            WHERE id_pedido = id_pedido;

            UPDATE Produto p
            JOIN Item i ON p.id = i.id_produto
            SET p.estoque = p.estoque + i.quantidade
            WHERE i.id_pedido = id_pedido;
        END IF;
    END;
    """

def create_database(cursor):
    try:
        cursor.execute(
            "CREATE DATABASE gerenciador_compra DEFAULT CHARACTER SET 'UTF8MB4'"
        )
    except mysql.connector.Error as err:
        print("Erro ao criar banco de dados: {}".format(err))
        exit(1)


def create_tables(cursor):
    for table_name in TABLES:
        table_description = TABLES[table_name]
        try:
            print("Criando tabela {}: ".format(table_name), end="")
            cursor.execute(table_description)
        except mysql.connector.Error as err:
            if err.errno == errorcode.ER_TABLE_EXISTS_ERROR:
                print("Já existe.")
            else:
                print(err.msg)
        else:
            print("OK")

def create_trigger(cursor):
    try:
        print("Criando Trigger: ", end="")
        cursor.execute(TRIGGER)
        print("OK")
    except mysql.connector.Error:
        print("Já existe.")


def create_if_not_exists(conexao, cursor):
    try:
        cursor.execute("USE {}".format(DB_NAME))
    except mysql.connector.Error as err:
        print("Database {} não existe.".format(DB_NAME))
        if err.errno == errorcode.ER_BAD_DB_ERROR:
            create_database(cursor)
            print("Database {} criada com sucesso.".format(DB_NAME))
            conexao.database = DB_NAME
        else:
            print(err)
            exit(1)

    create_tables(cursor)
    
    create_trigger(cursor)
