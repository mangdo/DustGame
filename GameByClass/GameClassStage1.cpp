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

int m_w;//Game area�� ����ĭ ����
int m_h;//Game area�� ����ĭ ����
int g_x = 200;//game area�� x��ǥ
int g_y = 50;//game area�� y��ǥ
int g_area = 500;//game area ����,���α���


Stage1::Stage1()
{
		// ����̹��� �۾�
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

	//snake�̹���
	{
		SDL_Surface* temp_surface = IMG_Load("../img/snake.png");
		texture_snake = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		SDL_QueryTexture(texture_snake, NULL, NULL, &source_rectangle_snake.w, &source_rectangle_snake.h);


		source_rectangle_snake.x = 0;
		source_rectangle_snake.y = 0;

	}
	//snakeHead�̹���
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

		
		item.Renewal();//�������� �ƹ������� �߰Բ�
		poison.Renewal();

		{//"Time : "�̶�� �������� �۾�
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
		{//"speed up "�̶�� �������� �۾�
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

		{//"poisoning "�̶�� �������� �۾�
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

void Stage1::Renewal() {//�ٽ� �����Ҷ����� �ʱ���·� ����������.
	NoDeleteTail = 0;
	score = 0;
	lec = 0;


	Node *temp = head;
	while (temp != nullptr) {//������ �����ϴ� ���� �ٻ���

		DeleteHedad();
		temp = head;

	}

		AddNodeAtFront();//ĳ������ �ʱ���̴� 1�̴�.

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

	Node *temp = head->next;//�Ӹ��� ���̶� �ε����°�?
	while (temp != nullptr) {
		if ((head->i == temp->i) && (head->j == temp->j))
			g_current_game_phase = PHASE_ENDING;
		temp = temp->next;
	}

	//���� area�� ����°�?
	temp = head;
	while (temp != nullptr) {
		if ((temp->i < 0) || (temp->i >= m_w) || (temp->j < 0) || (temp->j >= m_h))
			g_current_game_phase = PHASE_ENDING;
		temp = temp->next;
	}

	if ((head->i == item.i) && (head->j == item.j)) {//�������� ������,
		poisonControl = false;
		NoDeleteTail += 3;
		score += 10;
		item.Renewal();//������ ��ġ �ٽ� ����
		while (item.i == poison.i&&item.j == poison.j) {
			item.Renewal();//�����۰� ���� ��ġ�� ��ġ���ʰ� ��ġ ����
			std::cout << "������ ����ٰ� �㫉��!!!!";
			
		}

	}
	if ((head->i == poison.i) && (head->j == poison.j)) {//���� ������,
		
		score -= 10;//10�� ���
		if (score < 50) {
			lec = 0;
			g_frame_time_ms = 120;
		}
		if (head->next == nullptr) {//���� ��尡 1�������ٸ�
			g_current_game_phase = PHASE_ENDING; // �� ��尡 ����..! ���� ��
		}
		else {
			newPoison = true;
			poisonControl = true;
			DeleteTail();//������� ����
			poison.Renewal();
			while (item.i == poison.i&&item.j == poison.j) {
				poison.Renewal();//�����۰� ���� ��ġ�� ��ġ���ʰ� ��ġ����
				std::cout << "������ٰ� �㫉��!!!!";
			}
		}
	}
	if (poisonControl == true) {
		Uint32 cur_time = SDL_GetTicks();
		static Uint32 poison_time = SDL_GetTicks();
		if (newPoison) {//intro���� Ŭ�������� Ÿ�̸� ������� true�� �ѹ��Ǵµ�
			poison_time = cur_time;//�̶� last_time�� ��������.
			newPoison = false;
		}
			int time_ms = cur_time - poison_time;
			if (time_ms > 1000) {
				if (head->next == nullptr) {//���� ��尡 1�������ٸ�,
					g_current_game_phase = PHASE_ENDING; // �� ��尡 ����..! ���� ��
				}
				else {
					DeleteTail();
					poison_time = cur_time;
				}
			}
	}
	{//score���� ������Ʈ
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
	SDL_RenderClear(g_renderer); //���� ����

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); //staage1���


	Node *n = head;
	{//�Ӹ��� �ٸ�������
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

	{ //"����:"��� �۾�
		SDL_Rect r;
		r.x = 10;
		r.y = 30;
		r.w = title_score_en_rect.w;
		r.h = title_score_en_rect.h;
		SDL_RenderCopy(g_renderer, title_score_en, 0, &r);
	}

	if(lec==1){ //"speedup"�̶�� �۾�
		SDL_Rect r;
		r.x = 700;
		r.y = 30;
		r.w = title_speedup_en_rect.w;
		r.h = title_speedup_en_rect.h;
		SDL_RenderCopy(g_renderer, title_speedup_en, 0, &r);
	}

	{ // score���� ����
		SDL_Rect r;
		r.x = 150;
		r.y = 30;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}
	if (poisonControl) { //"speedup"�̶�� �۾�
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
