#pragma once
#include"basic.h"
#include"SqStack.h"

void first()
{
	SqStack<char> *Optr, *temp;
	InitStack(Optr);
	InitStack(temp);
	char exp[30];
	cin >> exp;
	char e, postexp[100];
	int length = 0;
	for (int i = 0; exp[i] != '\0'; i++)
	{
		switch (exp[i])
		{
		case '(':
			Push(Optr, exp[i]);
			break;
		case ')':
			Pop(Optr, e);
			while (e != '(')
			{
				postexp[length++] = e;
				postexp[length++] = ' ';
				Pop(Optr, e);
			}
			break;
		case '+':
		case '-':
			while (!StackEmpty(Optr))
			{
				GetTop(Optr, e);
				if (e != '(')
				{
					postexp[length++] = e;
					postexp[length++] = ' ';
					Pop(Optr, e);
				}
				else
					break;
			}
		case '*':
		case '/':
			while (!StackEmpty(Optr))
			{
				GetTop(Optr, e);
				if (e == '*' || e == '/')
				{
					postexp[length++] = e;
					postexp[length++] = ' ';
					Pop(Optr, e);
				}
				else
					break;
			}
			Push(Optr, exp[i]);
			break;
		default:
			postexp[length++] = exp[i];
			postexp[length++] = ' ';
		}
	}
	while (!StackEmpty(Optr))
	{
		Pop(Optr, e);
		postexp[length++] = e;
		postexp[length++] = ' ';
	}
	postexp[length-1] = '\0';
	cout << postexp;
}