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

void InitializeFifoTex(fifo_tex* fifo){
    fifo->el_head = NULL;
    fifo->el_tail = NULL;
    fifo->length = 0;
}

int AddTexture(fifo_tex* fifo, SDL_Texture* t){
    el_tex* el = NULL;
    el = (el_tex*)malloc(sizeof(el_tex));
    el->t = t;

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

int CutTextureHead(fifo_tex* fifo){
    if (fifo)
        if (!fifo->length)
            return 0;
        else{
            el_tex* del;
            del = fifo->el_head;
            fifo->el_head = fifo->el_head->p_next;
            free(del);
            fifo->length--;
            return 1;
        }
}

int FifoTexLength(fifo_tex* fifo){
    if (fifo)
        return fifo->length;
    else
        return -1;
}

struct el_tex* FifoTexHead(fifo_tex* fifo){
    el_tex* el = NULL;
    el = (el_tex*)malloc(sizeof(el_tex));

    if (fifo && el)
        if (!fifo->length){
            printf("ERROR -- No element found!");
            return el;
        }
        else
            return fifo->el_head;
    free(el);
}

struct el_tex* FifoTexTail(fifo_tex* fifo){
    el_tex* el = NULL;
    el = (el_tex*)malloc(sizeof(el_tex));

    if (fifo && el)
        if (!fifo->length){
            printf("ERROR -- No element found!");
            return el;
        }
        else
            return fifo->el_tail;
    free(el);
}

int PrintFifoTex(fifo_tex* fifo){ // TODO include render method here
    if (fifo)
        if (!fifo->length)
            return 0;
        else{
            el_tex* current = NULL;
            current = fifo->el_head;

            printf("String : ");
            while (current != NULL){
                printf("%c", current->t);
                current = current->p_next;
            }
            printf("\n");
            return 1;
        }
    return 0;
}

int PrintTexture(struct renderer sRenderer, el_tex* el){ // TODO include render method here
    if (el){
        void Render_Texture(sRenderer, el->t)
        return 1;
    }
    return 0;
}

int DestroyFifoTex(fifo_tex* fifo){
    if (!fifo->length)
        return 0;
    else
        while (fifo->length)
            CutTextureHead(fifo);
    return 1;
}
