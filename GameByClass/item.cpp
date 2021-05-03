#include <iostream>
#include <cstdlib>
#include <ctime>

#include "item.h"
#include "GameFunc.h"
#include "SDL_image.h"

extern int m_w;
extern int m_h;
extern SDL_Renderer* g_renderer;
extern Node *head;
Item::Item() {
	srand((unsigned int)time(NULL));

	//사과이미지
	SDL_Surface* temp_surface = IMG_Load("../img/apple.png");
	texture_apple = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	SDL_QueryTexture(texture_apple, NULL, NULL, &source_rectangle_apple.w, &source_rectangle_apple.h);

	source_rectangle_apple.x = 0;
	source_rectangle_apple.y = 0;

	

}

Item::~Item(){
	SDL_DestroyTexture(texture_apple);

}

void Item::Renewal(){


	i = rand() % m_w;
	j = rand() % m_h;

	Node *temp = head;//같은 노드가 있는가?  snake의 몸에 아이템이 생기는 일이없도록함.

	while (temp != nullptr) {

		if (temp->i == i&&temp->j == j) {
			i = rand() % m_w;
			j = rand() % m_h;
			temp = head;
		}
		temp = temp->next;
	}
	std::cout << "아이템 만들었다";
}

void Item::Draw() {
	int x, y;
	GridToPixel(i, j, x, y);
	SDL_Rect r = { x,y,500 / m_w,500 / m_h };
	SDL_RenderCopy(g_renderer, texture_apple, &source_rectangle_apple, &r);

	
}