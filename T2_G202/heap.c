/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//conforme aula prática

#define RAIZ   (1)
#define PAI(x)    (x/2)
#define Filho_esquerda(x) (x*2)
#define Filho_direita(x)  ((x*2)+1)


void swap(elemento *elem1, elemento *elem2){
    elemento aux;
    aux=*elem1;
    *elem1=*elem2;
    *elem2=aux;
}

/*função usada ao longo das funções pedidas
troca elementos de baixo para cima*/
void troca_para_cima(heap* h, int i, int j){

    h->elementos[i]->prioridade=j;

    while(i!=RAIZ && ((h->elementos[i]->prioridade) < (h->elementos[PAI(i)]->prioridade))){
                    swap(h->elementos[i],(h->elementos[PAI(i)]));
                    i=PAI(i);
    }
}

/*função usada ao longo das funções pedidas
troca elementos de cima para baixo*/
void troca_para_baixo(heap* h, int i, int j){

    int maisprioritario;

    h->elementos[i]->prioridade=j;

    while(Filho_esquerda(i) <= h->tamanho){

        if(Filho_esquerda(i)== h->tamanho){

            if(h->elementos[Filho_esquerda(i)]->prioridade < h->elementos[i]->prioridade){

                swap(h->elementos[Filho_esquerda(i)],h->elementos[i]);
                break;
            }
            break;
        }

        maisprioritario=Filho_esquerda(i);

        if((h->elementos[Filho_direita(i)]->prioridade  < h->elementos[Filho_esquerda(i)]->prioridade) && (h->elementos[Filho_direita(i)]!=NULL)){//assumimos à partida que o mais prioritário é o da esquerda

            maisprioritario=Filho_direita(i);

        }

        if(h->elementos[maisprioritario]->prioridade < h->elementos[PAI(maisprioritario)]->prioridade){

            swap(h->elementos[maisprioritario],h->elementos[PAI(maisprioritario)]);
            i=maisprioritario;
        }
        else break;
    }

}
heap* heap_nova(int capacidade){

    if(capacidade<1){ // não faz sentido poder ter capacidade 0
        return NULL;
    }

    heap *h;
    h=(heap*)malloc(sizeof(heap));

    if(!h){
        return NULL;
    }
    else{
        h->tamanho=0;
        h->capacidade=capacidade;
        h->elementos=(elemento**)calloc((capacidade+1),sizeof(elemento*));
    }

    if(!h->elementos){
        free(h);
        return NULL;
    }

    return h;
}

int heap_insere(heap * h, const char * texto, int prioridade){
    
    if(!h || prioridade <1 || !texto || strlen(texto) < 1 ){//testar os parâmetros
        return 0;
    }
  
    if(h->tamanho>=h->capacidade){ // se a heap está cheia
        return 0;
    }

    int i;

    elemento* elem=(elemento*)malloc(sizeof(elemento));

    if(!elem){ // se ocorreu algum erro a alocar
        free(elem);
        return 0;
    }

    elem->valor = strdup(texto); //função que aloca, testa a alocação e faz strcpy
    elem->prioridade=prioridade;

    (h->tamanho)++;
    i=h->tamanho;
    h->elementos[i] = elem;


    //reordenar heap
    while(i!=RAIZ && ((h->elementos[i]->prioridade) < (h->elementos[PAI(i)]->prioridade))){
        swap(h->elementos[i],(h->elementos[PAI(i)]));
        i=PAI(i);
    }
    return 1;
}


void heap_apaga(heap *h){
    int i;
    if(h==NULL) return;

    for(i=1;i<= (h->tamanho); i++){
        free(h->elementos[i]->valor);
		free(h->elementos[i]);
    }
    free(h->elementos);
    free(h);
    return;
}

