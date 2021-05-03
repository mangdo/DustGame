#include "poison.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ClassNode.h"
#include "GameFunc.h"


extern int m_w;
extern int m_h;
extern SDL_Renderer* g_renderer;
extern Node *head;

Poison::Poison() {
	srand((unsigned int)time(NULL));

	//������̹���
	SDL_Surface* temp_surface = IMG_Load("../img/poison.png");
	texture_poison = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	SDL_QueryTexture(texture_poison, NULL, NULL, &source_rectangle_poison.w, &source_rectangle_poison.h);

	source_rectangle_poison.x = 0;
	source_rectangle_poison.y = 0;

}

Poison::~Poison() {
	SDL_DestroyTexture(texture_poison);

}

void Poison::Renewal() {
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
	std::cout << "�� �������";

}

void Poison::Draw() {
	int x, y;
	GridToPixel(i, j, x, y);
	SDL_Rect r = { x,y,500 / m_w,500 / m_h };
	SDL_RenderCopy(g_renderer, texture_poison, &source_rectangle_poison, &r);

}