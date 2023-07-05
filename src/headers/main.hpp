int main(int argc, char *args[]) {

    if (!init()) {
        printf("main/init\n");
    } else {
        bool running = true;

        SDL_Event e;

        Timer fpsTimer;
        Timer frameTimer;
        int countedFrames = 0;
        double frameTicks = 0;
        int dt = 0;
        float avgFPS = 0;

        fpsTimer.start();

        Ship *ship = new Ship(window.getWidth() / 2,window.getHeight() / 2);

        //x = direction, y = speed
        SDL_Point mod = {0,0};

        // Texture text = Texture(window.windowP, window.rendererP);
        // text.loadFromFile("resources/Textures/dot.bmp");

        while (running) {
            frameTimer.start();
            dt = (frameTicks - frameTimer.getTicks() / 1000.f);

            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    running = false;
                } else {
                    window.handleEvent(e);
                }
                if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                    mod = {0,0};
                    if (e.key.keysym.sym == SDLK_UP){
                        mod.y += -2;
                    }
                    if (e.key.keysym.sym == SDLK_DOWN){
                        mod.y += 2;
                    }
                    if (e.key.keysym.sym == SDLK_LEFT){
                        mod.x += -2;
                    }
                    if (e.key.keysym.sym == SDLK_RIGHT){
                        mod.x += 2;
                    }
                }
            }

            printf("%i\n", dt);

            float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
            if(avgFPS > 240) {
                avgFPS = 0;
            }

            ship->move(mod, dt);

            window.clearRenderer();

            ship->render(window.rendererP);

            window.updateRenderer();

            ++countedFrames;
            
            frameTicks = frameTimer.getTicks();
            if (frameTicks < SCREEN_TICK_PER_FRAME) {
                SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
            }
        }
    }
    close();
    return 0;
}