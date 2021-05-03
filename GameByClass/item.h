#pragma once
#include "SDL.h"
class Item {
public:
	~Item();
	Item();

	int i;
	int j;
	void Draw();
	void Renewal();
private:
	SDL_Texture* texture_apple; // the SDL_Texture 
	SDL_Rect source_rectangle_apple; // the rectangle for source image
	SDL_Rect destination_rectangle_apple; // for destination
};