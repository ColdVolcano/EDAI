#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T Data;
	Node<T>* Left;
	Node<T>* Right;

	Node(T data)
	{
		this->Data = data;
		Left = nullptr;
		Right = nullptr;
	}

	void Insert(T data)
	{
		if (data < Data)
		{
			if (Left == nullptr)
				Left = new Node<T>(data);
			else 
				Left->Insert(data);
		}
		else
		{
			if (Right == nullptr)
				Right = new Node<T>(data);
			else
				Right->Insert(data);
		}
	}

	void Inorder()
	{
		if (Left)
			Left->Inorder();
		cout << Data << ' ';
		if (Right)
			Right->Inorder();
	}

	void Preorder()
	{
		cout << Data << ' ';
		if (Left)
			Left->Preorder();
		if (Right)
			Right->Preorder();
	}

	void Postorder()
	{
		if (Left)
			Left->Postorder();
		if (Right)
			Right->Postorder();
		cout << Data << ' ';
	}
};

template <typename T>
class BinaryTree
{
	Node<T>* root = nullptr;

public:
	bool IsEmpty()
	{
		return root == nullptr;
	}

	void Insert(T data)
	{
		if (root == nullptr)
			root = new Node<T>(data);
		else
			root->Insert(data);
	}

	bool Delete(T data)
	{
		if (root == nullptr)
			return false;
		Node<T> *parent = nullptr, *aux = root;

		while (aux != nullptr)
		{
			if (aux->Data == data)
			{
				if (aux->Left == nullptr && aux->Right == nullptr)
				{
					delete aux;
					if (parent == nullptr)
						root = nullptr;
					else if (parent->Data > data)
						parent->Left = nullptr;
					else
						parent->Right = nullptr;

					return true;
				}
				else if (aux->Left != nullptr && aux->Right != nullptr)
				{
					Node<T>* successor = aux->Right, *successorParent = aux;

					while (successor->Left != nullptr)
					{
						successorParent = successor;
						successor = successor->Left;
					}

					T tempData = successor->Data;

					if (successorParent == aux)
					{
						successorParent->Right = successor->Right;
						successor->Right = nullptr;
						delete successor;
					}
					else
					{
						successorParent->Left = successor->Right;
						successor->Right = nullptr;
						delete successor;
					}

					aux->Data = tempData;

					return true;
				}
				else
				{
					Node<T>* toChange = nullptr;

					if (aux->Left != nullptr)
					{
						toChange = aux->Left;
						aux->Left = nullptr;
					}
					else
					{
						toChange = aux->Right;
						aux->Right = nullptr;
					}

					delete aux;

					if (parent == nullptr)
						root = toChange;
					else if (parent->Data > data)
						parent->Left = toChange;
					else
						parent->Right = toChange;

					return true;
				}
			}
			else if(aux->Data > data)
			{
				parent = aux;
				aux = aux->Left;
			}
			else
			{
				parent = aux;
				aux = aux->Right;
			}
		}

		return false;
	}

	void Inorder()
	{
		if (root != nullptr)
			root->Inorder();
	}

	void Preorder()
	{
		if (root != nullptr)
			root->Preorder();
	}

	void Postorder()
	{
		if (root != nullptr)
			root->Postorder();
	}

	void Nullify()
	{
		while (root != nullptr)
			Delete(root->Data);
	}

	bool Search(T data)
	{
		if (!IsEmpty())
		{
			Node<T>* aux = root;
			while (aux != nullptr)
			{
				if (aux->Data == data)
					return true;
				if (data < aux->Data)
					aux = aux->Left;
				else
					aux = aux->Right;
			}
		}

		return false;
	}
};

int main()
{
	BinaryTree<int> binary;
	binary.Insert(10);
	binary.Insert(5);
	binary.Insert(2);
	binary.Insert(7);
	binary.Insert(6);
	binary.Insert(9);
	binary.Insert(8);
	binary.Insert(11);
	binary.Insert(12);
	int opc;
	do
	{
		cout << " Seleccione una opcion:\n\n 1.- Vacia\n 2.- Insertar\n 3.- Eliminar\n 4.- Imprimir En Order\n 5.- Imprimir Preorden\n 6.- Imprimir Postorden \n"
			<< " 7.- Buscar\n 8.- Anular\n 9.- Salir\n\n > ";
		cin >> opc;
		switch (opc)
		{
		case 1:
			cout << (binary.IsEmpty() ? "El arbol esta vacio" : "El arbol tiene datos") << endl;
			system("pause");
			break;
		case 2:
		{
			int c;
			cout << "Escribe el numero\n";
			cin >> c;
			binary.Insert(c);
			cout << "Se agrego el numero\n";
			system("pause");
			break;
		}
		case 3:
		{
			int c;
			cout << "Escribe el numero\n";
			cin >> c;
			cout << (binary.Delete(c) ? "Se elimino el numero" : "No se encontro el numero a eliminar") << endl;
			system("pause");
			break;
		}
		case 4:
			if (!binary.IsEmpty())
				binary.Inorder();
			else
				cout << "El arbol esta vacio";
			cout << endl;
			system("pause");
			break;
		case 5:
			if (!binary.IsEmpty())
				binary.Preorder();
			else
			cout << "El arbol esta vacio";
			cout << endl;
			system("pause");
			break;
		case 6:
			if (!binary.IsEmpty())
				binary.Postorder();
			else
			cout << "El arbol esta vacio";
			cout << endl;
			system("pause");
			break;
		case 7:
		{
			int c;
			cout << "Escribe el numero\n";
			cin >> c;
			cout << (binary.Search(c) ? "Se encontro el numero" : "No se encontro el numero") << endl;
			system("pause");
			break;
		}
		case 8:
			if (!binary.IsEmpty())
			{
				binary.Nullify();
				cout << "El arbol fue eliminado" << endl;
			}
			else
				cout << "El arbol ya esta vacio" << endl;
			system("pause");
			break;
		case 9:
			return 0;
		default:
			cout << "No se encuentra la opción" << endl;
			break;
		}
	} while (opc != 9);
	return 0;
	system("pause");
	return 0;
}