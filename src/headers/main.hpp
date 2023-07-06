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

        for (auto &i : stars) {
            i = {(int)randF(0, SCREEN_WIDTH - 3), (int)randF(0, SCREEN_HEIGHT - 3)};
        }

        fpsTimer.start();

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
            }

            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            if(currentKeyStates[SDL_SCANCODE_ESCAPE]) {
                running = false;
            }
            if(currentKeyStates[SDL_SCANCODE_UP]) {
                ship->updateVelocity();
            }
            if(currentKeyStates[SDL_SCANCODE_RIGHT]) {
                ship->updateAngle(true);
            }
            if(currentKeyStates[SDL_SCANCODE_LEFT]) {
                ship->updateAngle(false);
            }

            float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
            if(avgFPS > 240) {
                avgFPS = 0;
            }

            ship->update();
            
            window.clearRenderer();

            SDL_SetRenderDrawColor(window.rendererP, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderDrawPoints(window.rendererP, stars, starAmmt);

            ship->render(window.rendererP);

            window.updateRenderer();

            ++countedFrames;
            
            frameTicks = frameTimer.getTicks();
            if (frameTicks < SCREEN_TICK_PER_FRAME) {
                SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks - 1);
            }
        }
    }
    close();
    return 0;
}