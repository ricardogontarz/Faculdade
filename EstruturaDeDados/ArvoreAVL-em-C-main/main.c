#include <stdio.h>
#include "stdlib.h"
#include "locale.h"
typedef struct no{
    int valor;
    struct no *esquerdo, *direito;
    short altura;
}No;

/*
 *  Função que cria um novo nó
 *  x-> valor a ser inserido no nó
 *  Retorna: o endereço do no criado
 */
No* novoNo(int x){
    No* novo = (No*) malloc(sizeof(No));

    if(novo){
        novo->valor = x;
        novo->direito = NULL;
        novo->esquerdo = NULL;
        novo->altura = 0;
    }else{
        printf("\nERRO ao alocar nó em novoNó!\n");
    }
    return novo;
}

/*
 * Retorna o maior dentre dois valores
 * a, b -> altura de dois nós da árvore
 */
short maior(short a, short b){
    return (a > b)? a: b;
}

//retorna a atura do nó ou -1 caso ele seja null
short alturaDoNo(No* no){
    if(no == NULL){
        return -1;
    }else{
        return no->altura;
    }
}

//calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(No* no){
    if(no){
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    }else{
        return 0;
    }
}
//--------------ROTAÇÕES-------------------------

// função para rotação à esquerda
No* rotacaoEsquerda(No* r){
    No *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->direito), alturaDoNo(r->esquerdo)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

// função para a rotação à direita
No* rotacaoDireita(No* r){
    No *y, *f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

No* rotacaoEsquerdaDireita(No* r){
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);
}
No* rotacaoDireitaEsquerda(No* r){
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}
/*
 * Recebe o nó desbalanceado e retorna a nova raiz após o balanceamento
 */
No* balancear(No* raiz){
    short fb = fatorDeBalanceamento(raiz);

    //Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0 ){
        raiz = rotacaoEsquerda(raiz);
    }
    //Rotação à Direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0){
        raiz = rotacaoDireita(raiz);
    }
    //Rotação dupla à esquerda
    else if(fb < -1 && fatorDeBalanceamento(raiz->esquerdo) < 0){
        raiz = rotacaoEsquerdaDireita(raiz);
    }
    else if(fb > 1 && fatorDeBalanceamento(raiz->direito) > 0){
        raiz = rotacaoDireitaEsquerda(raiz);
    }
    return raiz;

}
/*
 * Insere um novo nó na árvore
 * x -> valor a ser inserido
 * Retorno: endereço do novo nó ou nova raiz após balanceamento
 */
No* inserir(No* raiz, int x){
    if(raiz == NULL){// árvore vazia
        return novoNo(x);
    }else{ // inserção será à esquerda ou à direita
        if( x < raiz->valor){
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        }
        else if (x > raiz->valor){
            raiz->direito = inserir(raiz->direito, x);
        }
        else{
            printf("\nInserção não realizada!\nO elemento %d já existe!", x);
        }
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // Verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}
 /*
  * Função para remover nó da árvore binária
  * Pode ser necessário rebalancear a árvore e a  raiz pode ser alterada
  * por isso precisamos retornar a raiz
  */
 No* remover(No* raiz, int chave){
     if( raiz == NULL){
         printf("Valor não encontrado!\n");
         return NULL;
     }else{ // Procura o nó a remover
         if(raiz->valor == chave){
             //remove nós folhas (nós sem filhos)
             if( raiz->direito == NULL && raiz->esquerdo == NULL){
                 free(raiz);
                 return NULL;
             }else{
                 // Remover nós que possuem 2 filhos
                 if (raiz->esquerdo != NULL && raiz->direito != NULL){
                     No *aux = raiz->esquerdo;
                     while (aux->direito != NULL){
                         aux = aux->direito;
                     }
                     raiz->valor = aux->valor;
                     aux->valor = chave;
                     printf("Elemento trocado: %d !\n", chave);
                     raiz->esquerdo = remover(raiz->esquerdo, chave);
                     return raiz;
                 }else{ // Remover nós com 1 filho
                     No* aux;
                     if( raiz->esquerdo != NULL){
                         aux = raiz->esquerdo;
                     }else{
                         aux = raiz->direito;
                     }
                     free(raiz);
                     printf("Elemento com um filho removido: %d !\n", chave);
                     return aux;
                 }
             }
         }else{
             if( chave < raiz->valor){
                 raiz->esquerdo = remover(raiz->esquerdo, chave);
             }else{
                 raiz->direito = remover(raiz->direito, chave);
             }
         }

         // Recalcula a altura de todos nós entre a raiz e o nov nó inserido
         raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

         // Verifica a necessidade de balancear
         raiz = balancear(raiz);

         return raiz;
     }
 }

 void imprimir(No* raiz, int nivel){
     int i;
     if(raiz){
         imprimir(raiz->direito, nivel + 1);
         printf("\n\n");
         for (i = 0; i < nivel; ++i) {
             printf("\t");
         }
         printf("%d", raiz->valor);
         imprimir(raiz->esquerdo, nivel + 1);
     }
 }

int main() {
    setlocale(LC_ALL,"");

    int opcao, valor;
    No* raiz = NULL;

    do {
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir \n\n");
        scanf(" %d",&opcao);

        switch (opcao) {
            case 0:
                printf("\nSaindo...\n");
                break;
            case 1:
                printf("\tDigite o valor a ser inserido: ");
                scanf(" %d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("\tDigite o valor a ser removido: ");
                scanf(" %d", &valor);
                raiz = remover(raiz, valor);
                break;
            case 3:
                imprimir(raiz, 1);
                break;
            default:
                printf("\nOpção inválida!!!\n");
        }
    } while (opcao != 0);
}
