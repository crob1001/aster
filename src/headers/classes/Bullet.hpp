class Bullet {
    public:
        Bullet(float x, float y, float angle, float vx, float vy);

        void updateVelocity();

        void update();

        float velocity = 1;
        float vx, vy;
        float angle;
        float x, y;
};

void Bullet::updateVelocity() {
    vx = vx + cos(angle * dtr) * velocity;
    vy = vy + sin(angle * dtr) * velocity;
}

void Bullet::update() {
    updateVelocity();
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

Bullet::Bullet(float x, float y, float angle, float vx, float vy) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->angle = angle;
}