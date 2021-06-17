#include <windows.h>
#include <stdio.h>

#include "menu.h"

// Toggle fullscreen
void Toggle_Fullscreen(struct renderer* sRenderer, struct text* tFullscreen){
    if (WINDOW_RATIO == FS_OFF){
        WINDOW_RATIO = FS_ON;
        strcpy(tFullscreen->caption, "Fullscreen ON");
    }else{
        WINDOW_RATIO = FS_OFF;
        strcpy(tFullscreen->caption, "Fullscreen OFF");
    }
    // Redraw screen
    Render_Window(sRenderer);
}

// Menu navigation (it turns the "while"'s state into chosen menu state)
void Menu_Navigation(int* gameState, int* menuState, int menuGameState){
    *gameState = menuGameState;
    *menuState = -1;
}

// Menu title
void Menu_Title(struct renderer sRenderer, int* gameState){
    const int nTitle = 5;
    // Variables
    SDL_Event event;
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color blackOff = {0, 0, 0, 100};
    int titleIndex = 0;
    int titleState = 0;
    // int titleGameState[5] = {1, 3, 4, 5, 6}; // Final states
    int titleGameState[nTitle]; // Temporary states
    titleGameState[0] = 0;
    titleGameState[1] = 0;
    titleGameState[2] = 4;
    titleGameState[3] = 5;
    titleGameState[4] = 6;
    // Objects
    text titles[nTitle];
    text tStart = {{{0, -50, 1},  {.5, .5, 1}}, "Start", black};
    text tContinue = {{{0, 50, 1},  {.5, .5, 1}}, "Continue", black};
    text tOptions = {{{0, 150, 1},  {.5, .5, 1}}, "Options", black};
    text tCredits = {{{0, 250, 1},  {.5, .5, 1}}, "Credits", black};
    text tQuit = {{{0, 350, 1},  {.5, .5, 1}}, "Quit", black};
    titles[0] = tStart;
    titles[1] = tContinue;
    titles[2] = tOptions;
    titles[3] = tCredits;
    titles[4] = tQuit;
    sprite sBackground = {{{0, 0, 0},  {GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 1}}, menu_asset_sBackground, {0, 0}, {1, 1}, 1, 1};
    text tGameTitle = {{{0, -250, 1},  {1, 1, 1}}, GAME_TITLE, black};
    // Event
    while (titleState != -1){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_RETURN: /* VALIDATE */
                        Menu_Navigation(gameState, &titleState, titleGameState[titleIndex]); break;
                    case SDLK_SPACE: /* VALIDATE */
                        Menu_Navigation(gameState, &titleState, titleGameState[titleIndex]); break;
                    case SDLK_KP_ENTER: /* VALIDATE */
                        Menu_Navigation(gameState, &titleState, titleGameState[titleIndex]); break;
                    case SDLK_ESCAPE: /* RETURN */
                        Menu_Navigation(gameState, &titleState, 6); break;
                        break;
                    case SDLK_UP: /* NAVIGATION */
                        if (titleIndex > 0)
                            titleIndex--;
                        else
                            titleIndex = nTitle - 1;
                        break;
                    case SDLK_DOWN: /* NAVIGATION */
                        if (titleIndex < nTitle - 1)
                            titleIndex++;
                        else
                            titleIndex = 0;
                        break;
                    default : break;
                }
            }
            if (event.type == SDL_QUIT){
                Menu_Navigation(gameState, &titleState, -1); break;
            }
            fflush(stdin);
        }
        // Render
        SDL_RenderClear(sRenderer.pRenderer);
        Render_Sprite(sRenderer, &sBackground);
        Render_Text(sRenderer, tGameTitle);
        for (int i = 0; i < nTitle; i++){
            if (i == titleIndex){
                titles[i].color = black;
                Render_Text(sRenderer, titles[i]);
            }else{
                titles[i].color = blackOff;
                Render_Text(sRenderer, titles[i]);
            }
        }
        SDL_RenderPresent(sRenderer.pRenderer);

        // FPS DEBUG
        FPS_Info();
    }
}

