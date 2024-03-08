// ���������� �����, ���-02-23
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class List
{
public:
	List();
	~List();
	void pop_front(); // ����� ������� ������ ������� 
	void push_back(T data);// ����� �������� � ����� 
	void clear(); // �������� ���� ��������� 
	int GetSize() { return size; } // ����� ���-�� ���������.
	T& operator[](const int index);// ����� ����� �� �������, index( ����� ��������)
	void push_front(T data); // ����� �������� � ������ 
	void insert(T data, int index);// ����� �������� �� �������
	void remove(int index); // ����� ������� �� �������.
	void pop_back(); // ����� ������� ���������.

private:
    template<typename T> // ��������� ����� ��� ������ ����� ������
	class Node // �������� ������ Node, ������ ������ 
	{
	public:
		Node* pNext; // ��������� �� ����-�� ������� 
		T data; // ������ 

		Node(T data = T(), Node* pNext = nullptr) // �����������, �������� ������, ������������ ���� ��������� ��������� �������. 
		{
			this->data = data; // ����������� �������� ���������
			this->pNext = pNext;
		}
	};
	int size; // ���������� size ���������� ���������. 
	Node<T> *head;// ������ node, ��������� �� ������ ������� � ������.
};


template<typename T>
List<T>::List() // ����������� 
{
	size = 0; 
	head = nullptr;
}


template<typename T>
List<T>::~List() // ���������� 
{
	clear(); // �������� ����� clear.
}


template<typename T>
void List<T>::pop_front() // ����� �������� ������� �������� 
{
	Node<T> *prov = head; // ������ ���� prov, ������ ����� head.

	head = head->pNext; // � head ����������� ����� ���������� ��������.

	delete prov; // �������� prov(�������� ������� ��������)

	size--; // ���������� ���������� ���������.

}

template<typename T>
void List<T>::push_back(T data) // ����� �������� � �����.
{
	if (head == nullptr) // ���� � ������ �����, �� ��������� �� nullptr.
	{
		head = new Node<T>(data); // ������� ����� ������� Node � �������� � ����������� ������.
	}
	else
	{
		Node<T> *moment = this->head; // ������������ �������� ��������� � moment.
		// ���� �� ���� ����� � ���� ����� ���������.
		while (moment->pNext != nullptr) // ���� ��������� �� ����� nullptr
		{
			moment = moment->pNext; // ���� moment ����������� ��������� �� ��������� �������
		}
		moment->pNext = new Node<T>(data); // ������� ����� ������� � �����

	}

	size++; // ���������� ���������� ���������.
}

template<typename T> 
void List<T>::clear() // �������� ���� ���������
{
	while (size) // ���� � ������ ���� ������� 
	{
		pop_front(); // ������� ����� pop_front
	}
}


template<typename T>
T& List<T>::operator[](const int index) // ����� ����� �� �������. 
{
	int counter = 0; // ��������� ���������� � ������� ��������.

	Node<T>* moment = this->head; // ��������� �� ������� ������� = head.

	while (moment != nullptr)  
	{
		if (counter == index) // ���� ������� = ������� ������ ����� ������ �������
		{
			return moment->data; // ��������� ������� 
		}
		moment = moment->pNext;// ����������� ������ ����-�� ��������.
		counter++; // ���������� ��������.
	}
}

template<typename T>
void List<T>::push_front(T data) // ����� �������� � ������  
{
	head = new Node<T>(data, head); // ��� ��������� head = ��������� ����� ��������( ���������, ��������� �� head)
	size++;// ����������� ���-�� ��������� 
}

template<typename T>
void List<T>::insert(T data, int index) // ����� �������� �� �������
{

	if (index == 0) // ���� ����� �������� �� 0 �������
	{
		push_front(data); // ���������� ����� ���������� � ������ 
	}
	else
	{
		Node<T> *early = this->head; // ��������� ����������� �������� head 

		for (int i = 0; i < index - 1; i++) // ���� ������� ������� � �������� �������������� �� ����� �������� ����� ���������
		{
			early = early->pNext; // early = ����� �������� 
		}

		Node<T> *newNode = new Node<T>(data, early->pNext);// ������� ����� ������

		early->pNext = newNode; // � ���� ����������� �������, ������������ ������ ��������, ��������� ����� ������ �������.

		size++;
	}

}

