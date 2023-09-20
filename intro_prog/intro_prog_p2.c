#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Caminho dos arquivos padrão, sempre na mesma pasta que o executavel
#define LIVROS_FILENAME "livros.csv"
#define USUARIOS_FILENAME "usuarios.csv"
#define RESERVAS_FILENAME "reservas.csv"
#define EMPRESTIMOS_FILENAME "emprestimos.csv"

// Salva no formato dia-mes-ano
// EX: 25-12-2022
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char titulo[256];
    char autor[256];
    int numeroDeRegistro;
    int anoDePublicacao;
    char isbn[256];
    int volume;
    char editora[256];
    int valid;
} Livro;

typedef struct {
    int id;
    char nome[256];
    char email[256];
    char senha[256];
    char curso[256];
    int cpf;
    /* 1 para aluno, 2 para docente, 3 para funcionarioBib */
    int tipo;
    int valid;
} Usuario;

typedef struct {
    int id;
    int numeroDeRegistro;
    int valid;
} Reserva;

typedef struct {
    int id;
    int numeroDeRegistro;
    Data dataEmprestimo;
    Data dataDevolucao;
} Emprestimo;

// Função para esperar a confirmacao do usuario antes de proseguir
void waitUser();
void clear();
void GotoXY(int XPos, int YPos);

// Funções relacioandas ao usuario
Usuario login();
Usuario cadastrarUsuario();
int permissao(int tipoUsuario);

// Funções relacionadas a adição ou ateração de informações
int inserirLivro();
int deletarLivro();
int compararDatas(Data primeiraData, Data segundaData);
int registrarEmprestimo();
int renovarEmprestimo();
int registrarReserva();

// Funções de busca
Livro procurarLivroTitulo();
Livro procurarLivroAutor();
Usuario procurarUsuario();

// Funções de print
int listarLivros();
int printLivro(Livro Livro);

// Funções de menu
int menuPrincipal();
int menuBiblioteca();

// Funções relacionadas a leitura e armazenamento dos dados, em arquivos .csv
void arquivosExistem();
void lerArquivos();
void salvarSair();

Livro listaLivros[200];
Usuario listaUsuarios[200];
Reserva listaReservas[200];
Emprestimo listaEmprestimos[200];

int posLivros = 0, posUsuarios = 0, posReservas = 0, posEmprestimos = 0;

int main() {
    // A variavel controle realiza o controle dos menus
    // As variaveis pos marcam a proxima posição das respectivas listas, a posição anterior e a última com valor

    Usuario usuario;
    Livro livroEncontrado;

    int controle;

    arquivosExistem();

    lerArquivos();

    do {
        controle = menuPrincipal();
        switch (controle) {
            case 1:
                usuario = login();
                if (usuario.valid == 0) {
                    printf("Usuario invalido\n");
                    waitUser();
                    break;
                }
                break;
            case 2:
                usuario = cadastrarUsuario();
                break;
            case 3:
                exit(1);
            default:
                printf("Erro na escolha\n");
                exit(0);
        }
    } while (usuario.valid == 0);

    do {
        controle = menuBiblioteca();
        switch (controle) {
            case 1:
                if (permissao(usuario.tipo)) {
                    inserirLivro();
                }
                break;
            case 2:
                livroEncontrado = procurarLivroTitulo();
                printLivro(livroEncontrado);
                break;
            case 3:
                livroEncontrado = procurarLivroAutor();
                printLivro(livroEncontrado);
                break;
            case 4:
                if (permissao(usuario.tipo)) {
                    deletarLivro();
                }
                break;
            case 5:
                listarLivros();
                break;
            case 6:
                if (permissao(usuario.tipo)) {
                    registrarEmprestimo();
                    break;
                }
                break;
            case 7:
                if (permissao(usuario.tipo)) {
                    registrarReserva();
                }
                break;
            case 8:
                renovarEmprestimo();
                break;

            case 9:
                salvarSair();
        }
    } while (1);
}

/*
 * Espera o usuario digitar enter para continuar o codigo
 */
void waitUser() {
    printf("\n");
    fflush(stdin);
    printf("Pressione enter para continuar");
    getchar();
}

/*
 * Limpa o terminal
 */
void clear() { printf("\e[1;1H\e[2J"); }

/*
 * ´Posiciona o cursor na posição de caracter selecionado
 */
void GotoXY(int XPos, int YPos) { printf("\033[%d;%dH", YPos + 1, XPos + 1); }

/*
 * Realiza o login do usuario
 */
