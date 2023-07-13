class Bullet {
    public:
        Bullet(float x, float y, float angle, float vx, float vy);

        float getVX();

        float getVY();

        float getX();

        float getY();

        float getSize();

        bool update();

        void render(SDL_Renderer *renderer);

    private:
        void updateVelocity();
        float velocity = .5;
        float x, y;
        int size = 5;
        float vx, vy;
        float angle;
};

void Bullet::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(renderer, new SDL_Rect({(int)x - (size / 2), (int)y - (size / 2), size ,size}));
}

void Bullet::updateVelocity() {
    vx = vx + cos(angle * dtr) * velocity;
    vy = vy + sin(angle * dtr) * velocity;
}

bool Bullet::update() {
    updateVelocity();
    x = x + vx;
    y = y + vy;
    if (x > SCREEN_WIDTH) {
        return true;
    } if (x < 0) {
        return true;
    } if (y > SCREEN_HEIGHT) {
        return true;
    } if (y < 0) {
        return true;
    } else {
        return false;
    }
}

float Bullet::getSize() {
    return size;
}

float Bullet::getVX() {
    return vx;
}

float Bullet::getVY() {
    return vy;
}

float Bullet::getX() {
    return x;
}

float Bullet::getY() {
    return y;
}

Bullet::Bullet(float x, float y, float angle, float vx, float vy) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->angle = angle;
}