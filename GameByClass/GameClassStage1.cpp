#include "GameClassStage1.h"
#include "GameClassPhase.h"

#include "SDL_image.h"
#include "GameFunc.h"
#include <iostream>
#include "SDL_ttf.h"
#include <string>



extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern Node *head;
extern int g_frame_time_ms;

int m_w;//Game area의 가로칸 갯수
int m_h;//Game area의 세로칸 갯수
int g_x = 200;//game area의 x좌표
int g_y = 50;//game area의 y좌표
int g_area = 500;//game area 가로,세로길이


Stage1::Stage1()
{
		// 배경이미지 작업
	{
		SDL_Surface* temp_surface = IMG_Load("../img/1.png");
		texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);

		SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
		destination_rectangle_.x = source_rectangle_.x = 0;
		destination_rectangle_.y = source_rectangle_.y = 0;
		destination_rectangle_.w = source_rectangle_.w;
		destination_rectangle_.h = source_rectangle_.h;
	}

	//snake이미지
	{
		SDL_Surface* temp_surface = IMG_Load("../img/snake.png");
		texture_snake = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		SDL_QueryTexture(texture_snake, NULL, NULL, &source_rectangle_snake.w, &source_rectangle_snake.h);


		source_rectangle_snake.x = 0;
		source_rectangle_snake.y = 0;

	}
	//snakeHead이미지
	{
		SDL_Surface* temp_surface = IMG_Load("../img/snakeHead.png");
		texture_snakeHead = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		SDL_QueryTexture(texture_snakeHead, NULL, NULL, &source_rectangle_snakeHead.w, &source_rectangle_snakeHead.h);


		source_rectangle_snakeHead.x = 0;
		source_rectangle_snakeHead.y = 0;

	}

		m_w = 20;
		m_h = 20;

		move_up = 0;
		move_down = 0;
		move_right = 0;
		move_left = 0;

		
		item.Renewal();//아이템을 아무곳에나 뜨게끔
		poison.Renewal();

		{//"Time : "이라는 글자위한 작업
			game_font1 = TTF_OpenFont("../img/malgun.ttf", 30);

			SDL_Color white = { 0, 0, 0, 255 };
			SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, "Score: ", white);

			title_score_en_rect.x = 0;
			title_score_en_rect.y = 0;
			title_score_en_rect.w = tmp_surface->w;
			title_score_en_rect.h = tmp_surface->h;

			title_score_en = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

			SDL_FreeSurface(tmp_surface);
		}
		{//"speed up "이라는 글자위한 작업
			game_font1 = TTF_OpenFont("../img/malgun.ttf", 30);

			SDL_Color white = { 0, 0, 0, 255 };
			SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, "Speed up! ", white);

			title_speedup_en_rect.x = 0;
			title_speedup_en_rect.y = 0;
			title_speedup_en_rect.w = tmp_surface->w;
			title_speedup_en_rect.h = tmp_surface->h;

			title_speedup_en = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

			SDL_FreeSurface(tmp_surface);
		}

		{//"poisoning "이라는 글자위한 작업
			game_font1 = TTF_OpenFont("../img/malgun.ttf", 30);

			SDL_Color red= { 255, 0, 0, 255 };
			SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, "Poisoning! ", red);

			text_poison_rect_.x = 0;
			text_poison_rect_.y = 0;
			text_poison_rect_.w = tmp_surface->w;
			text_poison_rect_.h = tmp_surface->h;

			text_poison_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

			SDL_FreeSurface(tmp_surface);
		}


}

Stage1::~Stage1()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(texture_snake);
	SDL_DestroyTexture(texture_snakeHead);

}

void Stage1::Renewal() {//다시 시작할때마다 초기상태로 리뉴얼해줌.
	NoDeleteTail = 0;
	score = 0;
	lec = 0;


	Node *temp = head;
	while (temp != nullptr) {//그전에 존재하던 노드는 다삭제

		DeleteHedad();
		temp = head;

	}

		AddNodeAtFront();//캐릭터의 초기길이는 1이다.

		head->i = m_w / 2;
		head->j = m_h / 2;


	move_up = 0;
	move_down = 0;
	move_right = 0;
	move_left = 0;

	item.Renewal();
	poison.Renewal();
	poisonControl = false;
	newPoison = false;
	
}

