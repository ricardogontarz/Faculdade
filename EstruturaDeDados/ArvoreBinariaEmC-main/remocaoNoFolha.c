#include "stdlib.h"
#include "stdio.h"

typedef struct no{
    int conteudo;
    struct no* direita;
    struct no* esquerda;
}NO;

typedef struct {
    NO* raiz;
    int tam;
}ArvB;

NO* inserir(NO* raiz, int valor){
    if(raiz == NULL){
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->conteudo = valor;
        novo->direita = NULL;
        novo->esquerda = NULL;
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
    if(raiz == NULL){
        return 0;
    }else{
        return 1 + tamanho(raiz->direita) + tamanho(raiz->esquerda);
    }
}
void imprimir(NO* raiz){
    if(raiz != NULL){
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}
int buscar(NO* raiz, int chave) {
    if (raiz == NULL) {
        return 0;
    } else {
        if (raiz->conteudo == chave) {
            return 1;
        } else {
            if (chave < raiz->conteudo) {
                return buscar(raiz->esquerda, chave);
            } else {
                return buscar(raiz->direita, chave);
            }
        }
    }
}
NO* remover(NO* raiz, int chave){
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    }else{
        if(raiz->conteudo == chave){
            //remove nos folhas
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                return NULL;
            }else{
                //remove nos com um filho
                if(raiz->esquerda == NULL || raiz->direita == NULL){
                    NO* aux;
                    if(raiz->esquerda != NULL){
                        aux = raiz->esquerda;
                    }else{
                        aux = raiz->direita;
                    }
                    free(raiz);
                    return aux;
                }else{
                    NO* aux = raiz->esquerda;
                    while (aux->direita != NULL){
                        aux = aux->direita;
                    }
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                   raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }
            }
        }else{
            if(chave < raiz->conteudo){
                raiz->esquerda = remover(raiz->esquerda, chave);
            }
            if(chave > raiz->conteudo){
                raiz->direita = remover(raiz->direita, chave);
            }
            return raiz;
        }
    }
}
int main(){
    int op, valor;
    ArvB arv;
    arv.raiz = NULL;

    do {
        printf("\n0 - sair\n1 - inserir\n2 - imprimir\n3 - Buscar\n4 - Remover\n");
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
            case 4:
                printf("\nDigite um valor a ser removido: ");
                scanf(" %d", &valor);
                arv.raiz = remover(arv.raiz, valor);
                break;
            default:
                printf("\nOpcao invalida...\n");
                break;
        }
    } while ( op != 0);
}
