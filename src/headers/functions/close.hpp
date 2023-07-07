void close() {
    window.free();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}