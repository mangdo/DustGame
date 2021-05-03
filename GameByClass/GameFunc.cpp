#include "ClassNode.h"
#include "GameFunc.h"

Node *head = nullptr;

extern int m_w;
extern int m_h;
extern int g_x;//game area�� x��ǥ
extern int g_y;//game area�� y��ǥ
extern int g_area;

//�Ӹ��� ���ο� ��带 �߰��ϴ� �Լ�
void AddNodeAtFront() {
	Node *n = new Node();
	n->next = head;
	head = n;

}

//���� ��带 �����ϴ� �Լ�
void DeleteTail() {
	if (head == nullptr)//�����Ͱ� ����.
		return;//����͵� ����.

	if (head->next == nullptr) {//�����Ͱ� 1��
		delete head;
		head = nullptr;
	}
	else { //�����Ͱ� ������
		Node *n = head;
		while (n->next->next != nullptr) {
			n = n->next;
		}
		delete n->next;
		n->next = nullptr;

	}
}


//�Ӹ� ��带 �����ϴ� �Լ�.
void DeleteHedad() {
	Node *n = head;
	head = n->next; //��尡 ���� ��带 ����Ű�� �Ѵ�.
	delete n; // ���� ��尡 ����ġ�� ���� ���ֱ�

}

// ������ ���ο� ��� �ϳ��� �߰��ϴ� �Լ�.
void AddNodeAtTail()
{
	Node *n = head;
	while (n->next != nullptr) {//n�� ������ ��尡 �ɶ����� �ݺ�.
		n = n->next;
	}

	n->next = new Node; //n�� �ڿ� ���ο� ��� ����.
	n->next->next = nullptr;//n�� ���� ���� ������ ���� next�� nullptr�־��ش�.
}


void GridToPixel(int i, int j, int&x, int&y) {
	
	x = g_x + g_area * (double)i / (double)m_w;
	y = g_y + g_area * (double)j / (double)m_h;

}