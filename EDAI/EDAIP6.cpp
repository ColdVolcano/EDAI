#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
	T Data;
	Node<T>* Next;
	Node(T data)
	{
		Data = data;
		Next = nullptr;
	}

	T First()
	{
		return Data;
	}

	T Last()
	{
		return Next == nullptr ? Data : Next->Last();
	}

	bool Set(int index, T data)
	{
		if (index == 0)
		{
			Data = data;
			return true;
		}
		return Next == nullptr ? false : Next->Set(index - 1, data);
	}

	bool Add(T newData)
	{
		if (Next == nullptr)
			Next = new Node<T>(newData);
		else
			Next->Add(newData);

		return true;
	}

	Node<T>* Insert(T newData, int position)
	{
		if (position == 1)
		{
			Node<T>* aux = Next;

			Next = new Node<T>(newData);
			Next->Next = aux;

			return this;
		}

		if (position == 0)
		{
			Node<T>* aux = new Node<T>(newData);
			aux->Next = this;

			return aux;
		}

		if (Next == nullptr)
			return nullptr;

		Next->Insert(newData, position - 1);

		return this;
	}

	Node<T>* RemoveAt(int index)
	{
		if (index > 0 && Next == nullptr)
			return nullptr;
		
		if (index == 0)
		{
			return Next;
		}

		if (index == 1)
		{
			Node<T>* aux = Next;

			Next = Next->Next;

			aux->Next = nullptr;

			delete aux;

			return this;
		}

		Next->RemoveAt(index - 1);

		return this;
	}

	bool TryGet(int index, T& out)
	{
		if (index > 0 && Next == nullptr)
			return false;

		if (index == 0)
			out = Data;
		else
			Next->TryGet(index - 1, out);

		return true;
	}

	int Length()
	{
		return length(1);
	}

private:
	int length(int current)
	{
		if (Next == nullptr)
			return current;
		return Next->length(current + 1);
	}

public:
	void Clear()
	{
		if (Next != nullptr)
		{
			Next->Clear();
			delete Next;
		}
		Next = nullptr;
	}
};

int main()
{
	Node<int>* startingNode = nullptr;
	int opc;
	do
	{
		cout << " Seleccione una opcion:\n\n 1.- Agregar al final\n 2.- Insertar en posicion\n 3.- Eliminar en posicion\n 4.- Imprimir todo\n 5.- Comprobar vacia\n 6.- Comprobar llena \n"
			<< " 7.- Imprimir primero\n 8.- Imprimir ultimo\n 9.- Limpiar\n 10.- Salir\n\n > ";

		cin >> opc;
		switch (opc)
		{
		case 1:
		{
			int c;
			cout << "Escribe el numero\n";
			cin >> c;

			if (startingNode == nullptr)
			{
				startingNode = new Node<int>(c);
				cout << "Se agregó el numero\n";

			}
			else
			{
				startingNode->Add(c);
				cout << "Se agregó el numero\n";
			}

			system("pause");
			break;
		}
		case 2:
		{
			int c, i;
			Node<int>* aux;
			cout << "Escribe el numero\n";
			cin >> c;

			cout << "Escribe la posicion\n";
			cin >> i;

			if ((aux = (startingNode == nullptr && i == 0 ? new Node<int>(c) : startingNode->Insert(c, i))) != nullptr)
			{
				cout << "Se agregó el numero\n";
				if (aux != startingNode)
					startingNode = aux;
			}
			else
				cout << "Se intentó ingresar fuera del tamaño actual de la lista, no se puede agregar" << endl;

			system("pause");
			break;
		}
		case 3:
		{
			if (startingNode == nullptr)
			{
				cout << "La lista está vacia, no se puede eliminar" << endl;
				break;
			}

			Node<int>* aux;
			int i;
			cout << "Escribe la posicion\n";
			cin >> i;

			if ((aux = startingNode->RemoveAt(i)) != nullptr)
			{
				if (aux != startingNode)
				{
					startingNode->Next = nullptr;
					startingNode = aux;
				}

				cout << "El dato fue eliminado" << endl;
			}
			else
				cout << "No se pudo eliminar el dato" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			if (startingNode == nullptr)
			{
				cout << "La lista esta vacia" << endl;
				system("pause");
				break;
			}

			cout << "Elementos en la lista: ";

			Node<int>* aux = startingNode;

			while (aux != nullptr)
			{
				cout << aux->Data << ' ';
				aux = aux->Next;
			}

			cout << endl;

			system("pause");
			break;
		}
		case 5:
			if (startingNode == nullptr)
				cout << "La lista está vacia" << endl;
			else
				cout << "La lista no está vacia" << endl;
			system("pause");
			break;
		case 6:
			cout << "La lista no está llena" << endl;
			system("pause");
			break;

		case 7:
			if (startingNode == nullptr)
			{
				cout << "La lista esta vacia" << endl;
				system("pause");
				break;
			}

			cout << "Elemento primero: " << startingNode->Data << endl;
			break;
		case 8:
			if (startingNode == nullptr)
			{
				cout << "La lista esta vacia" << endl;
				system("pause");
				break;
			}

			cout << "Elemento ultimo: " << startingNode->Last() << endl;
			break;

		case 9:
			startingNode->Clear();
			delete startingNode;
			startingNode = nullptr;
			cout << "Se ha limpiado la lista" << endl;
			break;

		case 10:
			return 0;
		default:
			cout << "No se encuentra la opción" << endl;
			break;
		}

	} while (opc != 10);

	return 0;
}