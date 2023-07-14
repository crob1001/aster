class Powerup {
    public:

        Powerup(int size, float x, float y, float vx, float vy);

        Powerup(int size);

        void update();

        float getVX();

        float getVY();

        float getX();

        float getY();

        float getSize();

        void render(SDL_Renderer *renderer);

    private:
        float size;
        float y, x;
        float rotSpeed;
        float angle;
        float vx = 0;
        float vy = 0;
};

void Powerup::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
}

float Powerup::getSize(){
    return size;
}

float Powerup::getVX(){
    return vx;
}

float Powerup::getVY(){
    return vy;
}

float Powerup::getX(){
    return x;
}

float Powerup::getY(){
    return y;
}

void Powerup::update() {
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

Powerup::Powerup(int size, float x, float y, float vx, float vy) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->vx = vx + randF(-2, 2);
    this->vy = vy + randF(-2, 2);
    rotSpeed = randF(0, 1.5);
    angle = randF(0, 361);
}

Powerup::Powerup(int size = (int)randF(2,5) * 10) {
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