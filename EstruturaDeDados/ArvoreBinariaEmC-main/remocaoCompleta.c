#include "stdio.h"
#include "stdlib.h"

typedef struct no{
    int conteudo;
    struct no* direita;
    struct no* esquerda;
}NO;
typedef struct{
    NO* raiz;
    int tam;
}ArvB;

NO* inserir(NO* raiz, int valor){
    if( raiz == NULL){
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
int buscar(NO* raiz, int valor){
    if(raiz == NULL){
        printf("\nValor não encontrado!\n");
        return 0;
    }else{
        if(raiz->conteudo == valor){
            return 1;
        }else{
            if(valor < raiz->conteudo){
                return buscar(raiz->esquerda, valor);
            }
            if(valor > raiz->conteudo){
                return buscar(raiz->direita, valor);
            }
        }
    }
}
NO* remover(NO* raiz, int chave){
    if(raiz == NULL){
        printf("valor nao encontrado!\n");
        return NULL;
    }else{
        if(chave == raiz->conteudo){
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                return NULL;
            }
            if(raiz->esquerda == NULL || raiz->direita == NULL){
                NO* aux;
                if(raiz->esquerda != NULL){
                    aux =raiz->esquerda;
                }else{
                    aux = raiz->direita;
                }
                free(raiz);
                return aux;
            }else{
                NO* aux;
                aux = raiz->esquerda;
                while(aux->direita != NULL){
                    aux = aux->direita;
                }
                raiz->conteudo = aux->conteudo;
                aux->conteudo = chave;
                raiz->esquerda = remover(raiz->esquerda, chave);
                return raiz;
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
NO* buscarNO(NO* raiz, int chave){
    if(raiz == NULL){
        printf("No nao encontrado!\n");
        return NULL;
    }else{
        if(raiz->conteudo == chave){
            return raiz;
        }else{
            if(chave < raiz->conteudo){
                return buscarNO(raiz->esquerda, chave);
            }else{
                return buscarNO(raiz->direita, chave);
            }
           ;
        }
    }
}
int alturaArv(NO* raiz){
    if(raiz == NULL || raiz->esquerda == NULL && raiz->direita == NULL){
        return 0;
    }else{
        int esq = 1 + alturaArv(raiz->esquerda);
        int dir = 1 + alturaArv(raiz->direita);
        if(esq > dir){
            return esq;
        }else{
            return dir;
        }
    }
}
int alturaSubArv(NO* raiz, int chave){
    NO* no = buscarNO(raiz, chave);
    if(no){
        return alturaArv(no);
    }else{
        return -1;
    }
}

int main(){
    int op, valor;
    ArvB arv;
    arv.raiz = NULL;

    do {
        printf("\n0 - sair\n1 - inserir\n2 - imprimir\n3 - Buscar\n4 - Remover\n5 - Altura\n6 - Altura subarvore\n");
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
            case 5:
                printf("Altura da arvore e: %d\n", alturaArv(arv.raiz));
                break;
            case 6:
                printf("\nQual valor deseja calcular a altura? ");
                scanf(" %d", &valor);
                printf("altura da subarvore e: %d\n", alturaSubArv(arv.raiz, valor));
                break;
            default:
                printf("\nOpcao invalida...\n");
                break;
        }
    } while ( op != 0);
}