Usuario login() {
    clear();

    char email[256], senha[256];
    Usuario usuarioLogado;
    printf("Por favor, digite seu email de usuario: \n");
    printf("Por favor, digite sua senha: ");

    GotoXY(40, 0);
    scanf(" %256[^\n]", email);

    GotoXY(29, 1);
    scanf(" %256[^\n]", senha);

    for (int i = 0; i < posUsuarios; i++) {
        if (strcmp(email, listaUsuarios[i].email) == 0 && strcmp(senha, listaUsuarios[i].senha) == 0) {
            usuarioLogado.id = listaUsuarios[i].id;
            strcpy(usuarioLogado.nome, listaUsuarios[i].nome);
            strcpy(usuarioLogado.email, listaUsuarios[i].email);
            strcpy(usuarioLogado.senha, listaUsuarios[i].senha);
            strcpy(usuarioLogado.curso, listaUsuarios[i].curso);
            usuarioLogado.cpf = listaUsuarios[i].cpf;
            usuarioLogado.tipo = listaUsuarios[i].tipo;
            usuarioLogado.valid = 1;
            return usuarioLogado;
        }
    }

    usuarioLogado.valid = 0;

    return usuarioLogado;
}

/*
 * Realiza o cadastro de um novo usuario e salva na lista
 */
Usuario cadastrarUsuario() {
    clear();

    int ultimoID = 0;
    Usuario novoUsuario;

    printf("Digite o nome: \n");
    printf("Digite o email: \n");
    printf("Digite a senha: \n");
    printf("Digite o curso: \n");
    printf("Digite o cpf, sem formatacao, apenas numeros: \n");
    printf("Digite o tipo de usuario, 1 para aluno, 2 para docente, 3 para funcionario da biblioteca: \n");

    GotoXY(15, 0);
    scanf(" %256[^\n]", novoUsuario.nome);

    GotoXY(16, 1);
    scanf(" %256[^\n]", novoUsuario.email);

    GotoXY(16, 2);
    scanf(" %256[^\n]", novoUsuario.senha);

    GotoXY(16, 3);
    scanf(" %256[^\n]", novoUsuario.curso);

    GotoXY(46, 4);
    scanf(" %d", &novoUsuario.cpf);

    GotoXY(90, 5);
    scanf(" %d", &novoUsuario.tipo);

    printf("tipo: %d\n", novoUsuario.tipo);

    while ((novoUsuario.tipo < 1) && (novoUsuario.tipo > 3)) {
        printf("Tipo de usuario invalido, digite novamente\n");
        printf("Digite o tipo de usuario, 1 para aluno, 2 para docente, 3 para funcionario da biblioteca: ");
        scanf(" %d", &novoUsuario.tipo);
    }

    // Percore a lista de usuarios e procura o último ID cadastrado
    for (int i = 0; i < posUsuarios; ++i) {
        if (listaUsuarios[i].id > ultimoID) {
            ultimoID = listaUsuarios[i].id;
        }
    }
    // Escreve o ‘id’ do usuario apos o último cadastrado
    novoUsuario.id = ultimoID + 1;

    novoUsuario.valid = 1;
    listaUsuarios[posUsuarios] = novoUsuario;

    posUsuarios++;

    printf("\nUsuario cadastrado com sucesso, o sistema realizara login automaticamente\n");

    waitUser();

    return novoUsuario;
}

/*
 * Confere se o usuario possui permissão para acessar a função
 */
int permissao(int tipoUsuario) {
    clear();

    if (tipoUsuario == 3) {
        return 1;
    } else {
        printf("Somente funcionarios da biblioteca podem adicionar acessar essa funcao\n");

        waitUser();

        return 0;
    }
}

/*
 * Realiza o cadastro de um novo livro e salva na lista
 */
int inserirLivro() {
    clear();

    int ultimoRegistro = 0;
    Livro novoLivro;

    printf("Digite o titulo: \n");

    printf("Digite o autor: \n");

    printf("Digite o ano de publicacao: \n");

    printf("Digite o isbn: \n");

    printf("Digite o numero do volume: \n");

    printf("Digite a editora: \n");

    GotoXY(17, 0);
    scanf(" %256[^\n]", novoLivro.titulo);

    GotoXY(16, 1);
    scanf(" %256[^\n]", novoLivro.autor);

    GotoXY(28, 2);
    scanf(" %d", &novoLivro.anoDePublicacao);

    GotoXY(15, 3);
    scanf(" %256[^\n]", novoLivro.isbn);

    GotoXY(27, 4);
    scanf(" %d", &novoLivro.volume);

    GotoXY(18, 5);
    scanf(" %256[^\n]", novoLivro.editora);

    novoLivro.valid = 1;

    // Percore a lista de usuarios e procura o último ID cadastrado
    for (int i = 0; i < posLivros; ++i) {
        if (listaLivros[i].numeroDeRegistro > ultimoRegistro) {
            ultimoRegistro = listaLivros[i].numeroDeRegistro;
        }
    }
    // Escreve o ‘id’ do usuario apos o último cadastrado
    novoLivro.numeroDeRegistro = ultimoRegistro + 1;

    listaLivros[posLivros] = novoLivro;
    posLivros++;

    printf("\nLivro salvo com sucesso\n");

    waitUser();

    return 1;
}

