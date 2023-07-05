class Texture {
    public:
        Texture(SDL_Window* window, SDL_Renderer* renderer);

        //Loads image at specified path
        bool loadFromFile(std::string path);

        //Loads image into pixel buffer
        bool loadPixelsFromFile(std::string path);

        //Creates image from preloaded pixels
        bool loadFromPixels();

        //Creates blank texture
        bool createBlank(int width, int height, SDL_TextureAccess access);

        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setAlpha(Uint8 alpha);
        void setBlendMode(SDL_BlendMode blending);

        //Renders texture at given point
        void render(SDL_Rect* clip, SDL_Rect* renderQuad, double angle, SDL_Point* center, SDL_RendererFlip flip);

        //Set self as render target
        void setAsRenderTarget();

        //Pixel accessors
        Uint32* getPixels32();
        Uint32 getPixel32(Uint32 x, Uint32 y);
        Uint32 getPitch32();
        void copyRawPixels32(void* pixels);
        bool lockTexture();
        bool unlockTexture();

        //Gets texture dimensions
        int getWidth();
        int getHeight();

        //Deallocates texture
        void free();

	private:
        //window
        SDL_Window* window;

        //renderer
        SDL_Renderer* renderer;
    
		//hardware texture
        SDL_Texture* texture;

        //Surface pixels
        SDL_Surface* surfacePixels;

        //Raw pixels
        void* rawPixels;
        int rawPitch;

        //dimensions
        int width;
        int height;
};

Texture::Texture(SDL_Window* window, SDL_Renderer* renderer) {
    this->window = window;
    this->renderer = renderer;

    texture = NULL;
    width = 0;
    height = 0;

    surfacePixels = NULL;
    rawPixels = NULL;
    rawPitch = 0;
}

bool Texture::loadFromFile(std::string path) {
    //Load pixels
    if(!loadPixelsFromFile(path)) {
        printf("Texture::loadFromFile@loadPixelsFromFile");
    } else {
        //Load texture from pixels
        if(!loadFromPixels()) {
            printf("Texture::loadFromFile@loadFromPixels");
        }
    }

    //Return success
    return texture != NULL;
}

bool Texture::loadPixelsFromFile(std::string path) {
	//Free preexisting assets
	free();

	//Load image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if(loadedSurface == NULL) {
		printf("Texture::loadPixelsFromFile@loadedSurface | SDL_image Error: %s\n", IMG_GetError());
	} else {
		//Convert surface to display format
		surfacePixels = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(window), 0);
		if(surfacePixels == NULL) {
			printf("Texture::loadPixelsFromFile@surfacePixels | SDL Error: %s\n", SDL_GetError());
		} else {
			width = surfacePixels->w;
			height = surfacePixels->h;
		}
		//Get rid of unneeded surface
		SDL_FreeSurface( loadedSurface );
	}
	return surfacePixels != NULL;
}

bool Texture::loadFromPixels() {
	//loads pixels if they exist
	if(surfacePixels == NULL) {
        printf("SDL Error: %s\n", SDL_GetError());
    } else {
		//Color keys image
		SDL_SetColorKey(surfacePixels, SDL_TRUE, SDL_MapRGB(surfacePixels->format, colorKey.r, colorKey.g, colorKey.b));

		//Creates texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, surfacePixels);
		if(texture == NULL) {
			printf("SDL Error: %s\n", SDL_GetError());
		} else {
			//Get image dimensions
			width = surfacePixels->w;
			height = surfacePixels->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(surfacePixels);
		surfacePixels = NULL;
	}

	//Return success
	return texture != NULL;
}

bool Texture::createBlank(int width, int height, SDL_TextureAccess access) {
	//Get rid of preexisting texture
	free();

	//Create uninitialized texture
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
	if(texture == NULL)
	{
		printf("SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		this->width = width;
		this->height = height;
	}

	return texture != NULL;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(texture, blending);
}

void Texture::render(SDL_Rect* clip = NULL, SDL_Rect* renderQuad = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
	if (renderQuad == NULL) {
		SDL_Rect renderQuad = {0, 0, width, height};
	}

	if(clip != NULL) {
		renderQuad->w = clip->w;
		renderQuad->h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture, clip, renderQuad, angle, center, flip);
}

void Texture::setAsRenderTarget() {
	SDL_SetRenderTarget(renderer, texture);
}

Uint32* Texture::getPixels32() {
	Uint32* pixels = NULL;

	if(surfacePixels != NULL) {
		pixels =  static_cast<Uint32*>(surfacePixels->pixels);
	}

	return pixels;
}

Uint32 Texture::getPitch32() {
	Uint32 pitch = 0;

	if(surfacePixels != NULL) {
		pitch = surfacePixels->pitch / 4;
	}

	return pitch;
}

// bool Texture::updateTexture() {
	
// }

bool Texture::lockTexture() {
	//Texture is already locked
	if(rawPixels != NULL ) {
		return false;
	} else {
        //Lock texture
		if( SDL_LockTexture(texture, NULL, &rawPixels, &rawPitch) != 0 ) {
			printf("SDL Error: %s\n", SDL_GetError());
			return true;
		}
	}
}

bool Texture::unlockTexture() {
	//Texture is not locked
	if(rawPixels == NULL) {
        return false;
	} else {
        //Unlock texture
		SDL_UnlockTexture(texture);
		rawPixels = NULL;
		rawPitch = 0;
        return true;
	}
}

void Texture::copyRawPixels32(void* pixels) {
	//Texture is locked
	if(rawPixels != NULL) {
		//Copy to locked pixels
		SDL_memcpy(rawPixels, pixels, rawPitch * height);
	}
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

void Texture::free() {
	//Free texture if it exists
	if(texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}

	//Free surface if it exists
	if(surfacePixels != NULL) {
		SDL_FreeSurface(surfacePixels);
		surfacePixels = NULL;
	}
}

