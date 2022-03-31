#include <iostream>

using namespace std;

template <typename T>
class List
{
private:
	T* underlying;
	int capacity;
	int length;
	bool orderEnsured;

public:
	List(int capacity)
	{
		length = 0;
		this->capacity = capacity;
		underlying = new T[capacity];
		orderEnsured = true;
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
		orderEnsured = false;

		if (index >= length)
			return false;

		underlying[index] = data;

		return true;
	}

	bool Add(T data)
	{
		if (length == capacity)
			return false;

		orderEnsured = false;

		underlying[length] = data;

		length++;

		return true;
	}

	bool Insert(int index, T data)
	{
		if (index > length || length == capacity)
			return false;

		orderEnsured = false;

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
		if (!orderEnsured)
			return -1;

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
	}

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

	void SortWithBubble()
	{
		BubbleSort(*this);
		orderEnsured = true;
	}

	void SortWithInsert()
	{
		InsertSort(*this);
		orderEnsured = true;
	}

	void SortWithQuick()
	{
		QuickSort(*this, 0, Length() - 1);
		orderEnsured = true;
	}

	void SortWithMerge()
	{
		MergeSort(*this);
		orderEnsured = true;
	}
	void SortWithExampleMerge()
	{
		MergeAsItWasWrittenOnThePresentation(underlying, 0, length - 1);
		orderEnsured = true;
	}

	bool IsOrdered()
	{
		return orderEnsured;
	}
};

template <typename T>
void BubbleSort(List<T>& list)
{
	for (int i = list.Length() - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (list[j] > list[j + 1])
			{
				T temp = list[j];
				list.Set(j, list[j + 1]);
				list.Set(j + 1, temp);
			}
		}
	}
}

template <typename T>
void InsertSort(List<T>& list)
{
	for (int i = i; i < list.Length(); i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (list[j] >= list[j - 1])
				break;

			T temp = list[j];
			list.Set(j, list[j - 1]);
			list.Set(j - 1, temp);
		}
	}
}

template <typename T>
void QuickSort(List<T>& list, int start, int end)
{
	if (start >= end)
		return;

	int i = start, j = end;

	while (i < j)
	{
		while (i < j && list[i] <= list[end])
			i++;

		while (i < j && list[j] >= list[end])
			j--;

		if (i != j)
		{
			T aux = list[j];
			list.Set(j, list[i]);
			list.Set(i, aux);
			Print(list);
		}

		if (i != end)
		{
			T aux = list[end];
			list.Set(end, list[i]);
			list.Set(i, aux);
			Print(list);
		}
	}

	QuickSort(list, start, i - 1);
	QuickSort(list, i + 1, end);
}

template <typename T>
void MergeSort(List<T>& list)
{
	if (list.Length() <= 1)
		return;
	int length = list.Length();
	List<T>** lists = new List<int>*[2];
	lists[0] = new List<T>(length / 2);
	lists[1] = new List<T>(length - lists[0]->Capacity());

	for (int i = 0; i < length; i++)
		lists[i >= (length / 2)]->Add(list[i]);

	MergeSort(*lists[0]);
	MergeSort(*lists[1]);

	int piv[2] = { 0, 0 };

	while (piv[0] + piv[1] < length)
	{
		int ind = piv[0] + piv[1];
		if (piv[1] >= lists[1]->Length() || piv[0] < lists[0]->Length() && (*lists[0])[piv[0]] < (*lists[1])[piv[1]])
			list.Set(ind, (*lists[0])[piv[0]++]);
		else
			list.Set(ind, (*lists[1])[piv[1]++]);
	}

	delete lists[0];
	delete lists[1];
	delete[] lists;
}

template <typename T>
void MergeAsItWasWrittenOnThePresentation(T* arr, int extizq, int extder)
{
	if (extizq >= extder)
		return;

	int medio = (extizq + extder) / 2;
	MergeAsItWasWrittenOnThePresentation(arr, extizq, medio, 27);
	MergeAsItWasWrittenOnThePresentation(arr, medio + 1, extder, 27);

	int* temp = new int[extder];

	memcpy_s(temp + extizq, sizeof(int) * (extder - extizq + 1), arr + extizq, sizeof(int) * (extder - extizq + 1));

	int i = extizq, j = medio + 1, x = extizq;

	while (i <= medio && j <= extder)
	{
		while (i <= medio && temp[i] <= temp[j])
		{
			arr[x] = temp[i];

			++i;
			++x;
		}

		if (i <= medio)
		{
			while (j <= extder && temp[j] <= temp[i])
			{
				arr[x] = temp[j];

				++j;
				++x;
			}
		}
	}

	while (i <= medio)
	{
		arr[x] = temp[i];
		++i;
		++x;
	}

	while (j <= extder)
	{
		arr[x] = temp[j];
		++j;
		++x;
	}
	delete temp;
}

