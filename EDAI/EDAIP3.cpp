#include <iostream>

using namespace std;

template <typename T>
class CircularQueue
{
private:
	int capacity;
	int end;
	int start;
	bool shouldBeEmpty;
	T* underlying;

public:
	CircularQueue(int capacity)
	{
		this->capacity = capacity;
		start = 0;
		shouldBeEmpty = true;
		end = capacity - 1;
		underlying = new T[capacity];
		for (int i = 0; i < capacity; i++)
		{
			underlying[i] = 0;
		}
	}

	bool Enqueue(T data)
	{
		if ((end + 1) % capacity == start && !shouldBeEmpty)
			return false;

		end = (end + 1) % capacity;
		underlying[end] = data;
		shouldBeEmpty = false;

		return true;
	}

	T Dequeue()
	{
		T out = underlying[start];
		shouldBeEmpty = start == end;

		start = (start + 1) % capacity;
		return out;
	}

	bool TryDequeue(T& out)
	{
		if (shouldBeEmpty)
		{
			out = 0;
			return false;
		}
		out = Dequeue();
		return true;
	}

	T Peek()
	{
		return underlying[start];
	}

	bool TryPeek(T& out)
	{
		if (shouldBeEmpty)
		{
			out = 0;
			return false;
		}

		out = Peek();
		return true;
	}

	bool Empty()
	{
		return shouldBeEmpty;
	}

	bool Full()
	{
		return !shouldBeEmpty && (end + 1) % capacity == start;
	}

	int Length()
	{
		if (end >= start)
			return end - start + 1;
		return end + capacity - start + 1;
	}

	int Capacity()
	{
		return capacity;
	}

	void Clear()
	{
		while (!Empty())
			Dequeue();
	}
};

int main()
{
	std::setlocale(LC_ALL, "es_MX");
	CircularQueue<char> queue(8);

	int opc;
	do
	{
		cout << " Seleccione una opcion:\n\n 1.- Encolar caracter \n 2.- Desencolar caracter\n 3.- Mostrar frente \n 4.- Imprimir cola \n 5.- Comprobar vacia\n 6.- Comprobar llena\n 7.- Salir\n\n > ";
		cin >> opc;
		switch (opc)
		{
		case 1:
		{
			if (queue.Full())
			{
				cout << "La cola está llena, no se puede encolar" << endl;
				break;
			}

			char c;
			cout << "Escribe el caracter\n";
			cin >> c;

			if (queue.Enqueue(c))
				cout << "Se encoló el caracter\n";
			else
				cout << "La cola está llena, no se puede encolar" << endl;

			system("pause");
			break;
		}
		case 2:
		{
			if (queue.Empty())
			{
				cout << "La cola está vacia, no se puede desencolar" << endl;
				system("pause");
				break;
			}

			char c;
			if (queue.TryDequeue(c))
				cout << "Caracter desencolado: " << c << endl;
			else
				cout << "La cola está vacia, no se puede desencolar" << endl;
			system("pause");
			break;
		}
		case 3:
		{
			if (queue.Empty())
			{
				cout << "La cola está vacia, no se puede mostrar el frente" << endl;
				system("pause");
				break;
			}

			char c;
			if (queue.TryPeek(c))
				cout << "Caracter en el frente: " << c << endl;
			else
				cout << "La cola está vacia, no se puede mostrar el frente" << endl;
			system("pause");
			break;
		}
		case 4:
		{

			if (queue.Empty())
			{
				cout << "La cola está vacia" << endl;
				system("pause");
				break;
			}

			char c;
			CircularQueue<char> aux(queue.Capacity());

			while (!queue.Full())
				queue.Enqueue('\0');

			cout << "Caracteres en la cola: ";
			while (!queue.Empty())
			{
				c = queue.Dequeue();
				if (c != '\0')
				{
					cout << c << ' ';
					aux.Enqueue(c);
				}
			}

			cout << endl;

			while (!aux.Empty())
				queue.Enqueue(aux.Dequeue());

			system("pause");
			break;
		}
		case 5:
			if (queue.Empty())
				cout << "La cola está vacia" << endl;
			else
				cout << "La cola no está vacia" << endl;
			system("pause");
			break;
		case 6:
			if (queue.Full())
				cout << "La cola está llena" << endl;
			else
				cout << "La cola no está llena" << endl;
			system("pause");
			break;
		case 7:
			return 0;
		default:
			cout << "No se encuentra la opción" << endl;
			break;
		}
	} while (opc != 7);
}