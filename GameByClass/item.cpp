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

	//����̹���
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

	Node *temp = head;//���� ��尡 �ִ°�?  snake�� ���� �������� ����� ���̾�������.

	while (temp != nullptr) {

		if (temp->i == i&&temp->j == j) {
			i = rand() % m_w;
			j = rand() % m_h;
			temp = head;
		}
		temp = temp->next;
	}
	std::cout << "������ �������";
}

void Item::Draw() {
	int x, y;
	GridToPixel(i, j, x, y);
	SDL_Rect r = { x,y,500 / m_w,500 / m_h };
	SDL_RenderCopy(g_renderer, texture_apple, &source_rectangle_apple, &r);

	
}