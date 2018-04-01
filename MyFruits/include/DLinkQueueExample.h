#pragma once
#include"DLinkQueue.h"

void DLinkQueueExamples()
{
	DLinkQueue<int> *dq;
	InitDLinkQueue(dq);
	int a[] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++)
	{
		enFDLinkQueue(dq, a[i]);
	}
	int e;
	while (!DLinkQueueEmpty(dq))
	{
		deRDLinkQueue(dq, e);
		cout << '\t' << e;
	}
	DestroyDLinkQueue(dq);
}