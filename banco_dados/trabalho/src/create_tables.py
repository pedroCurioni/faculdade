import mysql.connector

def create_database(host, user, password):
    query = """CREATE DATABASE IF NOT EXISTS gerenciador_compra;
    USE gerenciador_compra;
    CREATE TABLE IF NOT EXISTS Conta (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        nome VARCHAR(255),
        cidade VARCHAR(255),
        estado VARCHAR(255),
        bairro VARCHAR(255)
    );
    CREATE TABLE IF NOT EXISTS Usuario_Web (
        id_conta INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        login VARCHAR(255),
        senha VARCHAR(255),
        status VARCHAR(20),
        UNIQUE(login),
        FOREIGN KEY (id_conta) REFERENCES Conta(id)
    );
    CREATE TABLE IF NOT EXISTS Usuario_Telefone (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        FOREIGN KEY (id) REFERENCES Conta(id)
    );
    CREATE TABLE IF NOT EXISTS Pedido (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        data_pedido DATETIME,
        status_pedido VARCHAR(255),
        total DECIMAL(10, 2),
        id_conta INT,
        FOREIGN KEY (id_conta) REFERENCES Conta(id)
    );
    CREATE TABLE IF NOT EXISTS Pagamento (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        id_pedido INT,
        forma VARCHAR(255),
        FOREIGN KEY (id_pedido) REFERENCES Pedido(id)
    );
    CREATE TABLE IF NOT EXISTS Carrinho (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        id_conta INT,
        FOREIGN KEY (id_conta) REFERENCES Conta(id)
    );
    CREATE TABLE IF NOT EXISTS Produto (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        preco DECIMAL(10, 2),
        nome VARCHAR(255),
        estoque INT
    );
    CREATE TABLE IF NOT EXISTS Item (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        quantidade INT,
        id_produto INT,
        id_pedido INT,
        id_carrinho INT,
        FOREIGN KEY (id_produto) REFERENCES Produto(id),
        FOREIGN KEY (id_pedido) REFERENCES Pedido(id),
        FOREIGN KEY (id_carrinho) REFERENCES Carrinho(id)
    );
    DELIMITER // -- Trigger atualização do estoque
    CREATE TRIGGER IF NOT EXISTS after_update_pedido_status
    AFTER UPDATE ON Pedido FOR EACH ROW BEGIN
    DECLARE id_pedido INT;
    DECLARE novo_status VARCHAR(255);
    -- Obter o ID e o novo status do pedido
    SET id_pedido = NEW.id;
    SET novo_status = NEW.status_pedido;
    -- Se o novo status for 'confirmado', dar baixa no estoque
    IF novo_status = 'confirmado' THEN -- Atualizar o estoque dos itens do pedido
    UPDATE Item
    SET quantidade = quantidade * -1
    WHERE id_pedido = id_pedido;
    -- Atualizar o estoque do produto
    UPDATE Produto p
        JOIN Item i ON p.id = i.id_produto
    SET p.estoque = p.estoque + i.quantidade
    WHERE i.id_pedido = id_pedido;
    -- Se o novo status for 'cancelado', devolver itens ao estoque
    ELSEIF novo_status = 'cancelado' THEN -- Atualizar o estoque dos itens do pedido
    UPDATE Item
    SET quantidade = quantidade * -1
    WHERE id_pedido = id_pedido;
    -- Atualizar o estoque do produto
    UPDATE Produto p
        JOIN Item i ON p.id = i.id_produto
    SET p.estoque = p.estoque + i.quantidade
    WHERE i.id_pedido = id_pedido;
    END IF;
    END;"""

    config = {
        "host": host,
        "user": user,
        "password": password,
        "raise_on_warnings": True,
    }
    conexao = mysql.connector.connect(**config)
    cursor = conexao.cursor()

    cursor.execute(query)

    conexao.close()
    cursor.close()
