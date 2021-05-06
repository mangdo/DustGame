# DustGame
> SDL을 사용한 먼지 키우기 게임입니다.   
> 3학년 1학기, '게임 프로그래밍' 수업에서 진행한 개인 프로젝트입니다.

<br>

## 1. 제작 기간 & 참여 인원
- 2019년 5월 17일 ~ 2019년 5월 29일
- 개인 프로젝트

<br>

## 2. 사용 기술
  - C++
  - SDL 2

<br>

## 3. 게임 방법
<img width="550" alt="howtogame" src="https://user-images.githubusercontent.com/70243735/116843350-a6a6ab80-ac1a-11eb-8a4a-da0853f91958.png">

<br>

## 4. 게임 플레이 영상
<img src ="https://user-images.githubusercontent.com/70243735/116843665-95aa6a00-ac1b-11eb-9e9d-3aa69fa03888.gif" width ="800px">

[![https://youtu.be/s-zzxMNEUgE](https://user-images.githubusercontent.com/70243735/117240571-152e7800-ae6c-11eb-8a08-178b1bde8d16.png)](https://youtu.be/s-zzxMNEUgE)

<br>

## 5. 핵심 트러블 슈팅
### 5.1. 먼지의 위치  :bug:
 문제 상황   
* 앞으로 이동할 때마다, 아이템을 먹게 될 때마다 위치나 길이가 바뀌어야 했습니다.
* 때문에 **삽입과 삭제가 빈번**하게 일어났습니다.

해결   
* 계속해서 변하는 먼지의 위치와 길이를 나타내기 위하여 **Linked list**를 이용하였습니다.
<img src = "https://user-images.githubusercontent.com/70243735/116843284-73fcb300-ac1a-11eb-8f23-80ea5941a87d.png" width = "800px">
<details>
<summary>코드 확인 :pushpin: </summary>

[GameFunc.cpp](./GameByClass/GameFunc.cpp)

```c++
// 머리에 새로운 노드를 추가하는 함수
void AddNodeAtFront() {
	Node *n = new Node();
	n->next = head;
	head = n;

}

// 꼬리 노드를 제거하는 함수
void DeleteTail() {
	if (head == nullptr) // 데이터가 없음.
		return; //지울것도 없음.

	if (head->next == nullptr) {// 데이터가 1개
		delete head;
		head = nullptr;
	}
	else { // 데이터가 여러개
		Node *n = head;
		while (n->next->next != nullptr) {
			n = n->next;
		}
		delete n->next;
		n->next = nullptr;
	}
}
```

[GameClassStage1](./GameByClass/GameClassStage1.cpp)

```c++
void Stage1::Update() {
  if (move_left == 1) {
    Node *temp = head;
    AddNodeAtFront();
    head->i = temp->i - 1;
    head->j = temp->j;

    //(생략..)

    DeleteTail();
  }
  //(생략..)
}
```

</details>

### 5.2. 랜덤으로 생성되는 아이템 :apple: :green_apple:
 문제 상황   
* 아이템은 사용자가 패턴을 알 수 없도록 **랜덤의 위치**에서 생겨나야 합니다.
* 하지만, 각 아이템끼리의 **위치가 겹쳐서** 생기거나
* 이미 먼지가 있는 위치에도 아이템이 생기는 현상이 있었습니다.

해결
* **Item클래스에** 아이템을 **랜덤 위치에서 생성하는 Renewal()** 이라는 함수를 만들었습니다.
* Renewal()에서는 먼지의 위치를 체크해서 겹치면 아이템을 다시 생성합니다.
<details>
<summary>코드 확인 :pushpin: </summary>
  
[GameClassStage1.cpp](./GameByClass/GameClassStage1.cpp)
  
```c++
// 아이템을 먹었을 경우
if ((head->i == item.i) && (head->j == item.j)) { 
		poisonControl = false;
		NoDeleteTail += 3;
		score += 10;
		item.Renewal();//아이템 위치 다시 설정
		while (item.i == poison.i&&item.j == poison.j) {
			item.Renewal();//아이템과 독의 위치가 겹치지않게 위치 설정			
		}
	}
```

[item.cpp](./GameByClass/item.cpp)

```c++
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
}
```
</details>