// Menu options
void Menu_Options(struct renderer* sRenderer, int* gameState){
    const int nOption = 2;
    // Variables
    SDL_Event event;
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color blackOff = {0, 0, 0, 100};
    int optionIndex = 0;
    int optionState = 0;
    int optionGameState[nOption];
    optionGameState[0] = 4;
    optionGameState[1] = 0;
    char options[nOption][TITLE_LENGTH];
    // Objects
    sprite sBackground = {{{0, 0, 0},  {GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 1}}, menu_asset_sBackground, {0, 0}, {1, 1}, 1, 1};
    text tTitle = {{{0, -250, 1},  {1, 1, 1}}, "Options", black};
    text tFullscreen = {{{-100, -50, 1},  {.5, .5, 1}}, "", black};
    if (WINDOW_RATIO == FS_OFF)
        strcpy(tFullscreen.caption, "Fullscreen OFF");
    else
        strcpy(tFullscreen.caption, "Fullscreen ON");
    text tBack = {{{0, 350, 1},  {.5, .5, 1}}, "Back", black};
    // Event
    while (optionState != -1){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_RETURN: /* VALIDATE */
                            switch (optionIndex){
                                case 0: /*FULLSCREEN*/
                                    Toggle_Fullscreen(sRenderer, &tFullscreen); break;
                                case 1: /*BACK TO MENU*/
                                    Menu_Navigation(gameState, &optionState, optionGameState[optionIndex]); break;
                                default : break;
                            }
                        break;
                    case SDLK_SPACE: /* VALIDATE */
                        switch (optionIndex){
                                case 0: /*FULLSCREEN*/
                                    Toggle_Fullscreen(sRenderer, &tFullscreen); break;
                                case 1: /*BACK TO MENU*/
                                    Menu_Navigation(gameState, &optionState, optionGameState[optionIndex]); break;
                                default : break;
                            }
                        break;
                    case SDLK_KP_ENTER: /* VALIDATE */
                        switch (optionIndex){
                                case 0: /*FULLSCREEN*/
                                    Toggle_Fullscreen(sRenderer, &tFullscreen); break;
                                case 1: /*BACK TO MENU*/
                                    Menu_Navigation(gameState, &optionState, optionGameState[optionIndex]); break;
                                default : break;
                            }
                        break;
                    case SDLK_ESCAPE: /* RETURN */
                        Menu_Navigation(gameState, &optionState, 0);
                        break;
                    case SDLK_UP: /* NAVIGATION */
                        if (optionIndex > 0)
                            optionIndex--;
                        else
                            optionIndex = nOption - 1;
                        break;
                    case SDLK_DOWN: /* NAVIGATION */
                        if (optionIndex < nOption - 1)
                            optionIndex++;
                        else
                            optionIndex = 0;
                        break;
                    default : break;
                }
            }
            if (event.type == SDL_QUIT){
                Menu_Navigation(gameState, &optionState, 0);
            }
            fflush(stdin);
        }
        // Render
        SDL_RenderClear(sRenderer->pRenderer);
        Render_Sprite(*sRenderer, &sBackground);
        Render_Text(*sRenderer, tTitle);
        for (int i = 0; i < nOption - 1; i++){
            if (i == optionIndex){
                tFullscreen.color = black;
                Render_Text(*sRenderer, tFullscreen);
            }else{
                tFullscreen.color = blackOff;
                Render_Text(*sRenderer, tFullscreen);
            }
        }
        if (optionIndex == nOption - 1){
            tBack.color = black;
            Render_Text(*sRenderer, tBack);
        }else{
            tBack.color = blackOff;
            Render_Text(*sRenderer, tBack);
        }
        SDL_RenderPresent(sRenderer->pRenderer);
    }
}