/*
 * Deleta um livro pelo titulo, retorna verdadeiro se o livro foi deletado
 * Retorna 0 se o livro não for encontrado
 * O livro so sera deletado ao sair do programa, rodando a funcao salvarSair
 */
int deletarLivro() {
    clear();

    char titulo[256];
    printf("Digite o nome do livro desejado: ");
    scanf(" %256[^\n]", titulo);

    for (int i = 0; i < posLivros; i++) {
        if (strcmp(listaLivros[i].titulo, titulo) == 0) {
            listaLivros[i].valid = 0;

            printf("\nO livro foi deletado com sucesso\n");

            waitUser();

            return 1;
        };
    }
    printf("\nO livro nao foi encontrado\n");

    waitUser();

    return 0;
}

/*
 * Recebe duas datas e retorna 1 se a primeira for maior, 0 se a segunda for maior
 */
int compararDatas(Data primeiraData, Data segundaData) {
    if (primeiraData.ano > segundaData.ano) {
        return 1;
    } else if (primeiraData.ano < segundaData.ano) {
        return 0;
    } else if (primeiraData.mes > segundaData.mes) {
        return 1;
    } else if (primeiraData.mes < segundaData.mes) {
        return 0;
    } else if (primeiraData.dia > segundaData.dia) {
        return 1;
    } else if (primeiraData.dia < segundaData.dia) {
        return 0;
    } else {
        return 1;
    }
}

/*
 * Registra uma emprestimo no id do usuario desejdo para o id do livro indicado
 */
int registrarEmprestimo() {
    clear();

    char titulo[256], email[256];
    int count = 0, idUsuario, tipoUsuario, numeroRegistro, found = 0, diaHoje, mesHoje, anoHoje, diaEmprestimo,
        mesEmprestimo, anoEmprestimo, diaDevolucao, mesDevolucao, anoDevolucao;

    Data dataAtual;

    printf("Digite a data de hoje no formato, dia/mes/ano: \n");
    printf("Digite o titulo do livro desejado: \n");
    printf("Digite o email do usuario: \n");

    GotoXY(47, 0);
    scanf(" %d/%d/%d", &dataAtual.dia, &dataAtual.ano, &dataAtual.ano);
    GotoXY(35, 1);
    scanf(" %256[^\n]", titulo);
    GotoXY(27, 2);
    scanf(" %256[^\n]", email);

    while (!(dataAtual.dia > 0 && dataAtual.dia <= 31) && !(dataAtual.mes > 0 && dataAtual.mes <= 12)) {
        printf("Data com valores invalidos ou formatação invalida\n");
        printf("Digite a data de emprestimo novamente no formato, dia/mes/ano: ");
        scanf(" %d/%d/%d", &dataAtual.dia, &dataAtual.mes, &dataAtual.ano);
    }

    // Pesquisa na lista de livros
    for (int i = 0; i < posLivros; i++) {
        if ((strcmp(listaLivros[i].titulo, titulo) == 0) && (listaLivros[i].valid == 1)) {
            numeroRegistro = listaLivros[i].numeroDeRegistro;
            found = 1;
        };
    }
    if (found == 0) {
        GotoXY(0, 2);
        printf("\nNão foi possivel encontrar o livro desejado\n");

        waitUser();

        return 0;
    } else {
        found = 0;
    }

    // Pesquisa na lista de usuarios
    for (int i = 0; i < posUsuarios; i++) {
        if (strcmp(listaUsuarios[i].email, email) == 0) {
            idUsuario = listaUsuarios[i].id;
            tipoUsuario = listaUsuarios[i].tipo;
            found = 1;
        }
    }
    if (found == 0) {
        printf("\nNão foi possivel encontrar o usuario desejado\n");

        waitUser();

        return 0;
    }

    // Realiza o check se o usuario pode ralizar o emprestimo
    for (int i = 0; i < posEmprestimos; i++) {
        if ((idUsuario == listaEmprestimos[i].id) &&
            (compararDatas(dataAtual, listaEmprestimos[i].dataDevolucao) == 0)) {
            count++;
        }
    }

    if ((tipoUsuario == 1) && (count >= 2) || (tipoUsuario == 2) && (count >= 3)) {
        printf("\nO usuario desejado ja possui %d emprestimos\n", count - 1);

        waitUser();

        return 0;
    }

    count = 0;

    // Conta a quantidade de reservas do livro
    for (int i = 0; i < posReservas; i++) {
        if (numeroRegistro == listaReservas[i].numeroDeRegistro) {
            count++;
            // Se o usuario possuir uma reserva para o livro selecionado, ao realizar o empretimo a reserva sera marcada
            // para deleção ao rodar a função salvarSiar
            if (idUsuario == listaReservas[i].id) {
                listaReservas[i].valid = 0;
            }
        }
    }

    printf("\nO livro possui %d reservas\n", count);

    printf("\nDigite a data de emprestimo no formato, dia/mes/ano: \n");
    printf("Digite a data de devolucao no formato, dia/mes/ano: \n");

    GotoXY(53, 6);
    scanf(" %d/%d/%d", &diaEmprestimo, &mesEmprestimo, &anoEmprestimo);
    GotoXY(52, 7);
    scanf(" %d/%d/%d", &diaDevolucao, &mesDevolucao, &anoDevolucao);

    while (!(diaEmprestimo > 0 && diaEmprestimo <= 31) && !(mesEmprestimo > 0 && mesEmprestimo <= 12)) {
        printf("Data com valores invalidos ou formatação invalida\n");
        printf("Digite a data de emprestimo novamente no formato, dia/mes/ano: ");
        scanf(" %d/%d/%d", &diaEmprestimo, &mesEmprestimo, &anoEmprestimo);
    }

    while (!(diaDevolucao > 0 && diaDevolucao <= 31) && !(mesDevolucao > 0 && mesDevolucao <= 12)) {
        printf("Data com valores invalidos ou formatação invalida\n");
        printf("Digite a data de devolução novamente no formato, dia/mes/ano: ");
        scanf(" %d/%d/%d", &diaDevolucao, &mesDevolucao, &anoDevolucao);
    }

    listaEmprestimos[posEmprestimos].id = idUsuario;
    listaEmprestimos[posEmprestimos].numeroDeRegistro = numeroRegistro;
    listaEmprestimos[posEmprestimos].dataEmprestimo.dia = diaEmprestimo;
    listaEmprestimos[posEmprestimos].dataEmprestimo.mes = mesEmprestimo;
    listaEmprestimos[posEmprestimos].dataEmprestimo.ano = anoEmprestimo;
    listaEmprestimos[posEmprestimos].dataDevolucao.dia = diaDevolucao;
    listaEmprestimos[posEmprestimos].dataDevolucao.mes = mesDevolucao;
    listaEmprestimos[posEmprestimos].dataDevolucao.ano = anoDevolucao;

    posEmprestimos++;

    printf("\nEmprestimo registrado com sucesso\n");

    waitUser();

    return 1;
}

