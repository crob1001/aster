//static
static std::string PNAME = "aster";

static const double dtr = 0.01745329251994329576923690768489;

SDL_RendererFlags RENDERMETHOD = SDL_RENDERER_ACCELERATED;

enum STATES {
    RUNNING,
    PAUSED,
    LOSE,
    CLOSED,
    TOTAL_STATES
};

int SCREEN_RESOLUTION[7][2] {
    {640, 480},
    {1280, 720},
    {1920, 1080},
    {2560, 1440},
    {3840, 2160},
    {4096, 2160},
    {7680, 4320}
};

enum SCREEN_RESOLUTION_ENUM {
    VGA,
    HD,
    FULL_HD,
    WQHD,
    FOUR_K,
    FIVE_K,
    TOTAL_RESOLUTIONS
};

int RESOLUTION = FULL_HD;

//screen/level size
int SCREEN_WIDTH = SCREEN_RESOLUTION[RESOLUTION][0];
int SCREEN_HEIGHT = SCREEN_RESOLUTION[RESOLUTION][1];
int LEVEL_WIDTH = SCREEN_WIDTH * 2;
int LEVEL_HEIGHT = SCREEN_HEIGHT * 2;

int gTotalDisplays = 0;
SDL_Rect* gDisplayBounds = NULL; 

//fps
int SCREEN_FPS = 60;
float SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

//
SDL_Color colorKey = {0, 0xFF, 0xFF};
SDL_Color backgroundColor = {0x25, 0x19, 0x3c, 0xfe};

STATES CURRENTSTATE = PAUSED;

int starAmmt = 15;
SDL_Point stars[15];