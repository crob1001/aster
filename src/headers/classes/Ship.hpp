class Ship {
    public:

        Ship(int x, int y);

        void move(SDL_Point mod, int dt);

        void render(SDL_Renderer *renderer);

        float velocity, y, x, ;
};

void Ship::render(SDL_Renderer *renderer) {

    float mod = 10;

    SDL_Vertex vertex_1 = {{x, y - mod}, {0, 0, 255, 255}};
    SDL_Vertex vertex_2 = {{x + mod, y + mod}, {0, 0, 255, 255}};
    SDL_Vertex vertex_3 = {{x - mod, y + mod}, {0, 0, 255, 255}};

    SDL_Vertex vertices[] = {
        vertex_1,
        vertex_2,
        vertex_3
    };

    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
}

void Ship::move(SDL_Point mod, int dt) {

}

Ship::Ship(int x, int y) {
}