/*
 * Altera a data de um emprestimo, se as informações forem validas
 */
int renovarEmprestimo() {
    clear();

    char titulo[256], email[256];

    int idUsuario, numeroRegistro, found = 0, posEmprestimoAlterado = 0, diaEmprestimo, mesEmprestimo, anoEmprestimo,
                                   diaDevolucao, mesDevolucao, anoDevolucao;

    Data dataAtual;

    printf("Digite a data de hoje no formato, dia/mes/ano: \n");
    printf("Digite o titulo do livro desejado: \n");
    printf("Digite o email do usuario: \n");

    GotoXY(47, 0);
    scanf(" %d/%d/%d", &dataAtual.dia, &dataAtual.ano, &dataAtual.ano);
    GotoXY(35, 1);
    scanf(" %256[^\n]", titulo);
    GotoXY(27, 2);
    scanf(" %256[^\n]", email);

    // Pesquisa na lista de livros
    for (int i = 0; i < posLivros; i++) {
        if ((strcmp(listaLivros[i].titulo, titulo) == 0) && (listaLivros[i].valid == 1)) {
            numeroRegistro = listaLivros[i].numeroDeRegistro;
            found = 1;
        };
    }
    if (found == 0) {
        GotoXY(0, 2);
        printf("\nNão foi possivel encontrar o livro desejado\n");

        waitUser();

        return 0;
    } else {
        found = 0;
    }

    // Pesquisa na lista de usuarios
    for (int i = 0; i < posUsuarios; i++) {
        if (strcmp(listaUsuarios[i].email, email) == 0) {
            idUsuario = listaUsuarios[i].id;
            found = 1;
        }
    }
    if (found == 0) {
        printf("\nNão foi possivel encontrar o usuario desejado\n");

        waitUser();

        return 0;
    }

    for (int i = 0; i < posEmprestimos; i++) {
        if ((idUsuario == listaEmprestimos[i].id) && (numeroRegistro == listaEmprestimos[i].numeroDeRegistro) &&
            (compararDatas(dataAtual, listaEmprestimos[i].dataDevolucao) == 0)) {
            posEmprestimoAlterado = i;
        }
    }

    if (posEmprestimoAlterado == 0) {
        printf("\nNao foi encontrado um emprestimo com as inforamcoes selecionadas\n");

        waitUser();

        return 0;
    } else {
        printf("\nDigite a data de emprestimo no formato, dia/mes/ano: \n");
        printf("Digite a data de devolucao no formato, dia/mes/ano: \n");

        GotoXY(53, 4);
        scanf(" %d/%d/%d", &diaEmprestimo, &mesEmprestimo, &anoEmprestimo);
        GotoXY(52, 5);
        scanf(" %d/%d/%d", &diaDevolucao, &mesDevolucao, &anoDevolucao);

        while (!(diaEmprestimo > 0 && diaEmprestimo <= 31) && !(mesEmprestimo > 0 && mesEmprestimo <= 12)) {
            printf("Data com valores invalidos ou formatação invalida\n");
            printf("Digite a data de emprestimo novamente no formato, dia/mes/ano: ");
            scanf(" %d/%d/%d", &diaEmprestimo, &mesEmprestimo, &anoEmprestimo);
        }

        while (!(diaDevolucao > 0 && diaDevolucao <= 31) && !(mesDevolucao > 0 && mesDevolucao <= 12)) {
            printf("Data com valores invalidos ou formatação invalida\n");
            printf("Digite a data de devolução novamente no formato, dia/mes/ano: ");
            scanf(" %d/%d/%d", &diaDevolucao, &mesDevolucao, &anoDevolucao);
        }

        listaEmprestimos[posEmprestimoAlterado].dataEmprestimo.dia = diaEmprestimo;
        listaEmprestimos[posEmprestimoAlterado].dataEmprestimo.mes = mesEmprestimo;
        listaEmprestimos[posEmprestimoAlterado].dataEmprestimo.ano = anoEmprestimo;
        listaEmprestimos[posEmprestimoAlterado].dataDevolucao.dia = diaDevolucao;
        listaEmprestimos[posEmprestimoAlterado].dataDevolucao.mes = mesDevolucao;
        listaEmprestimos[posEmprestimoAlterado].dataDevolucao.ano = anoDevolucao;

        printf("\nEmprestimo renovado com sucesso\n");

        waitUser();

        return 1;
    }
}

