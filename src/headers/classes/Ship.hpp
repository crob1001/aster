class Ship {
    public:
        Ship(float x, float y);

        void update();

        void updateAngle(bool right);

        void updateVelocity(bool pos);

        void shoot();

        void killB(int i);

        float getVX();

        float getVY();

        float getX();

        float getY();

        float getSize();

        bool isInvin();

        void render(SDL_Renderer *renderer);

        void kill();

        std::vector<Bullet*> blist;

    private:
        enum POWERSTATE {
            DEFAULT,

        };
        int lives = 5;
        int invin = 0;
        bool hasInvin = false;
        float speedLimit = 10;
        float cooldown = 0;
        float rotSpeed = 6;
        float velocity = .06;
        float angle = -90;
        float size = 10;
        float vx = 0;
        float vy = 0;
        float vr = 0;
        float y, x;
};

void Ship::kill() {
    if (!invin) {
        lives -= 1;
        if (lives <= 0) {
            CURRENTSTATE = LOSE;
        }
        invin = 60;
        hasInvin = true;
    }
}

void Ship::render(SDL_Renderer *renderer) {
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

    if (!hasInvin){
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

float Ship::getVX(){
    return vx;
}

float Ship::getVY(){
    return vy;
}

bool Ship::isInvin() {
    return hasInvin;
}

void Ship::shoot() {
    if (cooldown <= 0) {
        blist.push_back(new Bullet(x, y, angle, vx, vy));
        blist.push_back(new Bullet(x, y, angle + 10, vx, vy));
        blist.push_back(new Bullet(x, y, angle - 10, vx, vy));
        cooldown = 15;
    }
    while (blist.size() > 15) {
        killB(0);
    }
}

void Ship::updateAngle(bool right) {
    if (right) {
        angle += rotSpeed;
    } else {
        angle -= rotSpeed;
    }
}

void Ship::updateVelocity(bool pos) {
    if (pos){
        vx = vx + cos(angle * dtr) * velocity;
        vy = vy + sin(angle * dtr) * velocity;
    } else {
        vx = vx - cos(angle * dtr) * velocity;
        vy = vy - sin(angle * dtr) * velocity;
    }
    if (vx > speedLimit) {
        vx = speedLimit;
    } else if (vx < -1 * speedLimit) {
        vx = -1 * speedLimit;
    }
    if (vy > speedLimit) {
        vy = speedLimit;
    } else if (vy < -1 * speedLimit) {
        vy = -1 * speedLimit;
    }
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
     
    if (invin <= 0) {
        invin = 0;
        hasInvin = false;
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