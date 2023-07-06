float rotatex(float angle, float x, float y, float cx, float cy) {
    return cos(angle * dtr) * (x - cx) - sin(angle * dtr) * (y - cy) + cx;
}

float rotatey(float angle, float x, float y, float cx, float cy) {
    return sin(angle * dtr) * (x - cx) + cos(angle * dtr) * (y - cy) + cy;
}

class Ship {
    public:
        Ship(float x, float y);

        void update();

        void updateAngle(bool right);

        void updateVelocity();

        void shoot();

        void render(SDL_Renderer *renderer);

    private:
        float cooldown = 0;
        float rotSpeed = 6;
        float velocity = .2;
        float angle = -90;
        float size = 10;
        float vx = 0;
        float vy = 0;
        float vr = 0;
        float y, x;
};

void Ship::render(SDL_Renderer *renderer) {

    //add 90 to set origin angle to 90
    SDL_Vertex vertex_1 = {{rotatex(angle + 90, x, y - size, x, y), rotatey(angle + 90, x, y - size, x, y)}, {0x4d, 0x4d, 0xff, 255}};
    SDL_Vertex vertex_2 = {{rotatex(angle + 90, x + size, y + size, x, y), rotatey(angle + 90, x + size, y + size, x, y)}, {0xe4, 0xe3, 0xff, 255}};
    SDL_Vertex vertex_3 = {{rotatex(angle + 90, x - size, y + size, x, y), rotatey(angle + 90, x - size, y + size, x, y)}, {0xe4, 0xe3, 0xff, 255}};

    SDL_Vertex vertices[] = {
        vertex_1,
        vertex_2,
        vertex_3
    };

    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
}

void Ship::shoot() {
    if (cooldown <= 0) {
        blist.push_back(new Bullet(x, y, angle, vx, vy));
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
    if (cooldown > 0) {
        cooldown -= 1;
    }
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

Ship::Ship(float x, float y) {
    this->x = x;
    this->y = y;
}