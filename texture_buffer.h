#ifndef TEXTURE_BUFFER_H_INCLUDED
#define TEXTURE_BUFFER_H_INCLUDED

typedef struct el_tex{
    char t;
    struct el_tex* p_next;
}el_tex;

typedef struct fifo_tex{
    el_tex* el_head;
    el_tex* el_tail;
    int length;
}fifo_tex;

// PROTOTYPES
void InitializeFifoTex(fifo_tex* fifo); // OK
int AddTexture(fifo_tex* fifo, SDL_Texture* t); // OK
int CutTextureHead(fifo_tex* fifo); // OK
int FifoTexLength(fifo_tex* fifo); // OK
struct el_tex* FifoTexHead(fifo_tex* fifo); // OK
struct el_tex* FifoTexTail(fifo_tex* fifo); // OK
int PrintFifoTex(fifo_tex* fifo); // OK
int PrintTexture(struct renderer sRenderer, SDL_Texture* t); // OK
int DestroyFifoTex(fifo_tex* fifo); // OK

#endif // TEXTURE_BUFFER_H_INCLUDED