// Menu credits
void Menu_Credits(struct renderer sRenderer, int* gameState){
    // Variables
    SDL_Event event;
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color blackOff = {0, 0, 0, 100};
    int creditsState = 0;
    // Objects
    sprite sBackground = {{{0, 0, 0},  {GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 1}}, menu_asset_sBackground, {0, 0}, {1, 1}, 1, 1};
    sprite sLagLogo = {{{GetSystemMetrics(SM_CXSCREEN) * .5 - 100, GetSystemMetrics(SM_CYSCREEN) * .5 + 100, 1},  {200, 180, 1}}, menu_asset_sLagLogo, {0, 0}, {1, 1}, 1, 1};
    text tTitle = {{{0, -250, 1},  {1, 1, 1}}, "Credits", black};
    text tDev = {{{0, -50, 1},  {.5, .5, 1}}, "Developer", black};
    text tName0 = {{{0, 50, 1},  {.4, .4, 1}}, DEV_NAME0, black};
    text tName1 = {{{0, 100, 1},  {.3, .3, 1}}, DEV_NAME1, blackOff};
    text tBack = {{{0, 350, 1},  {.5, .5, 1}}, "Back", black};
    // Event
    while (creditsState != -1){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_RETURN: /* VALIDATE */
                        Menu_Navigation(gameState, &creditsState, 0); break;
                    case SDLK_SPACE: /* VALIDATE */
                        Menu_Navigation(gameState, &creditsState, 0); break;
                    case SDLK_KP_ENTER: /* VALIDATE */
                        Menu_Navigation(gameState, &creditsState, 0); break;
                    case SDLK_ESCAPE: /* RETURN */
                        Menu_Navigation(gameState, &creditsState, 0); break;
                        break;
                    default : break;
                }
            }
            if (event.type == SDL_QUIT){
                Menu_Navigation(gameState, &creditsState, -1); break;
            }
            fflush(stdin);
        }
        // Render
        SDL_RenderClear(sRenderer.pRenderer);
        // Render_Background(sRenderer);
        Render_Sprite(sRenderer, &sBackground);
        Render_Text(sRenderer, tTitle);
        Render_Text(sRenderer, tDev);
        Render_Text(sRenderer, tName0);
        Render_Text(sRenderer, tName1);
        Render_Text(sRenderer, tBack);
        Render_Sprite(sRenderer, &sLagLogo);
        SDL_RenderPresent(sRenderer.pRenderer);
    }
}

// Menu quit
void Menu_Quit(struct renderer sRenderer, int* gameState){
    const int nQuit = 2;
    // Variables
    SDL_Event event;
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color blackOff = {0, 0, 0, 100};
    int quitIndex = 1;
    int quitState = 0;
    int quitGameState[nQuit];
    quitGameState[0] = -1;
    quitGameState[1] = 0;
    // Objects
    sprite sBackground = {{{0, 0, 0},  {GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 1}}, menu_asset_sBackground, {0, 0}, {1, 1}, 1, 1};
    sprite sEarth = {{{50, 50, 1},  {200, 200, 1}}, menu_asset_sEarth, {1024, 1024}, {16, 16}, 1, 256};
    text tSure = {{{0, 0, 1},  {.5, .5, 1}}, "Are you sure ?", black};
    text quitTitles[nQuit];
    text tYes = {{{-100, 100, 1},  {.5, .5, 1}}, "Yes", black};
    text tNo = {{{100, 100, 1},  {.5, .5, 1}}, "No", black};
    quitTitles[0] = tYes;
    quitTitles[1] = tNo;
    // Events
    while (quitState != -1){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_RETURN: /* VALIDATE */
                        Menu_Navigation(gameState, &quitState, quitGameState[quitIndex]); break;
                    case SDLK_SPACE: /* VALIDATE */
                        Menu_Navigation(gameState, &quitState, quitGameState[quitIndex]); break;
                    case SDLK_KP_ENTER: /* VALIDATE */
                        Menu_Navigation(gameState, &quitState, quitGameState[quitIndex]); break;
                    case SDLK_ESCAPE: /* RETURN */
                        Menu_Navigation(gameState, &quitState, 0); break;
                        break;
                    case SDLK_LEFT: /* NAVIGATION */
                        if (quitIndex > 0)
                            quitIndex--;
                        else
                            quitIndex = nQuit - 1;
                        break;
                    case SDLK_RIGHT: /* NAVIGATION */
                        if (quitIndex < nQuit - 1)
                            quitIndex++;
                        else
                            quitIndex = 0;
                        break;
                    default : break;
                }
            }
            if (event.type == SDL_QUIT){
                Menu_Navigation(gameState, &quitState, -1); break;
            }
            fflush(stdin);
        }
        // Render
        SDL_RenderClear(sRenderer.pRenderer);
        Render_Sprite(sRenderer, &sBackground);
        Render_Sprite(sRenderer, &sEarth);
        Render_Text(sRenderer, tSure);
        for (int i = 0; i < nQuit; i++){
            if (i == quitIndex){
                quitTitles[i].color = black;
                Render_Text(sRenderer, quitTitles[i]);
            }else{
                quitTitles[i].color = blackOff;
                Render_Text(sRenderer, quitTitles[i]);
            }
        }
        SDL_RenderPresent(sRenderer.pRenderer);
    }
}
