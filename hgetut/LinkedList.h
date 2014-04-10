#pragma once

#include "missile.h"
#include <cassert>

struct node{

	node(hgeResourceManager* resman,hgeVector Position = hgeVector(0,0),float dgree = 0)
		:data(resman,Position,dgree){}
	node(const Missile &p)
		:data(p){}

	Missile data;
	node* prev;
	node* next;

	Missile& GetMissile(){return data;}
	
};

class _iterator{
public:
	_iterator(){};
	_iterator(node* p)
		:data(p) {}
	~_iterator(){};

	bool hasNext(){
		if(data->next->next != data->next)
			return true;
		return false;
	}
	void GoNext(){
		if(hasNext()){
			data = data->next;
		}
	}

	void operator++(const int){ GoNext(); }
	node* operator*(){ return data; }
	node* operator->(){ return data; }

private:
	node* data;
};

class LinkedList
{
public:
	LinkedList(hgeResourceManager*);
	~LinkedList(void);
	void Init();
	void InsertLast(node& data);
	void DeleteNode(node* data);
	void DeleteList();

	int GetSize() {return size;}
	_iterator GetIter(){ return _iterator(Head->next); }

private:
	node* Head;
	node* tail;

	int size;

	hgeResourceManager* m_resman;
};

