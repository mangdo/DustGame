#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "item.h"
#include "poison.h"

class Stage1
{
public:
	Stage1();
	~Stage1();

	void HandleEvents();
	void Update();
	void Render();
	void Renewal();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	SDL_Texture* texture_snakeHead; // the SDL_Texture 
	SDL_Rect source_rectangle_snakeHead; // the rectangle for source image
	SDL_Rect destination_rectangle_snakeHead; // for destination

	SDL_Texture* texture_snake; // the SDL_Texture 
	SDL_Rect source_rectangle_snake; // the rectangle for source image
	SDL_Rect destination_rectangle_snake; // for destination

	int move_up;
	int move_down;
	int move_right;
	int move_left;
	int NoDeleteTail = 0;

	SDL_Texture *title_score_en;//score:라는 글씨띄우려고
	SDL_Rect title_score_en_rect;


	int lec;//speedup제어하는 변수
	SDL_Texture *title_speedup_en;//speedup띄울려고
	SDL_Rect title_speedup_en_rect;

	SDL_Texture *text_time_;//score변수를 띄우기 위해
	SDL_Rect text_time_rect_;

	SDL_Texture *text_poison_;//score변수를 띄우기 위해
	SDL_Rect text_poison_rect_;

	int score;
	TTF_Font *game_font1;
	Item item;
	Poison poison;

	bool poisonControl;
	bool newPoison;

};


