class Aster {
    public:

        Aster(int size, float x, float y, float vx, float vy);

        Aster(int size);

        void update();

        float getVX();

        float getVY();

        float getX();

        float getY();

        float getSize();

        void render(SDL_Renderer *renderer);

    private:
        SDL_FPoint points[6];
        float size;
        float y, x;
        float rotSpeed;
        float angle;
        float vx = 0;
        float vy = 0;
};

void Aster::render(SDL_Renderer *renderer) {
    SDL_FPoint points[] = {
        {rotatex(angle, x + (size * cos(0 * dtr)), y + (size * sin(0 * dtr)), x, y), 
            rotatey(angle, x + (size * cos(0 * dtr)), y + (size * sin(0 * dtr)), x, y)},
        {rotatex(angle, x + (size * cos(60 * dtr)), y + (size * sin(60 * dtr)), x, y), 
            rotatey(angle, x + (size * cos(60 * dtr)), y + (size * sin(60 * dtr)), x, y)},
        {rotatex(angle, x + (size * cos(120 * dtr)), y + (size * sin(120 * dtr)), x, y), 
            rotatey(angle, x + (size * cos(120 * dtr)), y + (size * sin(120 * dtr)), x, y)},
        {rotatex(angle, x + (size * cos(180 * dtr)), y + (size * sin(180 * dtr)), x, y), 
            rotatey(angle, x + (size * cos(180 * dtr)), y + (size * sin(180 * dtr)), x, y)},
        {rotatex(angle, x + (size * cos(240 * dtr)), y + (size * sin(240 * dtr)), x, y), 
            rotatey(angle, x + (size * cos(240 * dtr)), y + (size * sin(240 * dtr)), x, y)},
        {rotatex(angle, x + (size * cos(300 * dtr)), y + (size * sin(300 * dtr)), x, y), 
            rotatey(angle, x + (size * cos(300 * dtr)), y + (size * sin(300 * dtr)), x, y)},
        {rotatex(angle, x + (size * cos(0 * dtr)), y + (size * sin(0 * dtr)), x, y), 
            rotatey(angle, x + (size * cos(0 * dtr)), y + (size * sin(0 * dtr)), x, y)}
        // {x + (size * cos(0 * dtr)), y + (size * sin(0 * dtr))},
        // {x + (size * cos(60 * dtr)), y + (size * sin(60 * dtr))},
        // {x + (size * cos(120 * dtr)), y + (size * sin(120 * dtr))},
        // {x + (size * cos(180 * dtr)), y + (size * sin(180 * dtr))},
        // {x + (size * cos(240 * dtr)), y + (size * sin(240 * dtr))},
        // {x + (size * cos(300 * dtr)), y + (size * sin(300 * dtr))},
        // {x + (size * cos(0 * dtr)), y + (size * sin(0 * dtr))}
    };

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderDrawLinesF(renderer, points, 7);
}

float Aster::getSize(){
    return size;
}

float Aster::getVX(){
    return vx;
}

float Aster::getVY(){
    return vy;
}

float Aster::getX(){
    return x;
}

float Aster::getY(){
    return y;
}

void Aster::update() {
    angle += rotSpeed;
    x = x + vx;
    y = y + vy;
    if (x > SCREEN_WIDTH + size) {
        x = 0;
    } if (x < 0) {
        x = SCREEN_WIDTH;
    } if (y > SCREEN_HEIGHT + size) {
        y = 0;
    } if (y < 0) {
        y = SCREEN_HEIGHT;
    }
}

Aster::Aster(int size, float x, float y, float vx, float vy) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->vx = vx + randF(-2, 2);
    this->vy = vy + randF(-2, 2);
    rotSpeed = randF(0, 1.5);
    angle = randF(0, 361);
}

Aster::Aster(int size = (int)randF(2,5) * 10) {
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
    this->size = size;
    vx = randF(-3, 4);
    vy = randF(-3, 4);
    rotSpeed = randF(0, 1.5);
    angle = randF(0, 361);
}