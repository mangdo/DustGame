
#include "GameClassEnding.h"
#include "GameClassPhase.h"
#include "SDL_image.h"
#include <iostream>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;

Ending::Ending()
{
	//엔딩화면(gameover) 띄우기위한 이미지 작업.
	SDL_Surface* temp_surface = IMG_Load("../img/end.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h); 
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	
	destination_rectangle_.w = source_rectangle_.w = 900;
	destination_rectangle_.h = source_rectangle_.h = 600;

}

Ending::~Ending()
{
	SDL_DestroyTexture(texture_);
}

void Ending::Update()
{
}


void Ending::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255,255,0,255);
	SDL_RenderClear(g_renderer);//렌더정리

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Ending::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
		
			// If the mouse left button is pressed. 
			if ( event.button.button == SDL_BUTTON_LEFT ) //마우스 왼쪽 클릭하면 다시 처음페이지로 넘어감
			{
				g_current_game_phase = PHASE_INTRO;
			}
			break;

		default:
			break;
		}
	}
}
