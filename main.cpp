#include<SDL.h>
#include<SDL_image.h>
#include<iostream>

const int WIDTH = 1280;
const int HEIGHT = 667;

SDL_Texture* texture = NULL;
SDL_Rect* rect = NULL;
SDL_Renderer* render = NULL;
SDL_Window* window = NULL;

bool Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { std::cerr << "Error! " << SDL_GetError(); return false; }
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) { std::cerr << "Error! " << IMG_GetError(); return false; }
	window = SDL_CreateWindow("SDL2 Texture and Image",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window) { std::cerr << "Error! " << SDL_GetError(); return false; }

	render = SDL_CreateRenderer(window,NULL,NULL);
	if (!render) { std::cerr << "Error! " << SDL_GetError(); return false; }

	rect = new SDL_Rect();
	rect->x = 0;
	rect->y = 0;
	rect->w = WIDTH;
	rect->h = HEIGHT;
	return true
}
bool Load() {
	texture = IMG_LoadTexture(render,"SDL2Image.png");
	if (!texture) { std::cerr << "Error! " << SDL_GetError(); return false; }
	return true;
}
void Draw() {
	SDL_RenderClear(render);
	SDL_RenderCopy(render,texture,NULL, rect);
	SDL_RenderPresent(render);
}

void Quit() {
	SDL_DestroyRenderer(render);
	render = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyTexture(texture);
	texture = NULL;

	delete rect;
	rect = NULL;

	SDL_Quit();
	IMG_Quit();
}

int main(int argc, char ** args) {
	if (!Init()) { return 1; }
	if (!Load()) { return 1; }
	bool run = true;

	SDL_Event* Event = new SDL_Event();
	while (run) {
		while (SDL_PollEvent(Event)) {
			if (Event->type == SDL_QUIT) {
				run = false;
			}			
		}
		Draw();
	}	

	delete Event;
	Event = NULL;
	Quit();
}