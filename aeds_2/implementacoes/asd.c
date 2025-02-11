#include<stdio.h>

typedef struct{
    double real;
    double imaginario;
}Complexo;


Complexo criaComplexo(double real, double imaginario){
    Complexo c;
    c.real = real;
    c.imaginario = imaginario;
    return c;
}


Complexo somaComplexo(Complexo c1, Complexo c2){
    Complexo resultado;

    resultado.real = c1.real + c2.real;
    resultado.imaginario = c1.imaginario + c2.imaginario;
    
    return resultado;
}


Complexo produtoComplexo(Complexo c1, Complexo c2){
    Complexo produto;

    produto.real = (c1.real * c2.real) - (c1.imaginario * c2.imaginario);
    produto.imaginario = (c1.real * c2.imaginario) + (c1.imaginario * c2.real);

    return produto;

}

void exibirComplexo(Complexo c){
    printf("%2.lf , %2.lf", c.real, c.imaginario);
}


int main(){
    Complexo c1 = criaComplexo(3.0,4.0);
    Complexo c2 = criaComplexo(1.0, 2.0);


    printf("complexo 1:");
    scanf("%d", &c1);
    // OLA Pedro
    printf("complexo 2:");
    scanf("%d", &c2);

    Complexo soma = somaComplexo(c1, c2);
    Complexo produto = produtoComplexo(c1, c2);

    exibirComplexo(produto);

    return 0;
}