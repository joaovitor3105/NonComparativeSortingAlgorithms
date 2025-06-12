#ifndef RATINGS_READER_H
#define RATINGS_READER_H

#include "data_structures.h"
#include "config.h"

int lerMovieIds_LinearList(LinearList **list, int maxLines);

int lerMovieIds_LinearStack(LinearStack **stack, int maxLines);

int lerMovieIds_LinearQueue(LinearQueue **queue, int maxLines);

int lerMovieIds_LinkedList(LinkedList **list, int maxLines);

int lerMovieIds_Stack(Stack **stack, int maxLines);

int lerMovieIds_Queue(Queue **queue, int maxLines);

int lerMovieIds_PorTipo(void **estrutura, TipoEstrutura tipo, int maxLines);

const char *getNomeEstrutura(TipoEstrutura tipo);

int lerMovieIds(int *movieIds);

#endif