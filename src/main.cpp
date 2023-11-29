//built in
#include <stdio.h>
#include <sstream>
#include <math.h>
#include <random>
#include <iostream>

//SDL
#include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>

//globals
#include "headers/globals.hpp"
#include "headers/functions/rotate.hpp"
#include "headers/functions/random.hpp"

//classes
#include "headers/classes/Window.hpp"
#include "headers/classes/Timer.hpp"
#include "headers/classes/Bullet.hpp"
#include "headers/classes/Powerups.hpp"
#include "headers/classes/Ship.hpp"
#include "headers/classes/Aster.hpp"

//declarations
Window window;

// functions
#include "headers/functions/init.hpp"
#include "headers/functions/close.hpp"
#include "headers/functions/collision.hpp"
#include "headers/main.hpp"