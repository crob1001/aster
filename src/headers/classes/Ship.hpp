class Ship {
    public:
        Ship(float x, float y);

        void update();

        void updateAngle(bool right);

        void updateVelocity();

        void shoot();

        void killB(int i);

        float getX();

        float getY();

        float getSize();

        void render(SDL_Renderer *renderer);

        void kill();

        std::vector<Bullet*> blist;

    private:
        enum POWERSTATE {
            DEFAULT,

        };
        int lives = 5;
        int invin = 0;
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

void Ship::kill() {
    if (invin <= 0) {
        lives -= 1;
        if (lives <= 0) {
            CURRENTSTATE = LOSE;
        }
        invin = 60;
    }
}

void Ship::render(SDL_Renderer *renderer) {
    // switch(RESOLUTION) {
    //     case VGA: 
    //         break;
    //     case HD:
    //         break;
    //     case FULL_HD:
    //         break;
    //     case WQHD:
    //         break;
    //     case FOUR_K:
    //         break;
    //     case FIVE_K:
    //         break;
    // }

    //add 90 to correct for upsidedown render graph
    SDL_FPoint points[] = {
        {rotatex(angle + 90, x, y - size, x, y), rotatey(angle + 90, x, y - size, x, y)},
        {rotatex(angle + 90, x + size, y + size, x, y), rotatey(angle + 90, x + size, y + size, x, y)},
        {rotatex(angle + 90, x - size, y + size, x, y), rotatey(angle + 90, x - size, y + size, x, y)},
        {rotatex(angle + 90, x, y - size, x, y), rotatey(angle + 90, x, y - size, x, y)}
    };

    for (Bullet *i : blist) {
        i->render(renderer);
    }

    if (invin % 2 == 0){
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    } else {
        SDL_SetRenderDrawColor(renderer, 0xff, 0x0, 0x0, 0xff);
    }
    SDL_RenderDrawLinesF(renderer, points, 4);
}

float Ship::getSize(){
    return size / 2;
}

float Ship::getX(){
    return x;
}

float Ship::getY(){
    return y;
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
    
    if (invin > 0) {
        invin -= 1;
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