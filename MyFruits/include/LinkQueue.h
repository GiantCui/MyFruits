#pragma once
#include"basic.h"

template <typename T> struct DataNode	//链队数据结点类型
{
	T date;					//存放元素
	DataNode<T> *next;		//下一个节点指针
};

template <typename T> struct LinkQuNode		//链队结点类型
{
	DataNode<T> *front;		//指向队首结点
	DataNode<T> *rear;		//指向队尾结点
};

template <typename T> void InitQueue(LinkQuNode<T> *&q)		//初始化队列
{
	q = new LinkQuNode<T>;
	q->front = q->rear = NULL;
}

template <typename T> void DestroyQueue(LinkQuNode<T> *&q)		//销毁队列
{
	DataNode<T> *pre = q->front, *p;
	if (pre != NULL)
	{
		p = pre->next;
		while (p != NULL)
		{
			delete pre;
			pre = p; 
			p = p->next;
		}
		delete pre;
	}
	delete q;
}

template <typename T> bool QueueEmpty(LinkQuNode<T> *q)
{
	return (q->rear == NULL);
}

template <typename T> void enQueue(LinkQuNode<T> *&q, T e)
{
	DataNode<T> *p;
	p = new DataNode<T>;
	p->date = e;
	p->next = NULL;
	if (q->rear == NULL)		//若栈为空，新结点既是队首结点又是队尾结点
		q->front = q->rear = p;
	else						//栈不为空
	{
		q->rear->next = p;		//将结点p连接到队尾，并将rear指向它
		q->rear = p;
	}
}

template <typename T> bool deQueue(LinkQuNode<T> *&q, T &e)
{
	DataNode<T> *t;
	if (q->rear == NULL)		//原队列为空
		return false;
	t = q->front;
	if (q->front == q->rear)		//原队列中只有一个数据结点
		q->front = q->rear = NULL;
	else
		q->front = q->front->next;		//原队列中有两个或以上数据结点
	e = t->date;
	delete t;
	return true;
}