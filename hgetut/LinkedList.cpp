#include "LinkedList.h"

LinkedList::LinkedList(hgeResourceManager* resman)
: m_resman(resman)
{
	Init();
}


LinkedList::~LinkedList(void)
{
	DeleteList();
}

void LinkedList::Init(){
	Head = new node(m_resman);
	tail = new node(m_resman);

	Head->prev = Head;
	Head->next = tail;
	tail->next = tail;
	tail->prev = Head;

	size = 0;
}

void LinkedList::InsertLast(node& data){
	node* s=Head;
	while(s->next!=tail) s = s->next;

	s= new node(data);
	//s= data;

	tail->prev->next = s;
	s->prev = tail->prev;
	tail->prev = s;
	s->next =tail;

	size++;
	//printf("insert %d\n",size);
}

void LinkedList::DeleteNode(node* pNode){
	pNode->next->prev = pNode->prev;
	pNode->prev->next = pNode->next;
	SAFE_DELETE(pNode);
	pNode = NULL;
	
	size--;
}

void LinkedList::DeleteList(){
	node* pNode = Head->next;
	while(pNode != tail){
		pNode = pNode->next;
		DeleteNode(pNode->prev);
	}
// 	SAFE_DELETE(Head);
// 	SAFE_DELETE(tail);
}
