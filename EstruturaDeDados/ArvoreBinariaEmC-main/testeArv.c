#include <stdlib.h>
#include <stdio.h>

typedef struct no{
    int conteudo;
    struct no* esquerda;
    struct no* direita;
}NO;
typedef struct {
    NO* raiz;
}ArvB;
void inserirDireita(NO* no, int valor);
void inserirEsquerda(NO* no, int valor){
    if(no->esquerda == NULL){
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->esquerda = novo;
    }else{
        if(valor < no->esquerda->conteudo){
            inserirEsquerda(no->esquerda, valor);
        }
        if(valor > no->esquerda->conteudo){
            inserirDireita(no->esquerda, valor);
        }
    }
}
void inserirDireita(NO* no, int valor){
    if(no->direita == NULL){
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->direita = novo;
    }else{
        if(valor < no->direita->conteudo){
            inserirEsquerda(no->direita, valor);
        }
        if(valor > no->direita->conteudo){
            inserirDireita(no->direita, valor);
        }
    }
}

void inserir(ArvB* arv, int valor){
    if(arv->raiz == NULL){
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arv->raiz = novo;
    }else{
        if( valor < arv->raiz->conteudo){
            inserirEsquerda(arv->raiz, valor);
        }
        if( valor > arv->raiz->conteudo){
            inserirDireita(arv->raiz, valor);
        }
    }
}

void imprimir(NO* raiz){
    if(raiz != NULL){
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}
int main(){
    int op, valor;
    ArvB arv;
    arv.raiz = NULL;

    do {
        printf("\n0 - sair\n1 - inserir\n2 - imprimir\n");
        scanf(" %d", &op);

        switch (op) {
            case 0:
                printf("\nSaindo...\n");
                break;
            case 1:
                printf("\nDigite um valor: ");
                scanf(" %d", &valor);
                inserir(&arv, valor);

                break;
            case 2:
                printf("\nimpressao da arvore binaria:\n");
                imprimir(arv.raiz);
                break;
            default:
                printf("\nOpcao invalida...\n");
        }
    } while ( op != 0);
}