void ShowOrder(List<int> &list)
{
	int opc;
	do
	{
		cout << " Seleccione una opcion:\n\n 1.- Burbuja\n 2.- Insercion\n 3.- QuickSort\n 4.- Merge Sort\n 5.- Merge Sort como en la presentación\n 6.- Volver\n\n > ";
		cin >> opc;
		switch (opc)
		{
		case 1:
			list.SortWithBubble();
			cout << "Se ha ordenado correctamente\n";
			break;
		case 2:
			list.SortWithInsert();
			cout << "Se ha ordenado correctamente\n";
			break;
		case 3:
			list.SortWithQuick();
			cout << "Se ha ordenado correctamente\n";
			break;
		case 4:
			list.SortWithMerge();
			cout << "Se ha ordenado correctamente (aunque el procedimiento me da migraña)\n";
			break;
		case 5:
			list.SortWithExampleMerge();
			cout << "Se ha ordenado correctamente\n";
			break;
		case 6:
			return;
		default:
			break;
		}
	} while (opc != 6);
}

void ShowSearch(List<int> &list)
{
	int opc;
	do
	{
		cout << "Seleccione una opcion:\n\n 1.- Busqueda secuencial\n 2.- Busqueda binaria\n 3.- Volver\n\n > ";
		cin >> opc;
		switch (opc)
		{
		case 1:
		{
			int c;
			cout << "Escribe el valor a buscar" << endl;
			cin >> c;
			int res = list.Search(c);
			if (res == -1)
				cout << "No se encontró el numero" << endl;
			else
				cout << "Se encontró el numero en la posición " << res << endl;
			break;
		}
		case 2:
		{
			if (!list.IsOrdered())
			{
				cout << "La lista no está ordenada, no se puede realizar busqueda binaria" << endl;
				break;
			}

			int c;
			cout << "Escribe el valor a buscar" << endl;
			cin >> c;
			int res = list.BinarySearch(c);
			if (res == -1)
				cout << "No se encontró el numero" << endl;
			else
				cout << "Se encontró el numero en la posición " << res << endl;
			break;
		}
		case 3:
			return;
		default:
			break;
		}
	} while (opc != 3);
}


int main()
{
	setlocale(LC_ALL, "es_MX");
	List<int> list(10);

	int opc;
	do
	{
		cout << " Seleccione una opcion:\n\n 1.- Agregar al final\n 2.- Insertar en posicion\n 3.- Eliminar en posicion\n 4.- Imprimir todo\n 5.- Comprobar vacia\n 6.- Comprobar llena \n"
			<< " 7.- Imprimir primero\n 8.- Imprimir ultimo\n 9.- Limpiar\n 10.- Ordenar\n 11.- Buscar\n 12.- Salir\n\n > ";
		cin >> opc;
		switch (opc)
		{
		case 1:
		{
			if (list.Full())
			{
				cout << "La lista está llena, no se puede agregar" << endl;
				break;
			}

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
			{
				cout << "La lista está llena, no se puede agregar" << endl;
				break;
			}

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
			{
				cout << "La lista está vacia, no se puede eliminar" << endl;
				break;
			}

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
				break;
			}

			cout << "Elementos en la lista: ";

			for (int i = 0; i < list.Length(); i++)
				cout << list[i] << ' ';

			cout << endl;

			system("pause");
			break;
		}
		case 5:
			if (list.Empty())
				cout << "La lista está vacia" << endl;
			else
				cout << "La lista no está vacia" << endl;
			system("pause");
			break;
		case 6:
			if (list.Full())
				cout << "La lista está llena" << endl;
			else
				cout << "La lista no está llena" << endl;
			system("pause");
			break;

		case 7:
			if (list.Empty())
			{
				cout << "La lista esta vacia" << endl;
				system("pause");
				break;
			}

			cout << "Elemento primero: " << list.First() << endl;
			break;
		case 8:
			if (list.Empty())
			{
				cout << "La lista esta vacia" << endl;
				system("pause");
				break;
			}

			cout << "Elemento ultimo: " << list.Last() << endl;
			break;

		case 9:
			list.Clear();
			cout << "Se ha limpiado la lista" << endl;
			break;
		case 10:
			ShowOrder(list);
			break;
		case 11:
			if (list.Empty())
			{
				cout << "La lista está vacia, no se puede realizar ninguna busqueda" << endl;
				break;
			}
			ShowSearch(list);
			break;
		case 12:
			return 0;
		default:
			cout << "No se encuentra la opción" << endl;
			break;
		}
	} while (opc != 12);
}
