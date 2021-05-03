
#include "SDL.h"
#include <iostream>

#include "GameClassPhase.h"
#include "GameClassIntro.h"
#include "GameClassHowToPlay.h"
#include "GameClassStage1.h"
#include "GameClassStage2.h"
#include "GameClassEnding.h"
#include "SDL_ttf.h"

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;

bool g_flag_running;
Uint32 g_last_time_ms;
int g_frame_time_ms = 120;

bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen);
void CleanWindow();


// Game Phases
int g_current_game_phase;
int renewal;

int main(int argc, char* argv[])
{
	InitializeWindow("Game By Class", 10, 50, 900, 600, false);





	g_current_game_phase = PHASE_INTRO;
	renewal=0;

	TTF_Init();

	Intro intro;
	HowToPlay howToPlay;
	Stage1 stage1;
	Ending ending;

	while ( g_flag_running )
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if ( cur_time_ms-g_last_time_ms < g_frame_time_ms )
			continue;

		if ( g_current_game_phase ==  PHASE_INTRO )
		{
			intro.HandleEvents();
			intro.Update();
			intro.Render();
		}
		else if (g_current_game_phase == PHASE_HOWTOPLAY)
		{
			howToPlay.HandleEvents();
			howToPlay.Update();
			howToPlay.Render();
		}
		else if ( g_current_game_phase == PHASE_STAGE1 )
		{
			if (renewal == 1) {
				stage1.Renewal();
				renewal = 0;
			}
			stage1.HandleEvents();
			stage1.Update();
			stage1.Render();
		}
		else if ( g_current_game_phase == PHASE_ENDING )
		{
			ending.HandleEvents();
			ending.Update();
			ending.Render();
		}

		g_last_time_ms = cur_time_ms;
	}

	CleanWindow();
	TTF_Quit();


	return 0;
}



////////////////////////////////////
// Functions for the Window
bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen)
{
	int flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		g_window = SDL_CreateWindow(title, xpos, ypos, 
			width, height, flags);

		if(g_window != 0) // window init success
		{
			std::cout << "window creation success\n";
			g_renderer = SDL_CreateRenderer(g_window, -1, 0);
			if(g_renderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(g_renderer, 
					255,255,255,255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	g_flag_running = true; // everything inited successfully, start the main loop

	return true;

}



void CleanWindow()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	SDL_Quit();
}