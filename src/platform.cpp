SDL_Window* WINDOW;
SDL_Renderer* RENDERER;
int SDLFLAGS = SDL_INIT_VIDEO;
unsigned int SCREEN_WIDTH = 1280;
unsigned int SCREEN_HEIGHT = 720;
int WINDOWFLAGS = SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI;
int MIXERFLAGS = MIX_DEFAULT_FORMAT;
char field_buffer[200];
Mix_Music* testMusic;
unsigned int W_ASPECT_RATIO = 3;
unsigned int H_ASPECT_RATIO = 2;
unsigned int PIXELS = 240;
unsigned int GAME_FRAME_RATE = 60;

const char* data_path = "../data/";

int platformInit(){
    //SDL init
    if( SDL_Init(SDLFLAGS) < 0 ){
	  printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	  return -1;
    }
    //Window init
    WINDOW = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_ASPECT_RATIO * PIXELS, H_ASPECT_RATIO * PIXELS, SDL_WINDOW_SHOWN );
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
	//For high dpi mode macos specifically
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
	if (Mix_OpenAudio(44100, MIXERFLAGS, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return -2;
	}
    return 0;
}

int platformDestroy(){
  SDL_Quit();
  Mix_Quit();
  SDL_DestroyWindow(WINDOW);
  SDL_DestroyRenderer(RENDERER);
  WINDOW = NULL;
  RENDERER = NULL;
  return 0;
}

char* concat(const char* s1, const char* s2){
  printf("size allocation %lu\n", strlen(s1) + strlen(s2) + 1);
  char* result = (char*)calloc(1, strlen(s1) + strlen(s2) + 1);
  strcpy(result, s1);
  strcat(result,s2);
  printf("memory allocated size %lu\n", strlen(result));
  return result;
}

Mix_Music* platformLoadMusic(const char* filepath){
  char* freeMe = concat(data_path, filepath);
  printf("Loading Track: %s",freeMe);
  Mix_Music* musicFilePtr = Mix_LoadMUS(freeMe);
  free(freeMe);
  return musicFilePtr;
}
