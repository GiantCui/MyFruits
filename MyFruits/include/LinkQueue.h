#pragma once
#include"basic.h"

template <typename T> struct DataNode	//�������ݽ������
{
	T date;					//���Ԫ��
	DataNode<T> *next;		//��һ���ڵ�ָ��
};

template <typename T> struct LinkQuNode		//���ӽ������
{
	DataNode<T> *front;		//ָ����׽��
	DataNode<T> *rear;		//ָ���β���
};

template <typename T> void InitQueue(LinkQuNode<T> *&q)		//��ʼ������
{
	q = new LinkQuNode<T>;
	q->front = q->rear = NULL;
}

template <typename T> void DestroyQueue(LinkQuNode<T> *&q)		//���ٶ���
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
	if (q->rear == NULL)		//��ջΪ�գ��½����Ƕ��׽�����Ƕ�β���
		q->front = q->rear = p;
	else						//ջ��Ϊ��
	{
		q->rear->next = p;		//�����p���ӵ���β������rearָ����
		q->rear = p;
	}
}

template <typename T> bool deQueue(LinkQuNode<T> *&q, T &e)
{
	DataNode<T> *t;
	if (q->rear == NULL)		//ԭ����Ϊ��
		return false;
	t = q->front;
	if (q->front == q->rear)		//ԭ������ֻ��һ�����ݽ��
		q->front = q->rear = NULL;
	else
		q->front = q->front->next;		//ԭ���������������������ݽ��
	e = t->date;
	delete t;
	return true;
}