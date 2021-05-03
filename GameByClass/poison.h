#pragma once
#include "SDL.h"
#include "SDL_image.h"


class Poison {
public:
	Poison();
	~Poison();

	int i;
	int j;
	void Draw();
	void Renewal();
private:
	SDL_Texture* texture_poison; // the SDL_Texture 
	SDL_Rect source_rectangle_poison; // the rectangle for source image
	SDL_Rect destination_rectangle_poison; // for destination

};