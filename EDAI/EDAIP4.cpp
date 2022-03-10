#include <iostream>

using namespace std;

template <typename T>
class List
{
private:
	T* underlying;
	int capacity;
	int length;

public:
	List(int capacity)
	{
		length = 0;
		this->capacity = capacity;
		underlying = new T[capacity];
	}

	T First()
	{
		return underlying[0];
	}

	T Last()
	{
		return underlying[length - 1];
	}

	bool Set(int index, T data)
	{
		if (index >= length)
			return false;

		underlying[index] = data;

		return true;
	}

	bool Add(T data)
	{
		if (length == capacity)
			return false;

		underlying[length] = data;

		length++;

		return true;
	}

	bool Insert(int index, T data)
	{
		if (index > length || length == capacity)
			return false;

		for (int i = length; i > index; i--)
			underlying[i] = underlying[i - 1];

		underlying[index] = data;

		length++;
		return true;
	}

	/*bool InsertAfter(T after, T data)
	{
		if (length == capacity)
			return false;

		int index = Search(after);

		return index == -1 ? false : this->Insert(index + 1, data);
	}

	bool InsertBefore(T before, T data)
	{
		if (length == capacity)
			return false;

		int index = Search(before);

		return index == -1 ? false : this->Insert(index, data);
	}*/
	//0 1 2 3 4 5 6 7 8 9 

	bool RemoveAt(int index)
	{
		if (index >= length || length == 0)
			return false;

		for (int j = index; j < length - 1; j++)
		{
			underlying[j] = underlying[j + 1];
		}

		length--;
		underlying[length] = 0;
		return true;
	}

	bool Empty()
	{
		return length == 0;
	}

	bool Full()
	{
		return length == capacity;
	}

	T operator[](int i)
	{
		return underlying[i];
	}
	
	bool TryGet(int index, T& out)
	{
		if (index >= length || length == 0)
			return false;

		out = this[index];

		return true;
	}

	/*

	int Search(T data)
	{
		for (int i = 0; i < length; i++)
		{
			if (underlying[i] == data)
				return i;
		}

		return -1;
	}

	int BinarySearch(T data)
	{
		int botLim = 0, topLim = length, ind;
		while (botLim < topLim)
		{
			ind = (botLim + topLim) / 2;

			if (underlying[ind] == data)
				return ind;

			if (underlying[ind] > data)
				botLim = ind + 1;
			else
				topLim = ind;
		}

		return -1;
	}*/

	int Length()
	{
		return length;
	}

	int Capacity()
	{
		return capacity;
	}

	void Clear()
	{
		while (!Full())
			RemoveAt(length - 1);
	}
};

int main()
{
	List<int> list(10);

	int opc;
	do
	{
		cout << " Seleccione una opcion:\n\n 1.- Agregar al final\n 2.- Insertar en posicion\n 3.- Eliminar en posicion\n 4.- Imprimir todo\n 5.- Comprobar vacia\n 6.- Comprobar llena \n"
			" 7.- Imprimir primero\n 8.- Imprimir ultimo\n 9.- Limpiar\n 10.- Salir\n\n > ";
		cin >> opc;
		switch (opc)
		{
		case 1:
		{
			if (list.Full())
				cout << "La lista está llena, no se puede agregar" << endl;

			int c;
			cout << "Escribe el numero\n";
			cin >> c;

			if (list.Add(c))
				cout << "Se agregó el numero\n";
			else
				cout << "La lista está llena, no se puede agregar" << endl;

			system("pause");
			break;
		}
		case 2:
		{
			if (list.Full())
				cout << "La lista está llena, no se puede agregar" << endl;

			int c, i;
			cout << "Escribe el numero\n";
			cin >> c;

			cout << "Escribe la posicion\n";
			cin >> i;

			if (list.Insert(i, c))
				cout << "Se agregó el numero\n";
			else
				cout << "Se intentó ingresar fuera del tamaño actual de la lista, no se puede agregar" << endl;

			system("pause");
			break;
		}
		case 3:
		{
			if (list.Empty())
				cout << "La lista está vacia, no se puede eliminar" << endl;

			int i;
			cout << "Escribe la posicion\n";
			cin >> i;

			if (list.RemoveAt(i))
				cout << "El dato fue eliminado" << endl;
			else
				cout << "No se pudo eliminar el dato" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			if (list.Empty())
			{
				cout << "La lista esta vacia" << endl;
				system("pause");
			}

			cout << "Elementos en la lista: ";

			for (int i = 0; i < list.Length(); i++)
				cout << list[i];

			cout << endl;

			system("pause");
			break;
		}
		case 5:
			if (list.Empty())
				cout << "La cola está vacia" << endl;
			else
				cout << "La cola no está vacia" << endl;
			system("pause");
			break;
		case 6:
			if (list.Full())
				cout << "La cola está llena" << endl;
			else
				cout << "La cola no está llena" << endl;
			system("pause");
			break;

		case 7:
			if (list.Empty())
			{
				cout << "La lista esta vacia" << endl;
				system("pause");
			}

			cout << "Elemento primero: " << list.First() << endl;
			break;
		case 8:
			if (list.Empty())
			{
				cout << "La lista esta vacia" << endl;
				system("pause");
			}

			cout << "Elemento ultimo: " << list.Last() << endl;
			break;

		case 9:
			list.Clear();
			cout << "Se ha limpiado la lista" << endl;
			break;

		case 10:
			return 0;
		default:
			cout << "No se encuentra la opción" << endl;
			break;
		}
	} while (opc != 10);
}