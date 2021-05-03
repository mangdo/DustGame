#include "ClassNode.h"
#include "GameFunc.h"

Node *head = nullptr;

extern int m_w;
extern int m_h;
extern int g_x;//game area의 x좌표
extern int g_y;//game area의 y좌표
extern int g_area;

//머리에 새로운 노드를 추가하는 함수
void AddNodeAtFront() {
	Node *n = new Node();
	n->next = head;
	head = n;

}

//꼬리 노드를 제거하는 함수
void DeleteTail() {
	if (head == nullptr)//데이터가 없음.
		return;//지울것도 없음.

	if (head->next == nullptr) {//데이터가 1개
		delete head;
		head = nullptr;
	}
	else { //데이터가 여러개
		Node *n = head;
		while (n->next->next != nullptr) {
			n = n->next;
		}
		delete n->next;
		n->next = nullptr;

	}
}


//머리 노드를 제거하는 함수.
void DeleteHedad() {
	Node *n = head;
	head = n->next; //헤드가 다음 노드를 가르키게 한다.
	delete n; // 원래 헤드가 가르치던 노드는 없애기

}

// 꼬리에 새로운 노드 하나를 추가하는 함수.
void AddNodeAtTail()
{
	Node *n = head;
	while (n->next != nullptr) {//n이 마지막 노드가 될때까지 반복.
		n = n->next;
	}

	n->next = new Node; //n의 뒤에 새로운 노드 생성.
	n->next->next = nullptr;//n의 다음 노드는 마지막 노드라서 next에 nullptr넣어준다.
}


void GridToPixel(int i, int j, int&x, int&y) {
	
	x = g_x + g_area * (double)i / (double)m_w;
	y = g_y + g_area * (double)j / (double)m_h;

}