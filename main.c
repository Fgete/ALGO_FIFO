#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
// SOURCES
#include "fifo.h"

#define WINDOW_RATIO .5

typedef struct renderer{
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
}renderer;

typedef struct el_tex{
    SDL_Texture* t;
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
int PrintFifoTex(struct renderer sRenderer, fifo_tex* fifo); // OK
int PrintTexture(struct renderer sRenderer, SDL_Texture* t); // OK
int DestroyFifoTex(fifo_tex* fifo); // OK

int main(int argc, char *argv[])
{
    /// Cette première partie conserne la File de charactères.
    /// Le code de la File se trouve dans la source "fifo.c".

    fifo_char* string = NULL;
    string = (fifo_char*)malloc(sizeof(fifo_char));

    InitializeFifo(string);

    if (AddChar(string, 'S'))
        printf("Insert char -- OK\n");
    if (AddChar(string, 'o'))
        printf("Insert char -- OK\n");
    if (AddChar(string, 'p'))
        printf("Insert char -- OK\n");

    printf("String length : %d\n", FifoLength(string));

    if (PrintFifo(string))
        printf("Print fifo -- OK\n");

    if (CutHead(string))
        printf("Cut head -- OK\n");
    if (PrintChar(FifoHead(string)))
        printf("Print head -- OK\n");
    if (PrintChar(FifoTail(string)))
        printf("Print tail -- OK\n");

    if (DestroyFifo(string))
        printf("Delete fifo -- OK\n");
    free(string);

    /// Cette seconde partie concerne la file de textures SDL.
    /// Le code de la File de texture se trouve sous le main()
    /// Pas le temps de faire un programme plus propre, desole...

    fflush(stdin);
    getchar();
    printf("\nVoulez vous tester la version SDL ? [Y/N]\n");
    fflush(stdin);

    if (getchar() == 'y' || getchar() == 'Y'){
        // RUN SDL
        printf("Running SDL...\n");

        // Init renderer
        struct renderer sRenderer;
        sRenderer.pWindow = NULL;
        sRenderer.pRenderer = NULL;

        // Load debug
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
            return 1;
        }else{
            SDL_Log("SDL2 -> OK");

            // Draw screen
            if (sRenderer.pWindow)
                SDL_DestroyWindow(sRenderer.pWindow);
            sRenderer.pWindow = SDL_CreateWindow(
                "File de textures SDL",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO,
                GetSystemMetrics(SM_CYSCREEN) * WINDOW_RATIO,
                SDL_WINDOW_SHOWN);
            sRenderer.pRenderer = SDL_CreateRenderer(sRenderer.pWindow, -1, SDL_RENDERER_PRESENTVSYNC);

            // Image init
            int flags = IMG_INIT_JPG|IMG_INIT_PNG;
            int initted = IMG_Init(flags);
            if ((initted & flags) != flags){
                SDL_Log("IMG_Init : Failed to init required .png .jpg support !\n");
                SDL_Log("IMG_Init : %s\n", IMG_GetError());
            }else{
                SDL_Log("SDL_image -> OK");
            }

            // TTF init
            TTF_Init();
            if (TTF_Init() != 0){
                SDL_Log("SDL_TTF -> ERROR");
            }else{
                SDL_Log("SDL_TTF -> OK");
            }

            // ------ PROGRAM ------

            srand(time(0));

            fifo_tex* buffer = NULL;
            buffer = (fifo_tex*)malloc(sizeof(fifo_tex));

            InitializeFifo(buffer);

            SDL_Surface* surfaceA = IMG_Load("./assets/image/s.png");
            SDL_Surface* surfaceB = IMG_Load("./assets/image/o.png");
            SDL_Surface* surfaceC = IMG_Load("./assets/image/p.png");

            SDL_Texture* textureA = SDL_CreateTextureFromSurface(sRenderer.pRenderer, surfaceA);
            SDL_Texture* textureB = SDL_CreateTextureFromSurface(sRenderer.pRenderer, surfaceB);
            SDL_Texture* textureC = SDL_CreateTextureFromSurface(sRenderer.pRenderer, surfaceC);

            if (AddTexture(buffer, textureA))
                printf("Insert texture -- OK\n");
            if (AddTexture(buffer, textureB))
                printf("Insert texture -- OK\n");
            if (AddTexture(buffer, textureC))
                printf("Insert texture -- OK\n");

            printf("Buffer length : %d\n", FifoTexLength(buffer));

            if (PrintFifoTex(sRenderer, buffer))
                printf("Draw buffer -- OK\n");

            if (CutTextureHead(buffer))
                printf("Cut head -- OK\n");
            if (PrintTexture(sRenderer, FifoTexHead(buffer)->t))
                printf("Draw head -- OK\n");
            if (PrintTexture(sRenderer, FifoTexTail(buffer)->t))
                printf("Draw tail -- OK\n");

            if (DestroyFifoTex(buffer))
                printf("Delete buffer -- OK\n");
            free(buffer);

            fflush(stdin);
            getchar();
        }

        // ------ QUIT ------
        SDL_Quit();
        }

    return 0;
}

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

int PrintFifoTex(struct renderer sRenderer, fifo_tex* fifo){ // TODO include render method here
    if (fifo)
        if (!fifo->length)
            return 0;
        else{
            el_tex* current = NULL;
            current = fifo->el_head;

            while (current != NULL){
                PrintTexture(sRenderer, current->t);
                current = current->p_next;
            }
            printf("\n");
            return 1;
        }
    return 0;
}

int PrintTexture(struct renderer sRenderer, SDL_Texture* t){ // TODO include render method here
    SDL_Rect imageRect;
    imageRect.w = 256 * WINDOW_RATIO;
    imageRect.h = 256 * WINDOW_RATIO;
    imageRect.x = GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO * .5 - imageRect.w / 2 + (rand() %
           (200 - (-200) + 1)) + (-200);
    imageRect.y = GetSystemMetrics(SM_CYSCREEN) * WINDOW_RATIO * .5 - imageRect.h / 2 + (rand() %
           (200 - (-200) + 1)) + (-200);
    SDL_RenderCopy(sRenderer.pRenderer, t, NULL, &imageRect);
    SDL_RenderPresent(sRenderer.pRenderer);
    return 1;
}

int DestroyFifoTex(fifo_tex* fifo){
    if (!fifo->length)
        return 0;
    else
        while (fifo->length)
            CutTextureHead(fifo);
    return 1;
}
