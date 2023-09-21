#include <stdio.h>

void esvazia(int *f, int *r) {
    (*f) = 0;
    (*r) = 0;
}

int enfila(int *fila, int *f, int *r, int n, int k) {
    int prov = ((*r) % n) + 1;
    if (prov != (*f)) {
        (*r) = prov;
        fila[(*r)] = prov;
        if ((*f) == 0) {
            (*f) = 1;
        }
        return (*r);
    } else {
        return -1;
    }
}

int desenfila(int *fila, int *f, int *r, int n) {
    if ((*f) != 0) {
        int k = fila[(*f)];
        if ((*f) == (*r)) {
            esvazia(f, r);
        } else {
            (*f) = ((*f) % n) + 1;
        }
        return k;
    } else {
        return -1;
    }
}

int main() {
    int fila[10], f, r;

    return 0;
}