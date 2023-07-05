bool init() {
    //Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Get number of displays
		gTotalDisplays = SDL_GetNumVideoDisplays();
		if( gTotalDisplays < 2 )
		{
			printf( "Warning: Only one display connected!" );
		}
		
		//Get bounds of each display
		gDisplayBounds = new SDL_Rect[ gTotalDisplays ];
		for(int i = 0; i < gTotalDisplays; ++i)
		{
			SDL_GetDisplayBounds(i, &gDisplayBounds[ i ]);
		}

		//Create window
		if( !window.init() )
		{
			success = false;
		}
	}

	return success;
}