#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// STRUCT
typedef struct renderer{
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
}renderer;

typedef struct rendererObject{
    SDL_Surface *pSurface;
    SDL_Texture *pTexture;
}rendererObject;

typedef struct vector3{
    float x;
    float y;
    float z;
}vector3;

typedef struct vector2{
    float x;
    float y;
}vector2;

typedef struct transform{
    vector3 position;
    // vector3 rotation;
    vector3 scale;
}transform;

typedef struct sprite{
    transform transform;
    SDL_Surface *surface;
    vector2 spriteSize; // Tile size
    vector2 tileCount; // Number of rows and columns
    int frame; // Current tile
    int nTile; // Number of tiles
}sprite;

#endif // STRUCTURE_H_INCLUDED
