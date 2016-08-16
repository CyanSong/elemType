// elemType.cpp : 定义控制台应用程序的入口点。
//本项目包括 stack，seqlist，linkedlist,queue的定义，及中缀表达式转后缀表达式
#include "stdafx.h"
#include <vector>
#include <exception>
#include<iostream>
#include<memory>
#include<map>
#include<string>
#include<exception>

template<class elemType>
class seqList
{
private:
	elemType* data;
	int maxSize;
	int currentLength;
	void doubleSize();
public:
	seqList(int num,const elemType& value);
	seqList(int size=10);
	~seqList() { delete[]data; }
	void clear();
	int length()const;
	void insert(size_t index,const elemType &value);
	elemType back()const;
	void push_back(const elemType& value);
	void pop_back();
	void remove(size_t num);
	elemType visit(size_t index)const;
	int search(const elemType& value)const;
	void traverse()const;
};

template<class elemtype,class container=seqList<elemtype>>
class stack {
private:
	container *content;
public:
	stack() :content(new container){};
	~stack() { delete content; }
	void push(const elemtype& a) {content->push_back(a); }
	elemtype pop() { 
			elemtype tmp(content->back());
			content->pop_back();
			return tmp;}
	elemtype top() { return content->back(); }
	bool isEmpty() { return !content->length(); }
};

template<class elemtype>
class queue {
private:
	elemtype *data;
	int curSize;
	int head, rear;
	void doubleSpace();
public:
	queue(int size=10) :curSize(size), data(new elemtype[size]), head(0), rear(0) {}
	~queue() { delete[]data; }
	void enQueue(const elemtype &a) {
		if ((rear + 1) % curSize == head)doubleSpace();
		if (++rear > curSize - 1)rear = 0;
		data[rear] = a;
	}
	elemtype deQueue() {
		if (isEmpty()) { std::cout << "Try to get data from an empty queue!";std::exception e;throw e; }
		if (++head > curSize - 1)head = 0;
		return data[head];
	}
	elemtype front() { return data[(head + 1) % curSize]; }
	bool isEmpty() { return rear == head; }
	int num() { return (rear - head+curSize) % curSize; }
};

template<class elemType>
class myList{
private:
	struct node {
		elemType data;
		node* next=NULL;
		node* prev=NULL;
		node(const elemType& x);
		node() =default;
	};
	node* head;
	node* tail;
public:
	myList() :head(new node),tail(new node){
		head->next = tail;
		tail->prev = head;
	}
	class iterator {
		friend class myList;
	private:
		node* obj;
	public:
		iterator(node* a):obj(a) {}
		iterator(const iterator& a) :obj(a.obj) {}
		iterator& operator++(){ obj = obj->next;return *this; }
		iterator operator++(int) { iterator tmp(*this);++(*this);return tmp;}
		iterator& operator--(){ obj = obj->prev;return *this; }
		iterator operator--(int) { iterator tmp(*this);--(*this);return tmp;}
		bool operator==(const iterator& a) const{ return a.obj == obj; }
		bool operator!=(const iterator& a) const { return !(a.obj == obj); }
		elemType operator*() { return obj->data; }

	};
	
	void clear();
	iterator begin() const { return iterator(head->next); }
	iterator end() const{ return iterator(tail); }
	int length()const;
	iterator insert(iterator& it, const elemType& value);
	iterator erase(iterator& it);
	bool empty()const;
	iterator search(const elemType& value)const;
	void traverse()const;
	~myList();
};

using std::cout;
using std::string;
string rpNotion(string notion);
bool isSymbol(char a);
bool isLower(char a, char b);

int main()
{
	//string notion{ "(a+b)*(c-d*e)^f-(g/h+i)" };
	//cout << rpNotion(notion);
	/*
	stack<char, seqList<char>>a;
	if (a.isEmpty()) {
		a.push('1');
		cout << a.pop();
		if (a.isEmpty())cout << "+++++";
	}
	else {
		cout << "====";
	}*/
	queue<int>a;
	a.enQueue(2);a.enQueue(3);
	cout<<a.num();
	cout << a.deQueue();
	cout << a.num();
	cout << a.deQueue();
	cout << a.isEmpty()<<std::endl;
	for (int i = 0;i < 11;++i) {
		a.enQueue(i);
		cout << a.front();
		cout << a.num();
	}
	system("pause");
	return 0;
}

template<class elemType>
void seqList<elemType>::doubleSize()
{
	elemType* tmp = new elemType[maxSize * 2];
	for (int i = 0;i < currentLength;++i)
	{
		tmp[i] = data[i];
	}
	delete data;
	data = tmp;
	maxSize *= 2;
}

template<class elemType>
seqList<elemType>::seqList(int num,const elemType& value)
{
	maxSize = num * 2;
	currentLength = num;
	data = new elemType[maxSize];
	for (int i = 0;i < currentLength;++i)
	{
		data[i] = value;
	}
}

template<class elemType>
seqList<elemType>::seqList(int size)
{
	maxSize = size;
	currentLength = 0;
	data = new elemType[maxSize];
}

template<class elemType>
void seqList<elemType>::clear()
{
	delete data;
	currentLength = 0;
}

template<class elemType>
int seqList<elemType>::length()const
{
	return currentLength;
}

