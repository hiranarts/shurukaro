#include "platform.cpp"
#include <stdio.h>

int main(int argc, char** argv){
  platformInit();
    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(RENDERER, 0, 255, 255, 255);
        SDL_RenderClear(RENDERER);

        SDL_RenderPresent(RENDERER);
    }

    return 0;
}
