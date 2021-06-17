#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

void InitializeFifo(fifo_char* fifo){
    fifo->el_head = NULL;
    fifo->el_tail = NULL;
    fifo->length = 0;
}

int AddChar(fifo_char* fifo, char c){
    el_char* el = NULL;
    el = (el_char*)malloc(sizeof(el_char));
    el->c = c;

    if (fifo && el){
        if (!fifo->length)
            fifo->el_head = el;
        else
            fifo->el_tail->p_next = el;
        fifo->el_tail = el;
        fifo->el_tail->p_next = NULL;
        fifo->length++;
    }
    else
        return 0;
    return 1;
}

int CutHead(fifo_char* fifo){
    if (fifo)
        if (!fifo->length)
            return 0;
        else{
            el_char* del;
            del = fifo->el_head;
            fifo->el_head = fifo->el_head->p_next;
            free(del);
            fifo->length--;
            return 1;
        }
}

int FifoLength(fifo_char* fifo){
    if (fifo)
        return fifo->length;
    else
        return -1;
}

struct el_char* FifoHead(fifo_char* fifo){
    el_char* el = NULL;
    el = (el_char*)malloc(sizeof(el_char));

    if (fifo && el)
        if (!fifo->length){
            printf("ERROR -- No element found!");
            return el;
        }
        else
            return fifo->el_head;
    free(el);
}

struct el_char* FifoTail(fifo_char* fifo){
    el_char* el = NULL;
    el = (el_char*)malloc(sizeof(el_char));

    if (fifo && el)
        if (!fifo->length){
            printf("ERROR -- No element found!");
            return el;
        }
        else
            return fifo->el_tail;
    free(el);
}

int PrintFifo(fifo_char* fifo){
    if (fifo)
        if (!fifo->length)
            return 0;
        else{
            el_char* current = NULL;
            current = fifo->el_head;

            printf("String : ");
            while (current != NULL){
                printf("%c", current->c);
                current = current->p_next;
            }
            printf("\n");
            return 1;
        }
    return 0;
}

int PrintChar(el_char* el){
    if (el){
        printf("%c\n", el->c);
        return 1;
    }
    return 0;
}

int DestroyFifo(fifo_char* fifo){
    if (!fifo->length)
        return 0;
    else
        while (fifo->length)
            CutHead(fifo);
    return 1;
}
