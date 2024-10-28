#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo * sig;
}t_nodo;

#endif // NODO_H_INCLUDED
