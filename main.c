#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>

int slide = 4;
SDL_Surface* sdl_screen, *img, *img2, *tmp;

#ifndef SDL_TRIPLEBUF
#define SDL_TRIPLEBUF SDL_DOUBLEBUF
#endif

uint64_t start;
float real_FPS = (1000 / 60);

#define MAX_SECONDS 2


int main (int argc, char *argv[]) 
{
	SDL_Rect rct;
	SDL_Event event;
	int quit = 0;
	int i;
	int tempsPrecedent = 0, tempsActuel = 0;
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_ShowCursor(0);
	sdl_screen = SDL_SetVideoMode(0, 0, 0, SDL_HWSURFACE | SDL_TRIPLEBUF);
	if (!sdl_screen)
	{
		printf("Can't set video mode\n");
		return 0;
	}
	printf("Video OK ! Width %d, Heigth %d, Bpp %d\n", sdl_screen->w, sdl_screen->h, sdl_screen->format->BytesPerPixel*8);
	
	tmp = SDL_LoadBMP("yes.bmp");
	if (!tmp)
	{
		printf("Could not load yes.bmp image file\n");
		return 0;	
	}
	else
	{
		img = SDL_DisplayFormat(tmp);
		SDL_FreeSurface(tmp);
	}
	
	start = time(NULL); 

	while(!quit)
	{
		while (SDL_PollEvent(&event)) 
		{
			switch(event.type) 
			{
				case SDL_KEYUP:
					switch(event.key.keysym.sym) 
					{
						/*
						 * HOME is for OpenDingux
						 * 3 is for RetroFW
						 * RCTRL is for PocketGo v2
						 * ESCAPE is mapped to Select
						*/
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

		SDL_FillRect( sdl_screen, NULL, 65535);
		SDL_SoftStretch(img, NULL, sdl_screen, NULL);
		SDL_Flip(sdl_screen);
	}
	SDL_FreeSurface(sdl_screen);
	SDL_FreeSurface(img);
	SDL_Quit();
}
