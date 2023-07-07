int main(int argc, char *args[]) {

    if (!init()) {
        printf("main/init\n");
    } else {

        SDL_Event e;

        Timer fpsTimer;
        Timer frameTimer;
        int countedFrames = 0;
        double frameTicks = 0;
        int dt = 0;
        float avgFPS = 0;

        Uint32 score = 0;

        Uint16 asterrate = 0;

        Ship *ship = new Ship(window.getWidth() / 2, window.getHeight() / 2);

        std::vector<Aster*> aster= {
            new Aster(),
            new Aster(),
            new Aster(),
            new Aster(),
            new Aster(),
            new Aster(),
            new Aster(),
            new Aster()
        };

        for (auto &i : stars) {
            i = {(int)randF(0, SCREEN_WIDTH - 3), (int)randF(0, SCREEN_HEIGHT - 3)};
        }

        fpsTimer.start();

        // Texture text = Texture(window.windowP, window.rendererP);
        // text.loadFromFile("resources/Textures/dot.bmp");

        while (CURRENTSTATE != CLOSED) {
            frameTimer.start();
            dt = (frameTicks - frameTimer.getTicks() / 1000.f);

            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    CURRENTSTATE = CLOSED;
                } else {
                    window.handleEvent(e);
                }
            }            

            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            if(currentKeyStates[SDL_SCANCODE_ESCAPE]) {
                CURRENTSTATE = CLOSED;
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
            if(currentKeyStates[SDL_SCANCODE_SPACE]) {
                ship->shoot();
            }

            float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
            if(avgFPS > 240) {
                avgFPS = 0;
            }

            if (asterrate > 0) {
                asterrate -= 1;
            } else {
                aster.push_back(new Aster());
                asterrate = 120;
            }

            //collision detect
            for (int i = 0; i < aster.size(); i++){
                for (int j = 0; j < ship->blist.size(); j++) {
                    if (((aster[i]->x + aster[i]->size) >= (ship->blist[j]->x + ship->blist[j]->size) && (aster[i]->x - aster[i]->size) <= (ship->blist[j]->x - ship->blist[j]->size))) {
                        if (((aster[i]->y + aster[i]->size) >= (ship->blist[j]->y + ship->blist[j]->size) && (aster[i]->y - aster[i]->size) <= (ship->blist[j]->y - ship->blist[j]->size))) {
                            // delete ship->blist[i];
                            // ship->blist.erase(ship->blist.begin() + i);
                            delete aster[i];
                            aster.erase(aster.begin() + i);
                        }
                    }
                }
            }

            ship->update();

            for (auto *i : aster) {
                i->update();
            }

            
            window.clearRenderer();

            SDL_SetRenderDrawColor(window.rendererP, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderDrawPoints(window.rendererP, stars, starAmmt);

            for (auto *i : aster) {
                i->render(window.rendererP);
            } 

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