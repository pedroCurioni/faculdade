#include "cliente.h"
#include "produto.h"
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Menu principal do programa utilizado para chamar os menus secundarios
 *
 */
void menu_principal(struct Produto *cab_produto);

/**
 * @brief Menu de seleção das opções de gerenciamento dos produtos
 *
 */
void menu_gerenciador(struct Produto *cab_produto);

/**
 * @brief Menu de seleção das opções de busca dos produtos
 *
 */
void menu_busca(struct Produto *cab_produto);

/**
 * @brief Menu de seleção das opções de gerenciamento dos dados dos usuarios
 *
 */
void menu_cadastro();

/**
 * @brief Menu de seleção das opções do carrinho de compras
 *
 */
void menu_carrinho();