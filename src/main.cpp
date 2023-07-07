//built in
#include <stdio.h>
#include <string>
#include <sstream>
#include <math.h>
#include <random>
#include <iostream>

//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>

//globals
#include "headers/globals.hpp"

//structs
#include "headers/structs/Circle.hpp"

#include "headers/functions/rotate.hpp"
#include "headers/functions/random.hpp"

//classes
#include "headers/classes/Window.hpp"
#include "headers/classes/Timer.hpp"
#include "headers/classes/Bullet.hpp"
#include "headers/classes/Ship.hpp"
#include "headers/classes/Aster.hpp"

//declarations
Window window;

// functions
#include "headers/functions/init.hpp"
#include "headers/functions/loadMedia.hpp"
#include "headers/functions/collision.hpp"
#include "headers/functions/close.hpp"
#include "headers/main.hpp"