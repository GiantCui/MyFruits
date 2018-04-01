#pragma once
#include"basic.h"

template <typename T> struct DDataNode		//˫���������ݽ������
{
	T data;
	DDataNode<T> *next;
	DDataNode<T> *prear;
};

template <typename T> struct DLinkQueue		//˫�����ӽڵ�����
{
	DDataNode<T> *front;
	DDataNode<T> *rear;	
};

template <typename T> void InitDLinkQueue(DLinkQueue<T> *&dq)		//��ʼ������
{
	dq = new DLinkQueue<T>;
	dq->front = dq->rear = NULL;
}

template <typename T> void DestroyDLinkQueue(DLinkQueue<T> *&dq)		//���ٶ���
{
	DDataNode<T> *dpre = dq->front, *p;
	while (dpre != NULL)
	{
		p = dpre->next;
		while (p != NULL)
		{
			delete dpre;
			dpre = p;
			p = p->next;
		}
		delete p;
	}
	delete dq;
}

template <typename T> bool DLinkQueueEmpty(DLinkQueue<T> *dq)		//�ж϶����Ƿ�Ϊ��
{
	return (dq->rear == NULL);
}

template <typename T> void enFDLinkQueue(DLinkQueue<T> *&dq, T e)		//ͷ���
{
	DDataNode<T> *p;
	p = new DDataNode<T>;
	p->data = e;
	p->next = p->prear = NULL;
	if (dq->rear == NULL)		//���ԭ����Ϊ��
		dq->front = dq->rear = p;
	else
	{
		dq->front->prear = p;		//��ͷ����ǰһ�����ָ��p
		p->next = dq->front;		//��p����һ��������ӵ�ͷ���
		dq->front = p;				//ͷ����Ϊp���
	}
}

template <typename T> void enRDLinkQueue(DLinkQueue<T> *&dq, T e)		//β���
{
	DDataNode<T> *p;
	p = new DDataNode<T>;
	p->data = e;
	p->next = NULL;
	p->prear = dq->rear;		//p��ǰ���ָ��β�ڵ�
	if (dq->rear == NULL)		//���ԭ����Ϊ��
		dq->front = dq->rear = p;
	else
	{	
		dq->rear->next = p;			//��β������һ���������p
		dq->rear = p;				//β����Ϊp���
	}
}

template <typename T> bool deFDLinkQueue(DLinkQueue<T> *&dq, T &e)		//ͷ����
{
	DDataNode<T> *t;
	if (dq->front == NULL)		//���ԭ����Ϊ��
		return false;
	t = dq->front;
	if (dq->front == dq->rear)		//������ֻ��һ�����
		dq->front = dq->rear = NULL;
	else
		dq->front = dq->front->next;
	e = t->data;
	delete t;
	return true;
}

template <typename T> bool deRDLinkQueue(DLinkQueue<T> *&dq, T &e)		//β����
{
	DDataNode<T> *t;
	if (dq->rear == NULL)		//���ԭ����Ϊ��
		return false;
	t = dq->rear;
	if (dq->front == dq->rear)		//������ֻ��һ�����
		dq->front = dq->rear = NULL;
	else
		dq->rear = dq->rear->prear;
	e = t->data;
	delete t;
	return true;
}