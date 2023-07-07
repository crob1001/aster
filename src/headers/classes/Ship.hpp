class Ship {
    public:
        Ship(float x, float y);

        void update();

        void updateAngle(bool right);

        void updateVelocity();

        void shoot();

        void killB(int i);

        void render(SDL_Renderer *renderer);

        std::vector<Bullet*> blist;

    private:
        float cooldown = 0;
        float rotSpeed = 5;
        float velocity = .1;
        float angle = -90;
        float size = 10;
        float vx = 0;
        float vy = 0;
        float vr = 0;
        float y, x;
};

void Ship::render(SDL_Renderer *renderer) {
    //add 90 to set origin angle to 90
    SDL_FPoint point_1 = {rotatex(angle + 90, x, y - size, x, y), rotatey(angle + 90, x, y - size, x, y)};
    SDL_FPoint point_2 = {rotatex(angle + 90, x + size, y + size, x, y), rotatey(angle + 90, x + size, y + size, x, y)};
    SDL_FPoint point_3 = {rotatex(angle + 90, x - size, y + size, x, y), rotatey(angle + 90, x - size, y + size, x, y)};

    SDL_FPoint points[] = {
        point_1,
        point_2,
        point_3,
        point_1
    };

    for (Bullet *i : blist) {
        i->render(renderer);
    }

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderDrawLinesF(renderer, points, 4);
}

void Ship::killB(int i) {
    delete blist[i];
    blist.erase(blist.begin() + i);
}

void Ship::shoot() {
    if (cooldown <= 0) {
        blist.push_back(new Bullet(x, y, angle, vx, vy));
        cooldown = 10;
    }
}

void Ship::updateAngle(bool right) {
    if (right) {
        angle += rotSpeed;
    } else {
        angle -= rotSpeed;
    }
}

void Ship::updateVelocity() {
    vx = vx + cos(angle * dtr) * velocity;
    vy = vy + sin(angle * dtr) * velocity;
}

void Ship::update() {
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

    for (int i = 0; i < blist.size(); i++) {
        if (blist[i]->update()) {
            killB(i);
        }
    }

    if (cooldown > 0) {
        cooldown -= 1;
    }
}

Ship::Ship(float x, float y) {
    this->x = x;
    this->y = y;
}