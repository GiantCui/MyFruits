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

typedef struct
{
	int i;	//��ǰ������к�
	int j;	//��ǰ������к�
	int di;	//di����һ�������ڷ�λ�ķ�λ��
} Box;		//���巽������


int mg[8 + 2][8 + 2] =
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


bool mgpath(int xi, int yi, int xe, int ye)	//���·��Ϊ:(xi,yi)->(xe,ye)
{
	Box path[MAX_SIZE], e;  int i, j, di, i1, j1, k;   bool find;
	SqStack<Box> *st = 0;			//����ջst
	InitStack(st);				//��ʼ��ջ��ָ��
	e.i = xi; e.j = yi; e.di = -1;			//����eΪ���
	Push(st, e);				//����e��ջ
	mg[xi][yi] = -1;	//��ڵ��Թ�ֵ��Ϊ-1�����ظ��ߵ��÷���

	while (!StackEmpty(st))		//ջ����ʱѭ��
	{
		GetTop(st, e);		//ȡջ������e
		i = e.i; j = e.j; di = e.di;
		if (i == xe && j == ye)		//�ҵ��˳���,�����·��
		{
			printf("һ���Թ�·������:\n");
			k = 0;
			while (!StackEmpty(st))
			{
				Pop(st, e);		//��ջ����e
				path[k++] = e;	//��e��ӵ�path������
			}
			while (k >= 1)
			{
				k--;
				printf("\t(%d,%d)", path[k].i, path[k].j);
				if ((k + 2) % 5 == 0)  //ÿ���ÿ5�������һ��
					printf("\n");
			}
			printf("\n");
			DestroyStack(st);//����ջ
			return true;	//���һ���Թ�·���󷵻�true
		}
		find = false;
		while (di<4 && !find)   //�����ڿ��߷���(i1,j1)
		{
			di++;
			switch (di)
			{
			case 0:i1 = i - 1; j1 = j;   break;
			case 1:i1 = i;   j1 = j + 1; break;
			case 2:i1 = i + 1; j1 = j;   break;
			case 3:i1 = i;   j1 = j - 1; break;
			}
			if (mg[i1][j1] == 0)  find = true;
			//�ҵ�һ�����ڿ��߷��飬����findΪ��
		}
		if (find)  		//�ҵ���һ�����ڿ��߷���(i1,j1)
		{
			st->data[st->top].di = di;	  //�޸�ԭջ��Ԫ�ص�diֵ
			e.i = i1; e.j = j1; e.di = -1;
			Push(st, e);		  //���ڿ��߷���e��ջ
			mg[i1][j1] = -1;
			//(i1,j1)�Թ�ֵ��Ϊ-1�����ظ��ߵ��÷���
		}
		else			//û��·������,����ջ
		{
			Pop(st, e);	//��ջ��������ջ
			mg[e.i][e.j] = 0;
			//����ջ�����λ�ñ�Ϊ����·�����߷���
		}
	}
	DestroyStack(st);	//����ջ
	return false;		//��ʾû�п���·��
}

void mgpath_example()
{
	if (!mgpath(1, 1, 8, 8)) {
		printf("���Թ�����û�н�!");
	}
}