template<typename T>
void List<T>::remove(int index) // ����� ������� �� �������
{
	if (index == 0) // ���� ������ = 0
	{
		pop_front(); // ���������� ����� ������� ������ �������
	}
	else
	{
		Node<T>* early = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			early = early->pNext;
		}


		Node<T> *toDelete = early->pNext; // � toDel ������ ����� ������� ��-�� �� ������� �������� ���������� �������

		early->pNext = toDelete->pNext; 

		delete toDelete; // ������� �������

		size--; // ��������� ���-�� ���������
	}

}

template<typename T>
void List<T>::pop_back()// ����� �������� ����������
{
	remove(size - 1); // �������� ����� �������� �� ������� � ������� ( size - 1 ) �������
}


int main()
{
	setlocale(LC_ALL, "ru");
	List<int> lst;
	int data, index, choice, size;

    cout << "������� ���������� ��������� � ������: ";
	cin >> size;
	cout << "������� �������� ������:\n";
	for (int i = 0; i < size; i++) 
	{
	cin >> data;
	
	lst.push_back(data);
    }
	do {
		cout << "\n�������� ��������:\n";
		cout << "1. �������� ������� � ������\n";
		cout << "2. �������� ������� �� �������\n";
		cout << "3. �������� ������� � �����\n";
		cout << "4. ������� ������ �������\n";
		cout << "5. ������� ��������� �������\n";
		cout << "6. ������� ������� �� �������\n";
		cout << "7. ����� ������� �� �������\n";
		cout << "8. ������� ������\n";
		cout << "0. �����\n";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "������� �������: ";
			cin >> data;
			lst.push_front(data);
			break;
		case 2:
			cout << "������� ������ � �������: ";
			cin >> data >> index;
			lst.insert(data, index);
			break;
		case 3:
			cout << "������� �������: ";
			cin >> data;
			lst.push_back(data);
			break;
		case 4:
			lst.pop_front();
			break;
		case 5:
			lst.pop_back();
			break;
		case 6:
			cout << "������� ������: ";
			cin >> index;
			lst.remove(index);
			break;
		case 7:
			cout << "������� ������: ";
			cin >> index;
			cout << "������� �� ������� " << index << ": " << lst [index] << endl;
			break;
		case 8:
			for (int i = 0; i < lst.GetSize(); i++)
				{
					cout << lst[i] << endl;
				}
			break;
		}

	} while (choice != 0);

	return 0;
}


	// ����� ���������� � �����.
//lst.push_back(5);

	// ����� ����� �� �������. 
// cout << lst [2];

	// ����� �������� ������� �������� 
//for (int i = 0; i < lst.GetSize(); i++) 
//{
//	cout << lst[i] << endl;
//}
//cout << "�������� pop_front" << endl;
//lst.pop_front();

//for (int i = 0; i < lst.GetSize(); i++)
//{
//	cout << lst[i] << endl;
//}
//cout << endl << "��������� � ������" << endl<< lst.GetSize() << endl;

     //����� ���������� � ������
//lst.push_front(8);
//lst.push_front(7);
//for (int i = 0; i < lst.GetSize(); i++) 
//{
//	cout << lst[i] << endl;
//}
	
    // ����� ���������� �� �������
	//lst.push_back(64);
	//lst.push_back(54);

//for (int i = 0; i < lst.GetSize(); i++) 
//{
//	cout << lst[i] << endl;
//}
//lst.insert(34, 1);

//cout << "insert" << endl;

//for (int i = 0; i < lst.GetSize(); i++)
//{
//	cout << lst[i] << endl;
//}

  // ����� �������� �� �������
//lst.push_back(64);
//lst.push_back(54);
//lst.push_back(90);

	//for (int i = 0; i < lst.GetSize(); i++)
	//{
	//	cout << lst[i] << endl;
	//}
//lst.remove(1);

//cout << "remove" << endl;

//for (int i = 0; i < lst.GetSize(); i++)
//{
//	cout << lst[i] << endl;
//}