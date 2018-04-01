#pragma once
#include"SqStack.h"

//////////////////////////////////////////////////////////////////// 
// Examples
//////////////////////////////////////////////////////////////////// 

bool Symmetry(char str[])
{
	int i; char e;
	SqStack<char> *st;
	InitStack(st);
	for (i = 0; str[i] != '\0'; i++)
	{
		Push(st, str[i]);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		Pop(st, e);
		if (str[i] != e)
		{
			DestroyStack(st);
			return false;
		}
	}
	DestroyStack(st);
	return true;
}

void SymmetryExample()
{
	char a[] = { '1', '2', '3', '4', '5' };
	char b[] = { 'a', 'b', 'b', 'a', '\0' };
	const int n = 5;

	SqStack<char> *S;
	InitStack(S);

	if (Symmetry(b)) {
		cout << b << ": a symmetric string." << endl;
	}
	else {
		cout << b << ": an asymmetric string." << endl;
	}
	DispStack(S);
	DestroyStack(S);
}

void trans(char *exp, char postexp[])
{
	char e;
	SqStack<char> *Optr;
	InitStack(Optr);
	int i = 0;
	while (*exp != '\0')
	{
		switch (*exp)
		{
		case'(':
			//cout << "(";
			Push(Optr, '(');
			exp++;
			break;
		case')':
			Pop(Optr, e);
			while (e != '(')
			{
				postexp[i++] = e;
				Pop(Optr, e);
			}
			exp++;
			break;
		case'+':
		case'-':
			while (!StackEmpty(Optr))
			{
				GetTop(Optr, e);
				if (e != '(')
				{
					postexp[i++] = e;
					Pop(Optr, e);
				}
				else
					break;
			}
		case'*':
		case'/':
			while (!StackEmpty(Optr))
			{
				GetTop(Optr, e);
				if (e == '*' || e == '/')
				{
					postexp[i++] = e;
					Pop(Optr, e);
				}
				else
					break;
			}
			Push(Optr, *exp);
			exp++;
			break;
		default:
			while (*exp >= '0' && *exp <= '9')
			{
				postexp[i++] = *exp;
				exp++;
			}
			postexp[i++] = '#';
		}
	}
	while (!StackEmpty(Optr))
	{
		Pop(Optr, e);
		postexp[i++] = e;
	}
	postexp[i] = '\0';
	DestroyStack(Optr);
}

double compvalue(char *postexp)
{
	double d, a, b, c, e;
	SqStack<double> *Opnd;
	InitStack(Opnd);
	while (*postexp != '\0')
	{
		switch (*postexp)
		{
		case '+':
			Pop(Opnd, a);
			Pop(Opnd, b);
			c = b + a;
			Push(Opnd, c);
			break;
		case '-':
			Pop(Opnd, a);
			Pop(Opnd, b);
			c = b - a;
			Push(Opnd, c);
			break;
		case '*':
			Pop(Opnd, a);
			Pop(Opnd, b);
			c = b * a;
			Push(Opnd, c);
			break;
		case '/':
			Pop(Opnd, a);
			Pop(Opnd, b);
			c = b / a;
			Push(Opnd, c);
			break;
		default:
			d = 0;
			while (*postexp >= '0' && *postexp <= '9')
			{
				d = 10 * d + *postexp - '0';
				postexp++;
			}
			Push(Opnd, d);
			break;
		}
		postexp++;
	}
	GetTop(Opnd, e);
	DestroyStack(Opnd);
	return e;
}

void PostExpressionExample()
{
	char exp[] = "(56-20)/(4+2)";
	char postexp[200] = { 0 };
	trans(exp, postexp);
	cout << "��׺���ʽ��" << exp << endl;
	cout << "��׺���ʽ��" << postexp << endl;
	cout << "���ʽ��ֵ��" << compvalue(postexp) << endl;
}

