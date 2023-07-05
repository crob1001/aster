class Window {
	public:
		//pointers
		SDL_Window* windowP;
		SDL_Renderer* rendererP;

		//Intializes internals
		Window();

		//Creates windowP
		bool init();

		//Handles windowP events
		void handleEvent(SDL_Event& e);

		void setBorderlessFullScreen();

		//switches screen
		void switchDisplay(int windowDisplayID);

		//Focuses on windowP
		void focus();

		//clears window contents
		void clearRenderer();

		//Shows windows contents
		void updateRenderer();

		//resize windowP
		void updateScreenSize();

		//Deallocates internals
		void free();

		//Window dimensions
		int getWidth();
		int getHeight();

		//Window focii
		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized();
		bool isShown();

		SDL_Window* getWindowPointer();
		SDL_Renderer getRendererPointer();

	private:
		//Window data
		int windowID;
		int windowDisplayID;

		//Window dimensions
		int width;
		int height;

		//Window focus
		bool mouseFocus;
		bool keyboardFocus;
		bool fullScreen;
		bool minimized;
		bool shown;
};

Window::Window() {
	//Initialize window
	windowP = NULL;
	rendererP = NULL;

	mouseFocus = false;
	keyboardFocus = false;
	fullScreen = false;
	shown = false;
	windowID = -1;
	windowDisplayID = -1;
	
	width = 0;
	height = 0;
}

bool Window::init() {
	//Create sdl window
	windowP = SDL_CreateWindow(PNAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(windowP != NULL) {
		mouseFocus = true;
		keyboardFocus = true;
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;

		//Create rendererP for windowP
		rendererP = SDL_CreateRenderer(windowP, -1, RENDERMETHOD);
		if(rendererP == NULL) {
			printf("SDL Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(windowP);
			windowP = NULL;
		} else {
			//Initialize rendererP color
            SDL_SetRenderDrawColor(rendererP, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

			//Grab windowP identifiers
			windowID = SDL_GetWindowID(windowP);
			windowDisplayID = SDL_GetWindowDisplayIndex(windowP);

			//Flag as opened
			shown = true;
		}
	} else {
		printf("SDL Error: %s\n", SDL_GetError());
	}

	return windowP != NULL && rendererP != NULL;
}

void Window::handleEvent(SDL_Event& e) {
	//handle windowP events
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == windowID){
		switch(e.window.event) {
			//Window moved
			case SDL_WINDOWEVENT_MOVED:
				windowDisplayID = SDL_GetWindowDisplayIndex(windowP);
				break;

			//Window appeared
			case SDL_WINDOWEVENT_SHOWN:
				shown = true;
				break;

			//Window disappeared
			case SDL_WINDOWEVENT_HIDDEN:
				shown = false;
				break;

			//Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				width = e.window.data1;
				height = e.window.data2;
				updateScreenSize();
				SDL_RenderPresent(rendererP);
				break;

			//Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(rendererP);
				break;

			//Mouse enter
			case SDL_WINDOWEVENT_ENTER:
				mouseFocus = true;
				break;
			
			//Mouse exit
			case SDL_WINDOWEVENT_LEAVE:
				mouseFocus = false;
				break;

			//Keyboard focus gained
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				keyboardFocus = true;
				break;
			
			//Keyboard focus lost
			case SDL_WINDOWEVENT_FOCUS_LOST:
				keyboardFocus = false;
				break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
				minimized = true;
				break;

			//Window maximized
			case SDL_WINDOWEVENT_MAXIMIZED:
				minimized = false;
				updateScreenSize();
				break;
			
			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
				minimized = false;
				updateScreenSize();
				break;

			//Hide on close
			case SDL_WINDOWEVENT_CLOSE:
				SDL_HideWindow(windowP);
				break;
		}
	}
}

void Window::setBorderlessFullScreen() {
	minimized = false;
	fullScreen = true;
	SDL_SetWindowBordered(windowP, SDL_FALSE);
	SDL_SetWindowFullscreen(windowP, SDL_WINDOW_FULLSCREEN_DESKTOP);
	updateScreenSize();
}

void Window::switchDisplay(int windowDisplayID) {
	//Move windowP to center of next display
	SDL_SetWindowPosition(windowP, gDisplayBounds[windowDisplayID].x + (gDisplayBounds[windowDisplayID].w - width) / 2, gDisplayBounds[windowDisplayID ].y + (gDisplayBounds[windowDisplayID].h - height) / 2);
}

void Window::focus() {
	//Restore windowP if needed
	if(!shown) {
		SDL_ShowWindow(windowP);
	}
	//Move windowP forward
	SDL_RaiseWindow(windowP);
}

void Window::clearRenderer() {
	if(!minimized) {	
		SDL_SetRenderDrawColor(rendererP, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		SDL_RenderClear(rendererP);
	}
}

void Window::updateRenderer() {
	if(!minimized) {	
		SDL_RenderPresent(rendererP);
	}
}

void Window::updateScreenSize() {
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	LEVEL_WIDTH = SCREEN_WIDTH * 2;
	LEVEL_HEIGHT = SCREEN_HEIGHT * 2;
}

void Window::free() {
	if (windowP != NULL) {
		SDL_DestroyWindow(windowP);
	}

	mouseFocus = false;
	keyboardFocus = false;
	width = 0;
	height = 0;
}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

bool Window::hasMouseFocus() {
	return mouseFocus;
}

bool Window::hasKeyboardFocus() {
	return keyboardFocus;
}

bool Window::isMinimized() {
	return minimized;
}

bool Window::isShown() {
	return shown;
}


