#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Window* game_screen;
SDL_Renderer* renderer;

SDL_Surface* tmp;
SDL_Texture *tex;

int main (int argc, char *argv[]) 
{
	SDL_Rect rct;
	SDL_Event event;
	int quit = 0;
	int width = 0;
	int height = 0;
	
	SDL_Init( SDL_INIT_VIDEO );
	game_screen = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);  
	if (!game_screen)
	{
		printf("Can't init SDL2 window\n");
		return 0;
	}
	
	/* Create renderer, its resolution, set to HARDWARE aceleration and Vsync turned on */
	renderer = SDL_CreateRenderer(game_screen, -1, 0);
	SDL_RenderSetLogicalSize(renderer, 0, 0);
	
	/* Clear everything on screen */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	/* Hide the mouse and grab it */
	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	SDL_GetWindowSize(game_screen, &width, &height);
	
	printf("Video OK ! Width %d, Heigth %d\n", width, height);
	
	tmp = SDL_LoadBMP("yes.bmp");
	if (!tmp)
	{
		printf("Could not load yes.bmp image file\n");
		return 0;	
	}
	else
	{
		tex = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}

	while(!quit)
	{
		while (SDL_PollEvent(&event)) 
		{
			switch(event.type) 
			{
				case SDL_KEYUP:
					switch(event.key.keysym.sym) 
					{
						case SDLK_HOME:
						case SDLK_3:
						case SDLK_RCTRL:
						case SDLK_ESCAPE:
							quit = 1;
						break;
						default:
						break;
					}
				break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) 
					{
						case SDLK_LCTRL:
						break;
						default:
						break;
					}
				break;
				case SDL_QUIT:
					quit = 1;
				break;
			}
		}

		SDL_RenderCopy(renderer, tex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(game_screen);
	SDL_Quit();
}
