// Неустроева Ирина, НБИ-02-23
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class List
{
public:
	List();
	~List();
	void pop_front(); // метод удалить первый элемент 
	void push_back(T data);// метод добавить в конец 
	void clear(); // удаление всех элементов 
	int GetSize() { return size; } // метод кол-во элементов.
	T& operator[](const int index);// метод найти по индексу, index( номер элемента)
	void push_front(T data); // метод добавить в начало 
	void insert(T data, int index);// метод добавить по индексу
	void remove(int index); // метод удалить по индексу.
	void pop_back(); // метод удалить последний.

private:
    template<typename T> // шаблонный класс для разных типов данных
	class Node // создание класса Node, хранит данные 
	{
	public:
		Node* pNext; // указатель на след-ий элемент 
		T data; // данные 

		Node(T data = T(), Node* pNext = nullptr) // конструктор, передаем данные, контролируем куда указывает последний элемент. 
		{
			this->data = data; // присваеваем входящие параметры
			this->pNext = pNext;
		}
	};
	int size; // переменная size количество элементов. 
	Node<T> *head;// объект node, указатель на превый элемент в списке.
};


template<typename T>
List<T>::List() // конструктор 
{
	size = 0; 
	head = nullptr;
}


template<typename T>
List<T>::~List() // деструктор 
{
	clear(); // вызываем метод clear.
}


template<typename T>
void List<T>::pop_front() // метод удаление первого элемента 
{
	Node<T> *prov = head; // объект типа prov, хранит адрес head.

	head = head->pNext; // к head присваеваем адрес следуещего элемента.

	delete prov; // удаление prov(удаление первого элемента)

	size--; // уменьшение количества элементов.

}

template<typename T>
void List<T>::push_back(T data) // Метод добавить в конец.
{
	if (head == nullptr) // если в списке пусто, то указатель на nullptr.
	{
		head = new Node<T>(data); // создаем новый элемент Node и передаем в конструктор данные.
	}
	else
	{
		Node<T> *moment = this->head; // присваиваеем значение звголовка к moment.
		// идем по всем нодам и ищем самую последнюю.
		while (moment->pNext != nullptr) // пока указатель не равен nullptr
		{
			moment = moment->pNext; // полю moment присваеваем указатель на следующий элемент
		}
		moment->pNext = new Node<T>(data); // создаем новый элемент в конец

	}

	size++; // увеличение количества элементов.
}

template<typename T> 
void List<T>::clear() // удаление всех элементов
{
	while (size) // пока в списке есть элемент 
	{
		pop_front(); // выполни метод pop_front
	}
}


template<typename T>
T& List<T>::operator[](const int index) // Метод поиск по индексу. 
{
	int counter = 0; // находимся изначально в нулевом элементе.

	Node<T>* moment = this->head; // указатель на текущий элемент = head.

	while (moment != nullptr)  
	{
		if (counter == index) // если счетчик = индексу значит нашли нужный элемент
		{
			return moment->data; // возвращай элемент 
		}
		moment = moment->pNext;// присваеваем адресс след-го элемента.
		counter++; // увеличение счетчика.
	}
}

template<typename T>
void List<T>::push_front(T data) // метод добавить в начало  
{
	head = new Node<T>(data, head); // для указателя head = добавляем новый элементь( параметры, указатель на head)
	size++;// увеличиваем кол-во элементов 
}

template<typename T>
void List<T>::insert(T data, int index) // метод добавить по индексу
{

	if (index == 0) // если хотим добавить на 0 элемент
	{
		push_front(data); // используем метод добавление в начало 
	}
	else
	{
		Node<T> *early = this->head; // указателю присваеваем значение head 

		for (int i = 0; i < index - 1; i++) // цикл находим элемент с индексом предшестуещему на место которого хотим поставить
		{
			early = early->pNext; // early = адрес элемента 
		}

		Node<T> *newNode = new Node<T>(data, early->pNext);// создаем новый объект

		early->pNext = newNode; // в поле предыдущего объекта, относительно нового элемента, добавляем адрес нового объекта.

		size++;
	}

}

template<typename T>
void List<T>::remove(int index) // метод удалить по индексу
{
	if (index == 0) // если индекс = 0
	{
		pop_front(); // используем метод удалить первый элемент
	}
	else
	{
		Node<T>* early = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			early = early->pNext;
		}


		Node<T> *toDelete = early->pNext; // в toDel храним адрес старого эл-та на который указывал предыдущий элемент

		early->pNext = toDelete->pNext; 

		delete toDelete; // удаляем элемент

		size--; // уменьшаем кол-во элементов
	}

}

template<typename T>
void List<T>::pop_back()// метод удаление последнего
{
	remove(size - 1); // высываем метод удаление по индексу и удаляем ( size - 1 ) элемент
}


int main()
{
	setlocale(LC_ALL, "ru");
	List<int> lst;
	int data, index, choice, size;

    cout << "Введите количество элементов в списке: ";
	cin >> size;
	cout << "Введите элементы списка:\n";
	for (int i = 0; i < size; i++) 
	{
	cin >> data;
	
	lst.push_back(data);
    }
	do {
		cout << "\nВыберите действие:\n";
		cout << "1. Добавить элемент в начало\n";
		cout << "2. Добавить элемент по индексу\n";
		cout << "3. Добавить элемент в конец\n";
		cout << "4. Удалить первый элемент\n";
		cout << "5. Удалить последний элемент\n";
		cout << "6. Удалить элемент по индексу\n";
		cout << "7. Найти элемент по индексу\n";
		cout << "8. Вывести список\n";
		cout << "0. Выход\n";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Введите элемент: ";
			cin >> data;
			lst.push_front(data);
			break;
		case 2:
			cout << "Введите индекс и элемент: ";
			cin >> data >> index;
			lst.insert(data, index);
			break;
		case 3:
			cout << "Введите элемент: ";
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
			cout << "Введите индекс: ";
			cin >> index;
			lst.remove(index);
			break;
		case 7:
			cout << "Введите индекс: ";
			cin >> index;
			cout << "Элемент по индексу " << index << ": " << lst [index] << endl;
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


	// Метод добавление в конец.
//lst.push_back(5);

	// Метод найти по индексу. 
// cout << lst [2];

	// Метод удаление первого элемента 
//for (int i = 0; i < lst.GetSize(); i++) 
//{
//	cout << lst[i] << endl;
//}
//cout << "Выполняю pop_front" << endl;
//lst.pop_front();

//for (int i = 0; i < lst.GetSize(); i++)
//{
//	cout << lst[i] << endl;
//}
//cout << endl << "Элементов в списке" << endl<< lst.GetSize() << endl;

     //Метод добавление в начало
//lst.push_front(8);
//lst.push_front(7);
//for (int i = 0; i < lst.GetSize(); i++) 
//{
//	cout << lst[i] << endl;
//}
	
    // Метод добавление по индексу
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

  // Метод удаление по индексу
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
