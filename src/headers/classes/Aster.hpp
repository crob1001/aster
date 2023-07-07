class Aster {
    public:
        float size;
        float y, x;

        Aster();

        void update();

        void updateVelocity();

        void shatter();

        void render(SDL_Renderer *renderer);

    private:
        SDL_FPoint points[6];
        float rotSpeed;
        float angle;
        float vx = 0;
        float vy = 0;
};

void Aster::render(SDL_Renderer *renderer) {
    //add 90 to set origin angle to 90
    SDL_FPoint points[] = {
        {rotatex(angle + 90, x + size, y, x, y), rotatey(angle + 90, x + size, y, x, y)},
        {rotatex(angle + 90, x + (size * cos(60)), y + (size * sin(60)), x, y), rotatey(angle + 90, x + (size * cos(60)), y + (size * sin(60)), x, y)},
        {rotatex(angle + 90, x + (size * cos(120)), y + (size + sin(120)), x, y), rotatey(angle + 90, x + (size * cos(120)), y + (size + sin(120)), x, y)},
        {rotatex(angle + 90, x - size, y, x, y), rotatey(angle + 90, x - size, y, x, y)},
        {rotatex(angle + 90, x - (size * cos(240)), y + (size * sin(240)), x, y), rotatey(angle + 90, x - (size * cos(240)), y - (size * sin(240)), x, y)},
        {rotatex(angle + 90, x - (size * cos(300)), y + (size * sin(300)), x, y), rotatey(angle + 90, x - (size * cos(300)), y - (size * sin(300)), x, y)},
        {rotatex(angle + 90, x + size, y, x, y), rotatey(angle + 90, x + size, y, x, y)}
    };

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderDrawLinesF(renderer, points, 7);
}

void Aster::update() {
    angle += rotSpeed;
    x = x + vx;
    y = y + vy;
    if (x > SCREEN_WIDTH) {
        x = 0;
    } if (x < 0) {
        x = SCREEN_WIDTH;
    } if (y > SCREEN_HEIGHT) {
        y = 0;
    } if (y < 0) {
        y = SCREEN_HEIGHT;
    }
}

Aster::Aster() {
    switch ((int)randF(1,5)) {
        case 1:
            size = 10;
            break;
        case 2:
            size = 20;
            break;
        case 3:
            size = 30;
            break;
        case 4:
            size = 40;
            break;
    }
    switch ((int)randF(1, 5)) {
        case 1:
            x = 0;
            y = randF(0, SCREEN_HEIGHT + 1);
            break;
        case 2:
            x = SCREEN_WIDTH;
            y = randF(0, SCREEN_HEIGHT + 1);
            break;
        case 3:
            x = randF(0, SCREEN_WIDTH + 1);
            y = 0;
            break;
        case 4:
            x = randF(0, SCREEN_WIDTH + 1);
            y = SCREEN_HEIGHT;
            break;
    }
    vx = randF(-3, 4);
    vy = randF(-3, 4);
    rotSpeed = randF(0, 2);
    angle = randF(0, 361);
}