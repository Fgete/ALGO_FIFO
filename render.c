#include "render.h"
#define WINDOW_RATIO .5

// Render window
void Render_Window(struct renderer* sRenderer){
    if (sRenderer->pWindow)
        SDL_DestroyWindow(sRenderer->pWindow);
    sRenderer->pWindow = SDL_CreateWindow(
        "File de textures SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO,
        GetSystemMetrics(SM_CYSCREEN) * WINDOW_RATIO,
        SDL_WINDOW_SHOWN);
    sRenderer->pRenderer = SDL_CreateRenderer(sRenderer->pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
}
/*
// Render text
void Render_Text(struct renderer sRenderer, struct text text){
    // Sprite
    SDL_Rect titleRect;
    titleRect.w = GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO * .5 * text.transform.scale.x * strlen(text.caption) * .1;
    titleRect.h = GetSystemMetrics(SM_CYSCREEN) * WINDOW_RATIO * .1 * text.transform.scale.y;
    titleRect.x = GetSystemMetrics(SM_CXSCREEN) * WINDOW_RATIO * .5 - titleRect.w * .5 + WINDOW_RATIO * text.transform.position.x;
    titleRect.y = GetSystemMetrics(SM_CYSCREEN) * WINDOW_RATIO * .5 - titleRect.h * .5 + WINDOW_RATIO * text.transform.position.y;
    // Render
    rendererObject renderTitle;
    renderTitle.pSurface = TTF_RenderText_Solid(menu_asset_textFont, text.caption, text.color);
    renderTitle.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, renderTitle.pSurface);
    SDL_FreeSurface(renderTitle.pSurface);
    SDL_RenderCopy(sRenderer.pRenderer, renderTitle.pTexture, NULL, &titleRect);
    SDL_DestroyTexture(renderTitle.pTexture);
}
*/
// Render background
void Render_Sprite(struct renderer sRenderer, struct sprite* sprite){
    // int nTile = 58;
    int frameX = 1;
    int frameY = 1;
    if (sprite->tileCount.x > 0)
        frameX = sprite->frame % (int)sprite->tileCount.x;
    if (sprite->tileCount.y > 0)
        frameY = sprite->frame % (int)sprite->tileCount.y;
    // Sprite
    SDL_Rect imageRect;
    imageRect.x = sprite->transform.position.x * WINDOW_RATIO;
    imageRect.y = sprite->transform.position.y * WINDOW_RATIO;
    imageRect.w = sprite->transform.scale.x * WINDOW_RATIO;
    imageRect.h = sprite->transform.scale.y * WINDOW_RATIO;
    SDL_Rect tileRect;
    tileRect.x = (sprite->spriteSize.x / sprite->tileCount.x) * frameX;
    tileRect.y = (sprite->spriteSize.y / sprite->tileCount.y) * frameY;
    tileRect.w = (sprite->spriteSize.x / sprite->tileCount.x);
    tileRect.h = (sprite->spriteSize.y / sprite->tileCount.y);
    // Render
    rendererObject renderImage;
    renderImage.pSurface = sprite->surface;
    renderImage.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, renderImage.pSurface);
    renderImage.pSurface = NULL; // In order to preserve loaded surfaces
    SDL_FreeSurface(renderImage.pSurface);
    if (sprite->tileCount.x > 1 || sprite->tileCount.y > 1){ // If there is several tiles
        SDL_RenderCopy(sRenderer.pRenderer, renderImage.pTexture, &tileRect, &imageRect);
        if (sprite->frame < sprite->nTile)
            sprite->frame++; // Next tile
        else
            sprite->frame = 1;
        // printf("f : %d\n", sprite->frame);
    }
    else // If there is only one tile
        SDL_RenderCopy(sRenderer.pRenderer, renderImage.pTexture, NULL, &imageRect);
    SDL_DestroyTexture(renderImage.pTexture);
}
