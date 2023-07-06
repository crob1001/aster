//built in
#include <stdio.h>
#include <string>
#include <sstream>
#include <math.h>
#include <random>
#include <random>

//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>

//globals
#include "headers/globals.hpp"

//structs
#include "headers/structs/Circle.hpp"


//classes
#include "headers/classes/Window.hpp"
#include "headers/classes/Timer.hpp"
#include "headers/classes/Bullet.hpp"
#include "headers/classes/Ship.hpp"

//declarations
Window window;
std::vector<Bullet*> blist;
Ship *ship = new Ship(window.getWidth() / 2, window.getHeight() / 2);

// functions
#include "headers/functions/init.hpp"
#include "headers/functions/loadMedia.hpp"
#include "headers/functions/collision.hpp"
#include "headers/functions/close.hpp"
#include "headers/functions/random.hpp"
#include "headers/main.hpp"