#define MAX 1000

int stack[MAX];
int cur = 0;

void push(int data)
{
	if(cur < MAX)
	{
		stack[cur++] = data;
	}
	else
	{
		assert(NULL);
	}
}

int top()
{
	if(cur == 0)
	{
		assert(NULL);
		return -1;
	}
	return stack[cur - 1];
}

int size()
{
	return cur;
}

void pop()
{
	if(cur == 0)
	{
		assert(NULL);
		return;
	}
	cur--;
}
