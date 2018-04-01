#pragma once
#include "LinkQueue.h"

void LinkQueueExample()
{
	LinkQuNode<int> *q;
	InitQueue(q);
	int a[] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++)
	{
		enQueue(q, a[i]);
	}
	int e;
	while (!QueueEmpty(q))
	{
		deQueue(q, e);
		cout << '\t' << e;
	}
}