void Stage1::Update() {
	if (move_left == 1) {
		Node *temp = head;
		AddNodeAtFront();
		head->i = temp->i - 1;
		head->j = temp->j;
		if (NoDeleteTail != 0)
			NoDeleteTail--;

		else {
			DeleteTail();
		}
	}
	if (move_right == 1) {
		Node *temp = head;
		AddNodeAtFront();
		head->i = temp->i + 1;
		head->j = temp->j;
		if (NoDeleteTail != 0)
			NoDeleteTail--;

		else {
			DeleteTail();
		}
	}
	if (move_up == 1) {
		Node *temp = head;
		AddNodeAtFront();
		head->i = temp->i;
		head->j = temp->j - 1;
		if (NoDeleteTail != 0)
			NoDeleteTail--;

		else {
			DeleteTail();
		}

	}
	if (move_down == 1) {
		Node *temp = head;
		AddNodeAtFront();
		head->i = temp->i;
		head->j = temp->j + 1;
		if (NoDeleteTail != 0)
			NoDeleteTail--;

		else {
			DeleteTail();
		}
	}

	Node *temp = head->next;//머리랑 몸이랑 부딪혔는가?
	while (temp != nullptr) {
		if ((head->i == temp->i) && (head->j == temp->j))
			g_current_game_phase = PHASE_ENDING;
		temp = temp->next;
	}

	//게임 area를 벗어났는가?
	temp = head;
	while (temp != nullptr) {
		if ((temp->i < 0) || (temp->i >= m_w) || (temp->j < 0) || (temp->j >= m_h))
			g_current_game_phase = PHASE_ENDING;
		temp = temp->next;
	}

	if ((head->i == item.i) && (head->j == item.j)) {//아이템을 먹으면,
		poisonControl = false;
		NoDeleteTail += 3;
		score += 10;
		item.Renewal();//아이템 위치 다시 설정
		while (item.i == poison.i&&item.j == poison.j) {
			item.Renewal();//아이템과 독의 위치가 겹치지않게 위치 설정
			std::cout << "아이템 만들다가 겹쳣다!!!!";
			
		}

	}
	if ((head->i == poison.i) && (head->j == poison.j)) {//독을 먹으면,
		
		score -= 10;//10점 깎고
		if (score < 50) {
			lec = 0;
			g_frame_time_ms = 120;
		}
		if (head->next == nullptr) {//남은 노드가 1개였었다면
			g_current_game_phase = PHASE_ENDING; // 그 노드가 죽음..! 게임 끝
		}
		else {
			newPoison = true;
			poisonControl = true;
			DeleteTail();//꼬리노드 삭제
			poison.Renewal();
			while (item.i == poison.i&&item.j == poison.j) {
				poison.Renewal();//아이템과 독의 위치가 겹치지않게 위치설정
				std::cout << "독만들다가 겹쳣다!!!!";
			}
		}
	}
	if (poisonControl == true) {
		Uint32 cur_time = SDL_GetTicks();
		static Uint32 poison_time = SDL_GetTicks();
		if (newPoison) {//intro에서 클릭했을때 타이머 제어변수가 true가 한번되는데
			poison_time = cur_time;//이때 last_time을 조정해줌.
			newPoison = false;
		}
			int time_ms = cur_time - poison_time;
			if (time_ms > 1000) {
				if (head->next == nullptr) {//남은 노드가 1개였었다면,
					g_current_game_phase = PHASE_ENDING; // 그 노드가 죽음..! 게임 끝
				}
				else {
					DeleteTail();
					poison_time = cur_time;
				}
			}
	}
	{//score변수 업데이트
		SDL_Color white = { 0, 0, 0, 255 };
		SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, std::to_string((long long)score).c_str(), white);

		text_time_rect_.x = 0;
		text_time_rect_.y = 0;
		text_time_rect_.w = tmp_surface->w;
		text_time_rect_.h = tmp_surface->h;

		text_time_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

		SDL_FreeSurface(tmp_surface);
	}
	
	if (score > 50) {
		g_frame_time_ms = 90;
		lec = 1;
	}
}


void Stage1::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0,255,255,0);
	SDL_RenderClear(g_renderer); //렌더 정리

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); //staage1배경


	Node *n = head;
	{//머리만 다른색으로
		int x, y;
		GridToPixel(n->i, n->j, x, y);
		SDL_Rect r = { x,y,500 / m_w,500 / m_h };
		SDL_RenderCopy(g_renderer, texture_snakeHead, &source_rectangle_snakeHead, &r);
		n = n->next;

	}
	while (n != nullptr) {
		int x, y;
		GridToPixel(n->i, n->j, x, y);
		SDL_Rect r = { x,y,500 / m_w,500 / m_h };
		SDL_RenderCopy(g_renderer, texture_snake, &source_rectangle_snake, &r);

		n = n->next;
	}

	item.Draw();
	poison.Draw();

	{ //"점수:"라는 글씨
		SDL_Rect r;
		r.x = 10;
		r.y = 30;
		r.w = title_score_en_rect.w;
		r.h = title_score_en_rect.h;
		SDL_RenderCopy(g_renderer, title_score_en, 0, &r);
	}

	if(lec==1){ //"speedup"이라는 글씨
		SDL_Rect r;
		r.x = 700;
		r.y = 30;
		r.w = title_speedup_en_rect.w;
		r.h = title_speedup_en_rect.h;
		SDL_RenderCopy(g_renderer, title_speedup_en, 0, &r);
	}

	{ // score변수 띄우고
		SDL_Rect r;
		r.x = 150;
		r.y = 30;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}
	if (poisonControl) { //"speedup"이라는 글씨
		SDL_Rect r;
		r.x = 700;
		r.y = 300;
		r.w = text_poison_rect_.w;
		r.h = text_poison_rect_.h;
		SDL_RenderCopy(g_renderer, text_poison_, 0, &r);
	}

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Stage1::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				move_left = 1;
				move_right = 0;
				move_down = 0;
				move_up = 0;
			}

			else if (event.key.keysym.sym == SDLK_RIGHT) {
				move_right = 1;
				move_left = 0;
				move_down = 0;
				move_up = 0;
			}

			else if (event.key.keysym.sym == SDLK_DOWN) {
				move_down = 1;
				move_right = 0;
				move_left = 0;
				move_up = 0;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				move_up = 1;
				move_right = 0;
				move_left = 0;
				move_down = 0;
			}

			
			break;
			/*
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)

			else if (event.key.keysym.sym == SDLK_RIGHT)
				move_right = 0;

			else if (event.key.keysym.sym == SDLK_DOWN) {
				move_down = 0;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				move_up = 0;
			}
			break;
			*/
		default:
			break;
		}
	}
}
