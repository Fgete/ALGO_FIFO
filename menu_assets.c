// Init assets
void Init_Menu_Assets(){
    // Font load
    menu_asset_textFont = TTF_OpenFont("./assets/font/default.ttf", 64);
    if (!menu_asset_textFont)
        printf("default.ttf --- LOAD ERROR !\n");

    // Surfaces load
    menu_asset_sBackground = IMG_Load("./assets/background/default.png");
    if (!menu_asset_sBackground)
        SDL_Log("%s --- LOAD ERROR !\n", menu_asset_sBackground);

    menu_asset_sLagLogo = IMG_Load("./assets/image/lag.png");
    if (!menu_asset_sLagLogo)
        SDL_Log("%s --- LOAD ERROR !\n", menu_asset_sLagLogo);

    menu_asset_sEarth = IMG_Load("./assets/image/earth.png");
    if (!menu_asset_sEarth)
        SDL_Log("%s --- LOAD ERROR !\n", menu_asset_sEarth);
}
