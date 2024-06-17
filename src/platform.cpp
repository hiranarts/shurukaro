#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

SDL_Window* WINDOW;
SDL_Renderer* RENDERER;
int SDLFLAGS = SDL_INIT_VIDEO;
unsigned int SCREEN_WIDTH = 1280;
unsigned int SCREEN_HEIGHT = 720;
int WINDOWFLAGS = SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI;
const char data_path[] = "../data/";
int platformInit(){
    //SDL init
    if( SDL_Init(SDLFLAGS) < 0 ){
	printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	return -1;
    }
    //Window init
    WINDOW = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (!WINDOW){
	printf("SDL Window could not be created! SDL_Error: %s\n", SDL_GetError());
	return -1;
    }
    //Renderer init
    RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
    if (!RENDERER){
      printf("SDL Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
      return -1;
    }
	//For high dpi mode and 
	int rw = 0, rh = 0;
	SDL_GetRendererOutputSize(RENDERER, &rw, &rh);
	if (rw != SCREEN_WIDTH || rh != SCREEN_HEIGHT) {
		printf("HIGH DPI on mac or IOS\n");
		float widthScale = (float)rw / (float)SCREEN_WIDTH;
		float heightScale = (float)rh / (float)SCREEN_HEIGHT;

		if (widthScale != heightScale) {
			fprintf(stderr, "WARNING: width scale != height scale\n");
		}

		SDL_RenderSetScale(RENDERER, widthScale, heightScale);
	}
	/*SDL Mixer initialization */
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return -2;
	}

    return 0;
}
