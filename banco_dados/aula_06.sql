DROP TABLE contem;

DROP TABLE telCliente;

DROP TABLE pedido;

DROP TABLE cliente;

DROP TABLE nota;

DROP TABLE mesa;

DROP TABLE item_consumo;

CREATE TABLE cliente (
    idCliente INTEGER AUTO_INCREMENT,
    nomeCliente VARCHAR(255),
    PRIMARY KEY(idCliente)
);

CREATE TABLE telCliente (
    idCliente INTEGER,
    telefone VARCHAR(255),
    PRIMARY KEY(idCliente),
    FOREIGN KEY(idCliente) REFERENCES cliente(idCliente)
);

CREATE TABLE nota (
    numeroNota INTEGER,
    dtPagamento DATE,
    PRIMARY KEY(numeroNota)
);

CREATE TABLE mesa (
    idMesa INTEGER AUTO_INCREMENT,
    PRIMARY KEY(idMesa)
);

CREATE TABLE pedido (
    idPedido INTEGER AUTO_INCREMENT,
    dtPedido DATE,
    motivoCancel VARCHAR(255),
    situacao VARCHAR(255),
    idMesa INTEGER,
    idCliente INTEGER,
    numeroNota INTEGER,
    PRIMARY KEY(idPedido),
    FOREIGN KEY(idMesa) REFERENCES mesa(idMesa),
    FOREIGN KEY(idCliente) REFERENCES cliente(idCliente),
    FOREIGN KEY(numeroNota) REFERENCES nota(numeroNota)
);

CREATE TABLE item_consumo (
    idItem INTEGER AUTO_INCREMENT,
    nomeItem VARCHAR(255),
    precoUnit FLOAT(6, 2),
    descricao VARCHAR(255),
    categoria VARCHAR(255),
    PRIMARY KEY(idItem)
);

CREATE TABLE contem (
    idPedido INTEGER,
    idItem INTEGER,
    quantidade INTEGER,
    FOREIGN KEY(idPedido) REFERENCES pedido(idPedido),
    FOREIGN KEY(idItem) REFERENCES item_consumo(idItem)
);