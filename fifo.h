#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

typedef struct el_char{
    char c;
    struct el_char* p_next;
}el_char;

typedef struct fifo_char{
    el_char* el_head;
    el_char* el_tail;
    int length;
}fifo_char;

// PROTOTYPES
void InitializeFifo(fifo_char* fifo); // OK
int AddChar(fifo_char* fifo, char c); // OK
int CutHead(fifo_char* fifo); // OK
int FifoLength(fifo_char* fifo); // OK
struct el_char* FifoHead(fifo_char* fifo); // OK
struct el_char* FifoTail(fifo_char* fifo); // OK
int PrintFifo(fifo_char* fifo); // OK
int PrintChar(el_char* el); // OK
int DestroyFifo(fifo_char* fifo); // OK

#endif // FIFO_H_INCLUDED
