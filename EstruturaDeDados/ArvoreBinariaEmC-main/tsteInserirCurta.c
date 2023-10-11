#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no* esquerda;
    struct no* direita;
}NO;
typedef struct {
    NO* raiz;
    int tam;
}ArvB;

NO* inserir(NO* raiz, int valor){
    if(raiz == NULL){
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }else{
        if(valor < raiz->conteudo){
            raiz->esquerda = inserir(raiz->esquerda, valor);
        }
        if(valor > raiz->conteudo){
            raiz->direita = inserir(raiz->direita, valor);
        }
        return raiz;
    }
}
int tamanho(NO* raiz){
    if (raiz == NULL){
        return 0;
    }else{
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
    }
}
void imprimir(NO* raiz){
    if(raiz != NULL){
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}
int buscar(NO* raiz, int chave){
    if(raiz == NULL){
        return -1;
    }else{
        if(raiz->conteudo == chave){
            return raiz->conteudo;
        }else{
            if(chave < raiz->conteudo){
                return buscar(raiz->esquerda, chave);
            }else{
                return buscar(raiz->direita, chave);
            }

        }
    }
}
int main(){
    int op, valor;
    ArvB arv;
    arv.raiz = NULL;

    do {
        printf("\n0 - sair\n1 - inserir\n2 - imprimir\n3 - Buscar\n");
        scanf(" %d", &op);

        switch (op) {
            case 0:
                printf("\nSaindo...\n");
                break;
            case 1:
                printf("\nDigite um valor: ");
                scanf(" %d", &valor);
                arv.raiz = inserir(arv.raiz, valor);
                break;
            case 2:
                printf("\nimpressao da arvore binaria:\n");
                imprimir(arv.raiz);
                printf("\n");
                printf("Tamanho: %d\n", tamanho(arv.raiz));
                break;
            case 3:
                printf("Qual valor deseja buscar? ");
                scanf(" %d", &valor);
                printf("\nResultado: %d\n", buscar(arv.raiz, valor));
                break;
            default:
                printf("\nOpcao invalida...\n");
                break;
        }
    } while ( op != 0);
}