/*
 * Registra uma reserva no id do usuario desejdo para o id do livro
 * indicado
 */
int registrarReserva() {
    clear();

    char titulo[256];
    char email[256];

    int idUsuario, tipoUsuario, numeroRegistro, found = 0, count = 0;

    printf("Digite o titulo do livro desejado: \n");
    printf("Digite o email do usuario: \n");

    GotoXY(35, 0);
    scanf(" %256[^\n]", titulo);
    GotoXY(27, 1);
    scanf(" %256[^\n]", email);

    // Pesquisa na lista de livros
    for (int i = 0; i < posLivros; i++) {
        if ((strcmp(listaLivros[i].titulo, titulo) == 0) && (listaLivros[i].valid == 1)) {
            numeroRegistro = listaLivros[i].numeroDeRegistro;
            found = 1;
        };
    }
    if (found == 0) {
        GotoXY(0, 2);
        printf("\nNão foi possivel encontrar o livro desejado\n");

        waitUser();

        return 0;
    } else {
        found = 0;
    }

    // Pesquisa na lista de usuarios
    for (int i = 0; i < posUsuarios; i++) {
        if (strcmp(listaUsuarios[i].email, email) == 0) {
            idUsuario = listaUsuarios[i].id;
            tipoUsuario = listaUsuarios[i].tipo;
            found = 1;
        }
    }
    if (found == 0) {
        GotoXY(0, 2);
        printf("\nNão foi possivel encontrar o usuario desejado\n");

        waitUser();

        return 0;
    }

    // Pesquisa se o usuario esta presente na lista de emprestimo
    for (int i = 0; i < posReservas; i++) {
        if (idUsuario == listaReservas[i].id) {
            count++;
        }
    }

    if ((tipoUsuario == 1) && (count < 2) || (tipoUsuario == 2) && (count < 3) || (tipoUsuario == 3)) {
        listaReservas[posReservas].id = idUsuario;
        listaReservas[posReservas].numeroDeRegistro = numeroRegistro;
        listaReservas[posReservas].valid = 1;

        printf("%d", listaReservas[posReservas].id);
        posReservas++;

        printf("\nReserva registrada com sucesso\n");

        waitUser();

        return 1;
    } else {
        printf("\nO usuario desejado ja possui %d reservas registradas\n", count);

        waitUser();

        return 0;
    }
}

/*
 * Realiza a busca de um livro pelo titulo
 */
Livro procurarLivroTitulo() {
    clear();

    Livro livroEncontrado;
    char titulo[256];

    livroEncontrado.valid = 0;

    printf("Digite o titulo do livro desejado: ");
    scanf(" %256[^\n]", titulo);

    for (int i = 0; i < posLivros; i++) {
        if ((strcmp(listaLivros[i].titulo, titulo) == 0) && (listaLivros[i].valid == 1)) {
            strcpy(livroEncontrado.titulo, listaLivros[i].titulo);

            strcpy(livroEncontrado.autor, listaLivros[i].autor);

            livroEncontrado.numeroDeRegistro = listaLivros[i].numeroDeRegistro;

            livroEncontrado.anoDePublicacao = listaLivros[i].anoDePublicacao;

            strcpy(livroEncontrado.isbn, listaLivros[i].isbn);

            livroEncontrado.volume = listaLivros[i].volume;

            strcpy(livroEncontrado.editora, listaLivros[i].editora);

            livroEncontrado.valid = 1;
        };
    }

    return livroEncontrado;
}

