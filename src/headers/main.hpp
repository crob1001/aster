int main(int argc, char *args[]) {
    if (!init()) {
        printf("main/init\n");
    } else {

        // SDL_SetWindowFullscreen(window.windowP, SDL_WINDOW_FULLSCREEN_DESKTOP);
        // SDL_MaximizeWindow(window.windowP);

        // SDL_DisplayMode DM;
        // SDL_GetCurrentDisplayMode(0, &DM);
        // SCREEN_WIDTH = DM.w;
        // SCREEN_HEIGHT = DM.h;

        // while (CURRENTSTATE != CLOSED) {
            SDL_Event e;

            Timer fpsTimer;
            Timer frameTimer;
            int countedFrames = 0;
            double frameTicks = 0;
            int dt = 0;
            float avgFPS = 0;
            Uint32 score = 0;
            Uint16 asterrate = 0;
            Ship *ship = new Ship(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            std::vector<Aster*> aster;

            for (auto &i : stars) {
                i = {(int)randF(0, SCREEN_WIDTH - 3), (int)randF(0, SCREEN_HEIGHT - 3)};
            }

            fpsTimer.start();

            while (CURRENTSTATE != LOSE && CURRENTSTATE != CLOSED) {
                frameTimer.start();
                dt = (frameTicks - frameTimer.getTicks() / 1000.f);

                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        CURRENTSTATE = CLOSED;
                    } else {
                        window.handleEvent(e);
                    }
                }            

                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                if(currentKeyStates[SDL_SCANCODE_ESCAPE]) {
                    CURRENTSTATE = CLOSED;
                }
                if(currentKeyStates[SDL_SCANCODE_UP]) {
                    ship->updateVelocity(true);
                }
                // if(currentKeyStates[SDL_SCANCODE_DOWN]) {
                //     ship->updateVelocity(false);
                // }
                if(currentKeyStates[SDL_SCANCODE_RIGHT]) {
                    ship->updateAngle(true);
                }
                if(currentKeyStates[SDL_SCANCODE_LEFT]) {
                    ship->updateAngle(false);
                }
                if(currentKeyStates[SDL_SCANCODE_SPACE]) {
                    ship->shoot();
                }

                if(currentKeyStates[SDL_SCANCODE_BACKSPACE]) {
                    aster.clear();
                }
                
                float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
                if(avgFPS > 240) {
                    avgFPS = 0;
                }

                if (aster.size() < 6) {
                    aster.push_back(new Aster());
                }

                ship->update();

                for (auto *i : aster) {
                    i->update();
                }

                //collision detect
                for (int i = 0; i < aster.size(); i++){
                    //ship
                    if (SACollision(ship, aster[i]) && !ship->isInvin()) {
                        ship->kill();
                        if (aster[i]->getSize() > 20 && aster.size() < 120) {
                            for (int l = 0; l <= int(randF(1, 4)); l++) {
                                aster.push_back(new Aster(aster[i]->getSize() - 10, aster[i]->getX(), aster[i]->getY(), 
                                aster[i]->getVX() + (ship->getVX() / (ship->getSize() * ship->getSize())), aster[i]->getVY() + (ship->getVY() / (ship->getSize() * ship->getSize()))));
                            }
                        }
                        delete aster[i];
                        aster.erase(aster.begin() + i);
                    }
                    for (int j = 0; j < ship->blist.size(); j++) {
                        //bullet
                        // if (abs(aster[i]->getX() - ship->blist[j]->getX()) < 100) {
                        //     if (abs(aster[i]->getY() - ship->blist[j]->getY()) < 100) {
                                if (ABCollision(aster[i], ship->blist[j])) {
                                    ship->killB(j);
                                    if (aster[i]->getSize() > 20 && aster.size() < 120) {
                                        for (int l = 0; l <= int(randF(1, 4)); l++) {
                                            aster.push_back(new Aster(aster[i]->getSize() - 10, aster[i]->getX(), aster[i]->getY(), 
                                            aster[i]->getVX() + (ship->blist[j]->getVX() / (ship->blist[j]->getSize() * ship->blist[j]->getSize())), aster[i]->getVY() + (ship->blist[j]->getVY() / (ship->blist[j]->getSize() * ship->blist[j]->getSize()))));
                                        }
                                    }
                                    if (aster[i]->getSize() == 20) {
                                        if ((int)randF(1,10) == 6) {
                                            ;
                                        }
                                    }
                                    score += aster[i]->getSize();
                                    delete aster[i];
                                    aster.erase(aster.begin() + i);
                                }
                        //     }
                        // }
                    }
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
    // }
    close();
    return 0;
}