char* heap_remove(heap *h){

    if(h==NULL)return NULL; //testar parametros

    char* nomer;
    int maisprioritario;


    if(h->tamanho < 1 || h==NULL){ //se o tamanho for 0 ou o apontador apontar para NULL
        return NULL;
    }

    nomer=strdup(h->elementos[RAIZ]->valor);
    free(h->elementos[RAIZ]->valor);
    free(h->elementos[RAIZ]);

    //se a heap tiver tamanho 1 é só remover o único elemento

    if( h->tamanho == 1){

        h->tamanho--;
        return nomer;
    }
    //para os outros casos
    //colocar o ultimo elemento na raiz

    h->elementos[RAIZ]=h->elementos[h->tamanho];
    h->elementos[h->tamanho]=NULL;
    h->tamanho--;

    int j=RAIZ;

    //reordenar a heap após a remoção
    while(Filho_esquerda(j) < h->tamanho){ //vai só até ao nivel tamanho-1


        maisprioritario=Filho_esquerda(j);//assumimos à partida que o mais prioritário é o da esquerda

        if(h->elementos[Filho_direita(j)]->prioridade < h->elementos[Filho_esquerda(j)]->prioridade &&(h->elementos[Filho_direita(j)]!=NULL)){//verificamos se é o da direita

            maisprioritario=Filho_direita(j);

        }

        //se o pai do mais prioritario tiver um nº de prioridade maior então trocam e atualiza o indice
        if(h->elementos[maisprioritario]->prioridade < h->elementos[PAI(maisprioritario)]->prioridade){

            swap(h->elementos[maisprioritario],h->elementos[PAI(maisprioritario)]);
            j=maisprioritario;
        }
        else break;
    }
  return nomer;
}

heap* heap_constroi(elemento* v, int n_elementos){
    int i;

    if(v==NULL || n_elementos <1){//verificação da correta passagem dos argumentos
        return NULL;
    }

    heap *h;
    h=heap_nova(n_elementos);

    if(h==NULL){//verificação de erros
        return NULL;
    }

    for(i=0;i<n_elementos;i++){

        if(heap_insere(h,v[i].valor,v[i].prioridade)==0){
            return NULL;
        }
    }
    return h;
}

int heap_altera_prioridade(heap *h, int indice, int nova_prioridade){

    if(nova_prioridade <1 || indice <1 || !h || indice > h->tamanho){ //verificações da correta passagem dos argumentos

        return -1;

    }
 
    if(nova_prioridade==h->elementos[indice]->prioridade){//prioridade igual, nao altera
        return 1;
    } 

    if(indice==1){ // é a raíz
        if(nova_prioridade < h->elementos[indice]->prioridade){ //quer se mudar a prioridade da raiz e nova prior e menor
            h->elementos[indice]->prioridade=nova_prioridade;//a estrutura da heap não muda, apenas se atualiza o valor da prioridade
        }

        if(nova_prioridade > h->elementos[indice]->prioridade){ //quer-se mudar a prioridade da raíz e a nova prioridade é maior, i.e, menos prioritária

            troca_para_baixo(h,indice, nova_prioridade);
        }
        return 1;
    }

    else if((h->elementos[Filho_direita(indice)]!=NULL)  && (h->elementos[Filho_esquerda(indice)]!=NULL)){ // não é a raíz, não é a base e tem ambos os filhos


            if(nova_prioridade > h->elementos[indice]->prioridade){ //troca sucessivamente para baixo, é menos prioritario

                troca_para_baixo(h,indice,nova_prioridade);
            }

            else{//troca sucessivamente  para cima

                troca_para_cima(h,indice,nova_prioridade);
            }
        return 1;
    }

    else if(h->elementos[Filho_esquerda(indice)] != NULL && h->elementos[Filho_direita(indice)]==NULL){ //não é a raiz, não está na base e tem apenas o filho da esquerda

        if(nova_prioridade > h->elementos[indice]->prioridade){ //troca sucessivamente para baixo, é menos prioritario

                h->elementos[indice]->prioridade=nova_prioridade;

                if(h->elementos[indice]->prioridade > h->elementos[Filho_esquerda(indice)]->prioridade){

                    swap(h->elementos[indice],h->elementos[Filho_esquerda(indice)]);

                }

        }
        else{//troca sucessivamente para cima

            troca_para_cima(h,indice,nova_prioridade);
        }
        return 1;
    }

    else if( h->elementos[Filho_direita(indice)] == NULL && h->elementos[Filho_esquerda(indice)]==NULL){// está na base

        troca_para_cima(h,indice,nova_prioridade);
        return 1;
    }
    return -1;
}

void mostraHeap(heap *h, int indice)
{
  int i, nivel = 0;

  if (indice <= h->tamanho){
  
    i = indice;
    while(i > 1)
    {
      i = i/2;
      nivel++;
    }

    mostraHeap(h, indice*2);

    for(i = 0; i < 3 * nivel; i++)
      printf("     ");

    printf("[indice %d] %s (%d)\n",indice,h->elementos[indice]->valor, h->elementos[indice]->prioridade);

    mostraHeap(h, indice*2+1);
  }
}