/*
 * Realiza a busca de um livro pelo autor
 */
Livro procurarLivroAutor() {
    clear();

    Livro livroEncontrado;
    char autor[256];

    livroEncontrado.valid = 0;

    printf("Digite o nome do autor do livro desejado: ");
    scanf(" %256[^\n]", autor);

    for (int i = 0; i < posLivros; i++) {
        if ((strcmp(listaLivros[i].autor, autor) == 0) && (listaLivros[i].valid == 1)) {
            strcpy(livroEncontrado.titulo, listaLivros[i].titulo);

            strcpy(livroEncontrado.autor, listaLivros[i].autor);

            livroEncontrado.numeroDeRegistro = listaLivros[i].numeroDeRegistro;

            livroEncontrado.anoDePublicacao = listaLivros[i].anoDePublicacao;

            strcpy(livroEncontrado.isbn, listaLivros[i].isbn);

            livroEncontrado.volume = listaLivros[i].volume;

            strcpy(livroEncontrado.editora, listaLivros[i].editora);

            livroEncontrado.valid = 1;

            return livroEncontrado;
        };
    }

    return livroEncontrado;
}

/*
 * Realiza a busca de um usuario pelo email e retorna todos os dados sem a
 * senha
 */
Usuario procurarUsuario() {
    clear();

    Usuario usuarioEncontrado;
    char email[256];
    printf("Digite o email do usuario: ");
    scanf(" %256[^\n]", email);

    for (int i = 0; i < posUsuarios; i++) {
        if (strcmp(listaUsuarios[i].email, email) == 0) {
            usuarioEncontrado.id = listaUsuarios[i].id;

            strcpy(usuarioEncontrado.nome, listaUsuarios[i].nome);

            strcpy(usuarioEncontrado.email, listaUsuarios[i].email);

            strcpy(usuarioEncontrado.curso, listaUsuarios[i].curso);

            usuarioEncontrado.cpf = listaUsuarios[i].cpf;

            usuarioEncontrado.tipo = listaUsuarios[i].tipo;

            usuarioEncontrado.valid = 1;

            return usuarioEncontrado;
        }
    }
    usuarioEncontrado.valid = 0;
    return usuarioEncontrado;
}

/*============================================================================
 * Funções de print
 ============================================================================*/
/*
 * Printa todos os livros lidos do arquivo
 * Printa a contagem de reservas de cada livro
 * Printa os emprestimos autuais de cada livro
 */
int listarLivros() {
    clear();
    for (int i = 0; i < posLivros; i++) {
        if (listaLivros[i].valid == 1) {
            int countReserva = 0, countEmprestimo = 0;
            printf("-------------------------------------------------\n");
            printf("Titulo: %s, Autor: %s\n", listaLivros[i].titulo, listaLivros[i].autor);
            // Percorre a lista de reservas, se o livro for encontrado, aumenta em 1
            for (int j = 0; j < posReservas; j++) {
                if (listaLivros[i].numeroDeRegistro == listaReservas[j].numeroDeRegistro) {
                    countReserva++;
                }
            }
            if (countReserva != 0) {
                printf("Qnt de reservas: %d\n", countReserva);
            }

            // Percorre a lista de emprestimo, para ver se o livro esta contido
            for (int j = 0; j < posEmprestimos; j++) {
                if (listaLivros[i].numeroDeRegistro == listaEmprestimos[j].numeroDeRegistro) {
                    countEmprestimo++;
                    printf("Possui um emprestimo de %d/%d/%d, ate %d/%d/%d\n", listaEmprestimos[j].dataEmprestimo.dia,
                           listaEmprestimos[j].dataEmprestimo.mes, listaEmprestimos[j].dataEmprestimo.ano,
                           listaEmprestimos[j].dataDevolucao.dia, listaEmprestimos[j].dataDevolucao.mes,
                           listaEmprestimos[j].dataDevolucao.ano);
                }
            }
        }
    }

    waitUser();

    return 1;
}

/*
 * Recebe um livro, confima se ele existe, se sim, printa suas informações
 */
int printLivro(Livro livroEncontrado) {
    if (livroEncontrado.valid == 1) {
        printf("Titulo: %s\n", livroEncontrado.titulo);
        printf("Autor: %s\n", livroEncontrado.autor);
        printf("Numero de Registro: %d\n", livroEncontrado.numeroDeRegistro);
        printf("Ano de publicacao: %d\n", livroEncontrado.anoDePublicacao);
        printf("ISBN: %s\n", livroEncontrado.isbn);
        printf("Volume: %d\n", livroEncontrado.volume);
        printf("Editora: %s\n", livroEncontrado.editora);

        waitUser();

        return 1;
    } else {
        printf("\nNão foi encontrado o livro desejado\n");

        waitUser();

        return 0;
    }
}

