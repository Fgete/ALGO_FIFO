#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <windows.h>

#include "structure.h"

// PROTOTYPES
void Render_Text(struct renderer, struct text text);
void Render_Sprite(struct renderer, struct sprite*);
void Render_Window(struct renderer*);

#endif // RENDER_H_INCLUDED
