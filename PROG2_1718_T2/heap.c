/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

heap* heap_nova(int capacidade)
{
  return NULL;
}

int heap_insere(heap * h, const char * texto, int prioridade)
{
  return 0;
}

void heap_apaga(heap *h)
{
  return;
}

char* heap_remove(heap * h)
{
  return NULL;
}

heap* heap_constroi(elemento* v, int n_elementos)
{
  return NULL;
}

int heap_altera_prioridade(heap *h, int indice, int nova_prioridade)
{
  return -1;
}

void mostraHeap(heap *h, int indice)
{
  int i, nivel = 0;
  
  if (indice < h->tamanho)
  {
    i = indice;
    while(i > 1)
    {
      i = i/2;
      nivel++;
    }
    
    mostraHeap(h, indice*2);
    
    for(i = 0; i < 3 * nivel; i++)
      printf("     ");
    
    printf("%s (%d)\n",h->elementos[indice]->valor, h->elementos[indice]->prioridade);
    
    mostraHeap(h, indice*2+1);
  }
}