bool JudgeLegal(const string &s1, const string &s2)
{
	SqStack<char> *sc = new SqStack<char>;
	InitStack(sc);

	int i = 0, j = 0;
	char e;
	while (s2[i] != '\0')
	{
		if (s1[j] != s2[i] && s1[j] != '\0')
		{
			Push(sc, s1[j]);
			j++;
		}
		else if (s1[j] == s2[i])
		{
			i++;
			j++;
		}
		else
		{
			Pop(sc, e);
			if (e != s2[i])
				return false;
			i++;
		}
	}
	return true;
}

void JudgeLegalExample()
{
	string s1 = "12345", s2 = "45132";
	if (JudgeLegal(s1, s2)) {
		cout << "input order:" << s1 << ", check order:" << s2 << ", is legal." << endl;
	}
	else {
		cout << "input order:" << s1 << ", check order:" << s2 << ", is illegal." << endl;
	}
}

void SqStackExample()
{
	SymmetryExample();
	PostExpressionExample();
	JudgeLegalExample();
}

// �Թ����

typedef struct Box
{
	int x;		//������
	int y;		//������
	int z;		//����
}Box;

int MG[8 + 2][8 + 2] =				//��ά��ͼ
{
	{ 1, 1,1,1,1,1,1,1,1,  1 },
	{ 1, 0,0,1,0,0,0,1,0,  1 },
	{ 1, 0,0,1,0,0,0,1,0,  1 },
	{ 1, 0,0,0,0,1,1,0,0,  1 },
	{ 1, 0,1,1,1,0,0,0,0,  1 },
	{ 1, 0,0,0,1,0,0,0,0,  1 },
	{ 1, 0,1,0,0,0,1,0,0,  1 },
	{ 1, 0,1,1,1,0,1,1,0,  1 },
	{ 1, 1,0,0,0,0,0,0,0,  1 },
	{ 1, 1,1,1,1,1,1,1,1,  1 }
};

bool Dirction(int &i, int &j, int &di)		//�ж��²�����
{
	di = 0;
	int dx, dy;
	while (di < 4)
	{
		switch (di)
		{
		case 0: dx = i - 1, dy = j; break;
		case 1: dx = i, dy = j + 1; break;
		case 2: dx = i + 1, dy = j; break;
		case 3: dx = i, dy = j - 1; break;
		}
		if (MG[dx][dy] == 0) {
			i = dx; j = dy;
			return true;
		}
		di++;
	}
	return false;
}

bool MGpath(int xi, int yi, int xe, int ye)		//��ڣ�xi, yi) �����ڣ�xe, ye��
{
	int i = xi, j = yi, di;
	Box e, path[MAX_SIZE];
	SqStack<Box> *st = 0;
	InitStack(st);
	e.x = xi, e.y = yi, e.z = -1;		
	Push(st, e);		//ѹջ����¼���λ��

	while (!StackEmpty(st))
	{
		GetTop(st, e);
		if (e.x == xe && e.y == ye)		//�������λ��
		{
			int k = 0;
			while (st->top >= 0)
			{
				Pop(st, e);
				path[k++] = e;		//��ջ�������ݴ�������
			}
			while (k > 0)
			{
				k--;
				cout << "\t(" << path[k].x << "," << path[k].y << ")";		//��ӡ·��
				if ((k + 2) % 5 == 0)
					cout << endl;
			}
			DestroyStack(st);
			return true;
		}
		else
		{
			if (Dirction(i, j, di))		//�ж��²�����
			{
				st->data[st->top].z = di;
				e.x = i; e.y = j;
				Push(st, e);
				MG[e.x][e.y] = -1;			
			}
			else if (!Dirction(i, j, di) && StackEmpty(st))		//��·���ߡ�û����·��ջΪ�գ�
			{
				cout << "No answer!\n";	
				return false;
			}
			else		//��·���ߡ�����·��ջ��Ϊ�գ�
			{
				Pop(st, e);				//��ջ����һ����
				MG[e.x][e.y] = 1;		//����߹�������ͬ
				st->data[st->top].z = -1;
				GetTop(st, e);
				i = e.x, j = e.y;
			}					
		}
	}
	return true;
}