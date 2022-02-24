// EDAI.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Stack
{
private:
	int length;
	int capacity = 100;
	T* underlying;
public:
	Stack(int capacity)
	{
		this->capacity = capacity;
		underlying = new T[capacity];

		for (int i = 0; i < capacity; i++)
			underlying[i] = 0;

		length = 0;
	}

	~Stack()
	{
		delete underlying;
	}

	bool Push(T data)
	{
		if (length == capacity)
			return false;

		underlying[length] = data;
		length++;

		return true;
	}

	T Pop()
	{
		if (length == 0)
			return 0;

		length--;

		T data = underlying[length];

		underlying[length] = 0;

		return data;
	}

	T Peek()
	{
		return length == 0 ? 0 : underlying[length - 1];
	}

	bool Empty()
	{
		return length == 0;
	}

	bool Full()
	{
		return length == capacity;
	}

	int Length()
	{
		return length;
	}

	int Capacity()
	{
		return capacity;
	}
};

int charType(char c)
{
	switch (c)
	{
	case '(':
		return -1;
	case ')':
		return -2;                                    
	case '\0':
		return -3;
	case ' ':
		return -4;
	case '^':
		return 3;
	case '/':
	case '*':
		return 2;
	case '-':
	case '+':
		return 1;
	default:
		return 0;
	}
}

int main()
{
	string i, o;
	cout << "Escriba una operacion infjia:" << endl;
	getline(cin, i);
	Stack<char> stack(i.length());
	for (char c : i)
	{
		int ct = charType(c);
		switch (ct)
		{
		case -1:
			stack.Push(c);
			break;
		case -2:
		{
			char sc;
			while (charType(sc = stack.Pop()) != -1)
			{
				o += sc;
			}
			break;
		}
		case -4:
			break;
		case 0:
			o += c;
			break;
		case 1:
		case 2:
		case 3:
		{
			int sc;
			while (!stack.Empty() && (sc = charType(stack.Peek())) > 0 && sc >= ct)
			{
				o += stack.Pop();
			}
			stack.Push(c);
			break;
		}
		}
	}

	while (!stack.Empty())
		o += stack.Pop();

	cout << o << endl;

	return 0;
}