/*============================================================================
 * Menus de controle
 ============================================================================*/
/*
 * Menu principal para selecionar a opção inicial
 */
int menuPrincipal() {
    clear();

    int controle = 0;
    printf("-------------------Menu principal-------------------\n");
    printf("Digite o numeroa indicado a esquerda da opcao para seleciona-la\n");
    printf("1. Entrar no sistema\n");
    printf("2. Cadastrar usuario\n");
    printf("3. Sair\n");

    printf("Digite a opcao desejada: ");
    scanf(" %d", &controle);

    while (controle != 1 && controle != 2 && controle != 3) {
        printf("Opcao invalida, por favor digite novamente: ");
        scanf(" %d", &controle);
    }

    return controle;
}

/*
 * Menu da biblioteca CEFET para selecionar as opções
 */
int menuBiblioteca() {
    clear();

    int controle = 0;

    printf("-------------------Biblioteca do CEFET-------------------\n");
    printf("Digite o numeroa indicado a esquerda da opcao para seleciona-la\n");
    printf("1. Inserir novo livro\n");
    printf("2. Procurar livro por titulo\n");
    printf("3. Procurar livro por autor\n");
    printf("4. Apagar livro\n");
    printf("5. Listar livros existentes na biblioteca\n");
    printf("6. Regstrar data de emprestimo e devolucao de um livro\n");
    printf("7. Registrar reserva\n");
    printf("8. Renovar emprestimo\n");
    printf("9. Sair\n");

    printf("Digite a opcao desejada: ");
    scanf(" %d", &controle);

    while (controle < 1 || controle > 9) {
        printf("Opcao invalida, por favor digite novamente: ");
        scanf(" %d", &controle);
    }

    return controle;
}

/*============================================================================
 * Leitura e salvament de arquivos
 ============================================================================*/
/*
 * Se os arquivos não exitem criar arquinos
 */
void arquivosExistem() {
    FILE *fileLivros = fopen(LIVROS_FILENAME, "r");
    if (fileLivros == NULL) {
        fileLivros = fopen(LIVROS_FILENAME, "w");
        fclose(fileLivros);
    }

    FILE *fileUsuarios = fopen(USUARIOS_FILENAME, "r");
    if (fileUsuarios == NULL) {
        fileUsuarios = fopen(USUARIOS_FILENAME, "w");
        fclose(fileUsuarios);
    }

    FILE *fileReservas = fopen(RESERVAS_FILENAME, "r");
    if (fileReservas == NULL) {
        fileReservas = fopen(RESERVAS_FILENAME, "w");
        fclose(fileReservas);
    }

    FILE *fileEmprestimos = fopen(EMPRESTIMOS_FILENAME, "r");
    if (fileEmprestimos == NULL) {
        fileEmprestimos = fopen(EMPRESTIMOS_FILENAME, "w");
        fclose(fileEmprestimos);
    }
}

/*
 * Preenche os arrays passados com os dados dos arquivos
 */
