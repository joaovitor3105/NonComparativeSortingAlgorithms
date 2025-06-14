#ifndef RATINGS_READER_H
#define RATINGS_READER_H

#include "data_structures.h"
#include "config.h"

int lerDados_LinearList(LinearList **list, int maxLines, TipoDado tipoDado);

int lerDados_LinearStack(LinearStack **stack, int maxLines, TipoDado tipoDado);

int lerDados_LinearQueue(LinearQueue **queue, int maxLines, TipoDado tipoDado);

int lerDados_LinkedList(LinkedList **list, int maxLines, TipoDado tipoDado);

int lerDados_Stack(Stack **stack, int maxLines, TipoDado tipoDado);

int lerDados_Queue(Queue **queue, int maxLines, TipoDado tipoDado);

int lerDados_PorTipo(void **estrutura, TipoEstrutura tipo, TipoDado tipoDado, int maxLines);

const char *getNomeEstrutura(TipoEstrutura tipo);

#endif