template<class elemType>
void seqList<elemType>::push_back(const elemType& value)
{
	if (currentLength == maxSize)doubleSize();
	data[currentLength] = value;
	currentLength++;
}

template<class elemType>
void seqList<elemType>::pop_back()
{
	remove(currentLength - 1);
}

template<class elemType>
void seqList<elemType>::remove(size_t num)
{
	for (int i = num;i < currentLength-1;++i)
	{
		data[i] = data[i + 1];
	}
	currentLength--;
}

template<class elemType>
elemType seqList<elemType>::visit(size_t index) const
{
	return data[index];
}

template<class elemType>
int seqList<elemType>::search(const elemType& value) const
{
	int index = -1;
	for (int i=0;i<currentLength;++i)
	{
		if (data[i] == value)
		{
			index = i;
			break;
		}
	}
	return index;
}

template<class elemType>
void seqList<elemType>::traverse() const
{
	for (int i = 0;i < currentLength;++i)
	{
		std::cout << data[i] << " ";
	}
}

template<class elemType>
void seqList<elemType>::insert(size_t index, const elemType& value)
{
	if (currentLength == maxSize) 
	{
		doubleSize();
	}
	for (size_t i = currentLength;i > index;i--)
	{
		data[i] = data[i-1];
	}
	data[index] = value;
	currentLength++;
}

template<class elemType>
elemType seqList<elemType>::back() const
{
	return data[currentLength - 1]; 
}


template<class elemType>
void myList<elemType>::clear()
{
	while (!empty())
	{
		erase(begin());
	}
}

template<class elemType>
int myList<elemType>::length() const
{
	int len = 0;
	iterator tmp(begin());
	while (tmp!=end())
	{
		len++;
		tmp++;
	}
	return len;
}

template<class elemType>
typename myList<elemType>::iterator myList<elemType>::insert(iterator& it, const elemType & value)
{
	node *tmp = new node(value);
	iterator tmpIt(it);
	tmpIt--;
	(tmpIt.obj)->next = tmp;tmp->prev = tmpIt.obj;
	(it.obj)->prev = tmp;tmp->next = (it.obj);
	return --it;
}

template<class elemType>
typename myList<elemType>::iterator myList<elemType>::erase(iterator& it)
{
	node* tmpNode;
	tmpNode = it.obj;
	++it;
	tmpNode->prev->next = tmpNode->next;
	tmpNode->next->prev = tmpNode->prev;
	delete tmpNode;
	return it;
}

template<class elemType>
bool myList<elemType>::empty()const
{
	return head->next==tail;
}

template<class elemType>
typename myList<elemType>::iterator myList<elemType>::search(const elemType & value) const
{
	iterator tmp(begin());
	for (;tmp != end();++tmp)
	{
		if (*tmp == value)return tmp;
	}
	return tmp;
}



template<class elemType>
void myList<elemType>::traverse()const
{
	for (iterator tmp = begin();tmp != end();++tmp)
	{
		std::cout << *tmp << " ";
	}
}

template<class elemType>
myList<elemType>::~myList()
{
	clear();
	delete tail;
	delete head;
}

template<class elemType>
myList<elemType>::node::node(const elemType & x):data(x){
}

string rpNotion(string notion )
{
	string result;
	stack<char, seqList<char>> myStack;
	for (auto tmp:notion) {
		bool flag ;
		switch (tmp) {
			//左括号一律压入栈
		case '(':myStack.push(tmp);break;
			//右括号则不断出栈，直到遇见左括号，如左括号不存在返回error
		case ')':
			do {
				try {
					flag = true;
					if (myStack.isEmpty()) {
						std::exception e{ "Right bracket without left bracket!" };
						throw e;
					}
					if (myStack.top() == '(') { flag = false;myStack.pop(); }
					else result += myStack.pop();
				}catch (std::exception e) { cout << e.what(); }
			} while (flag);
			break;
		default:
			if(isSymbol(tmp)){
				while (!myStack.isEmpty()&&myStack.top()!='('&&isLower(myStack.top(), tmp) ){
					result += myStack.pop();
				}
				myStack.push(tmp);
			}else  result += tmp; 
		}
	}
	while (!myStack.isEmpty())
	{
		try {
			if (myStack.top() != '(')result += myStack.pop();
			else { std::exception e{ "Left bracket without right bracket!" }; }
		}
		catch (std::exception e) { cout << e.what(); }
	}
	return result;
}

inline bool isSymbol(char a)
{
	return a=='+'||a=='-'||a=='%'||a=='*'||a=='/'||a=='^';
}

bool isLower(char oldWord, char newWord)
{
	typename std::map<char, size_t>sort{ { '+',1 }, {'-',1} ,{'*',2},{'%',2},{'/',2}, \
	{'^',3} };
	return sort[oldWord] > sort[newWord];
}

template<class elemtype>
void queue<elemtype>::doubleSpace()
{
	elemtype *tmpData = new elemtype[2 * curSize];
	for (int i = 1;i < curSize ;++i)
	{
		tmpData[i] = data[(head+i) % curSize];
	}
	rear = curSize;
	curSize *= 2;
	head = 0;
	delete data;
	data = tmpData;
}