void lerArquivos() {
    char linha[1500];
    int qntValoresLidos;

    FILE *fileLivros = fopen(LIVROS_FILENAME, "r");
    FILE *fileUsuarios = fopen(USUARIOS_FILENAME, "r");
    FILE *fileReservas = fopen(RESERVAS_FILENAME, "r");
    FILE *fileEmprestimos = fopen(EMPRESTIMOS_FILENAME, "r");

    // Preencher lista de listaLivros com dados do csv de listaLivros
    if (fileLivros == NULL) {
        printf("Erro ao abrir listaLivros.csv");
        exit(0);
    }
    while (fscanf(fileLivros, "%[^\n] ", linha) != EOF) {
        qntValoresLidos = sscanf(linha, "%[^,],%[^,],%d,%d,%[^,],%d,%[^,]", listaLivros[posLivros].titulo,
                                 listaLivros[posLivros].autor, &listaLivros[posLivros].numeroDeRegistro,
                                 &listaLivros[posLivros].anoDePublicacao, listaLivros[posLivros].isbn,
                                 &listaLivros[posLivros].volume, listaLivros[posLivros].editora);
        listaLivros[posLivros].valid = 1;

        if (qntValoresLidos == 7) {
            posLivros++;
        } else {
            printf("A linha %d, do arquivo listaLivros.csv, esta formatada incorretamanete\n", posLivros);
        }
    }

    // Preencher lista de listaUsuarios com dados do csv de listaUsuarios
    if (fileUsuarios == NULL) {
        printf("Erro ao abrir listaUsuarios.csv\n");
        exit(0);
    }
    while (fscanf(fileUsuarios, "%[^\n] ", linha) != EOF) {
        qntValoresLidos =
            sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d", &listaUsuarios[posUsuarios].id,
                   listaUsuarios[posUsuarios].nome, listaUsuarios[posUsuarios].email, listaUsuarios[posUsuarios].senha,
                   listaUsuarios[posUsuarios].curso, &listaUsuarios[posUsuarios].cpf, &listaUsuarios[posUsuarios].tipo);

        if (qntValoresLidos == 7) {
            posUsuarios++;
        } else {
            printf("A linha %d, do arquivo listaUsuarios.csv, esta formatada incorretamanete\n", posUsuarios);
        }
    }

    // Preencher lista de listaReservas com dados do csv de listaReservas
    if (fileReservas == NULL) {
        printf("Erro ao abrir listaReservas.csv\n");
        exit(0);
    }
    while (fscanf(fileReservas, "%[^\n] ", linha) != EOF) {
        qntValoresLidos =
            sscanf(linha, "%d,%d", &listaReservas[posReservas].id, &listaReservas[posReservas].numeroDeRegistro);
        listaReservas[posReservas].valid = 1;

        if (qntValoresLidos == 2) {
            posReservas++;
        } else {
            printf("A linha %d, do arquivo listaReservas.csv, esta formatada incorretamanete\n", posReservas);
        }
    }

    // Preencher lista de listaEmprestimos com dados do csv de
    // listaEmprestimos
    if (fileEmprestimos == NULL) {
        printf("Erro ao abrir empresimos.csv\n");
        exit(0);
    }
    while (fscanf(fileEmprestimos, "%[^\n] ", linha) != EOF) {
        qntValoresLidos = sscanf(
            linha, "%d,%d,%d/%d/%d,%d/%d/%d", &listaEmprestimos[posEmprestimos].id,
            &listaEmprestimos[posEmprestimos].numeroDeRegistro, &listaEmprestimos[posEmprestimos].dataEmprestimo.dia,
            &listaEmprestimos[posEmprestimos].dataEmprestimo.mes, &listaEmprestimos[posEmprestimos].dataEmprestimo.ano,
            &listaEmprestimos[posEmprestimos].dataDevolucao.dia, &listaEmprestimos[posEmprestimos].dataDevolucao.mes,
            &listaEmprestimos[posEmprestimos].dataDevolucao.ano);

        if (qntValoresLidos == 8) {
            posEmprestimos++;
        } else {
            printf("A linha %d, do arquivo listaEmprestimos.csv, esta formatada incorretamanete\n", posEmprestimos);
        }
    }
    fclose(fileLivros);
    fclose(fileUsuarios);
    fclose(fileReservas);
    fclose(fileEmprestimos);
}

/*
 * Salva os arquivos os dados dos vetores nos arquivos csv e encerra o programa
 */
void salvarSair() {
    clear();
    printf("Salvando os dados\n");

    FILE *fileLivros = fopen(LIVROS_FILENAME, "w");
    FILE *fileUsuarios = fopen(USUARIOS_FILENAME, "w");
    FILE *fileReservas = fopen(RESERVAS_FILENAME, "w");
    FILE *fileEmprestimos = fopen(EMPRESTIMOS_FILENAME, "w");

    for (int i = 0; i < posLivros; ++i) {
        // Confirma se o livro foi deletado durante a run do programa
        // Se valid for falso o livro foi deletado
        if (listaLivros[i].valid == 1) {
            fprintf(fileLivros, "%s,%s,%d,%d,%s,%d,%s\n", listaLivros[i].titulo, listaLivros[i].autor,
                    listaLivros[i].numeroDeRegistro, listaLivros[i].anoDePublicacao, listaLivros[i].isbn,
                    listaLivros[i].volume, listaLivros[i].editora);
        }
    }

    for (int i = 0; i < posUsuarios; ++i) {
        fprintf(fileUsuarios, "%d,%s,%s,%s,%s,%d,%d\n", listaUsuarios[i].id, listaUsuarios[i].nome,
                listaUsuarios[i].email, listaUsuarios[i].senha, listaUsuarios[i].curso, listaUsuarios[i].cpf,
                listaUsuarios[i].tipo);
    }

    for (int i = 0; i < posReservas; ++i) {
        if (listaReservas[i].valid == 1) {
            fprintf(fileReservas, "%d,%d\n", listaReservas[i].id, listaReservas[i].numeroDeRegistro);
        }
    }

    for (int i = 0; i < posEmprestimos; ++i) {
        fprintf(fileEmprestimos, "%d,%d,%d/%d/%d,%d/%d/%d\n", listaEmprestimos[i].id,
                listaEmprestimos[i].numeroDeRegistro, listaEmprestimos[i].dataEmprestimo.dia,
                listaEmprestimos[i].dataEmprestimo.mes, listaEmprestimos[i].dataEmprestimo.ano,
                listaEmprestimos[i].dataDevolucao.dia, listaEmprestimos[i].dataDevolucao.mes,
                listaEmprestimos[i].dataDevolucao.ano);
    }

    fclose(fileLivros);
    fclose(fileUsuarios);
    fclose(fileReservas);
    fclose(fileEmprestimos);

    exit(1);
}