// Неустроева Ирина НБИ-02-23
#include <iostream>
using namespace std;

class matr; // прототип, чтобы можно было объявить в векторе метод с аргументами матрица и вектор 

class vect {
private:
  int dim; // размерность 
  double *b; // массив дина-ий 
  int num; // номер объекта
  static int count; // количество объектов 

public:
  vect(int d) : dim(d), num(++count) { // конструктор принимает параметр d
    b = new double[dim]; // создание b как динамический массив с размером dim 
    for (int i = 0; i < dim; ++i) { // заполнение массива 0
      b[i] = 0;
    }
    cout << "Конструктор вектора: объект №" << num << endl; // номер объекта 
  }

  vect(int d, const double *arr) : dim(d), num(++count) { // конструктор два параметра: d (размерность) и arr (указатель на массив)
    b = new double[dim];  // создание дина-го массив размером dim 
    for (int i = 0; i < dim; ++i) {
      b[i] = arr[i]; // копирование в него значения из arr
    }
    cout << "Конструктор вектора с массивом: объект №" << num << endl; // номер объекта.  
  }

  ~vect() {
    delete[] b;
    cout << "Деструктор вектора: объект №" << num << endl;
    --count;
  }

  vect(const vect &v) : dim(v.dim), num(++count) { // конструктор копирования, в аргументе другой вектор и создает его копию. Увеличивает count.
    b = new double[dim]; // создает массив такого же размера, как у исходного вектора и копирует значения из него. 
    for (int i = 0; i < dim; ++i) {
      b[i] = v.b[i];
    }
    cout << "Конструктор копирования вектора: объект №" << num << endl; // Увеличивает count для уникального номера.
  }

  void print() const { // метод не изменяет состояние вектора (const)
    cout << "Вектор объект №" << num << ": [ ";
    for (int i = 0; i < dim; ++i) { 
      cout << b[i] << " "; // вывод на экран содержимое вектора (номер объекта, все элементы массива b) 
    }
    cout << "]" << endl;
  }

  // Операторы
  friend vect operator+(const vect &v1, const vect &v2); // v + v
  friend vect operator-(const vect &v1, const vect &v2); // v - v
  vect operator-() const; //  -v 
  friend double operator*(const vect &v1, const vect &v2); //  v * v 
  friend vect operator*(double k, const vect &v); // k * v
  vect &operator=(const vect &v); // v = v 

  friend vect operator*(const matr &m, const vect &v); // m * v 

  static int getCount() { return count; } //  Статический метод для получения количества объектов
};

vect operator+(const vect &v1, const vect &v2) { // v +  v 
  if (v1.dim != v2.dim) {
    cout << "Размерности векторов не совпадают!" << endl;
    exit(1);
  }
  vect sum(v1.dim); // создание нового вектора 
  for (int i = 0; i < v1.dim; ++i) {
    sum.b[i] = v1.b[i] + v2.b[i]; 
  }
  return sum; 
}

vect operator-(const vect &v1, const vect &v2) { // v - v 
  if (v1.dim != v2.dim) {
    cout << "Размерности векторов не совпадают!" << endl;
    exit(1);
  }
  vect diff(v1.dim); // создание нового вектора 
  for (int i = 0; i < v1.dim; ++i) { 
    diff.b[i] = v1.b[i] - v2.b[i];
  }
  return diff;
}

vect vect::operator-() const {  // -v ( смена знака) 
  vect neg(dim); // создание нового вектора 
  for (int i = 0; i < dim; ++i) {
    neg.b[i] = -b[i]; // смена знака 
  }
  return neg;
}

double operator*(const vect &v1, const vect &v2) { // v * v (скалярное) 
  if (v1.dim != v2.dim) {
    cout << "Размерности векторов не совпадают!" << endl;
    exit(1);
  }
  double product = 0.0;
  for (int i = 0; i < v1.dim; ++i) {
    product += v1.b[i] * v2.b[i]; // умножаем и суммируем результат 
  }
  return product;
}

vect operator*(double k, const vect &v) { // v * k 
  vect scaled(v.dim); // создаем новый вектор scaled той же размерности, что и входной вектор v
  for (int i = 0; i < v.dim; ++i) {
    scaled.b[i] = k * v.b[i]; // создание нового вектора 
  }
  return scaled;
}

vect &vect::operator=(const vect &v) { // v = v 
  if (this == &v) { // проверка на равенство v = v?
    return *this; // возвращает вектор 
  }
  if (dim != v.dim) { // проверка на размер
    cout << "Размерности векторов не совпадают!" << endl;
    exit(1);
  }
  for (int i = 0; i < dim; ++i) {
    b[i] = v.b[i]; // v1 = v2  
  }
  return *this; // сыллка на измененный вектор 
}

int vect::count = 0; 

class matr {
private:
  int dim1, dim2; // размерность 
  double **b; // двумерный динамический массив
  int num; // номер объекта
  static int count; // количество объектов класса

public:
  matr(int d1, int d2) : dim1(d1), dim2(d2), num(++count) { // конструктор принимает два параметра для установки значений полей dim 
    b = new double *[dim1]; // создание и заполнение массива 0, увеличение num 
    for (int i = 0; i < dim1; ++i) {
      b[i] = new double[dim2];
      for (int j = 0; j < dim2; ++j) {
        b[i][j] = 0; 
      }
    }
    cout << "Конструктор матрицы: объект №" << num << endl;
  }

  matr(int d1, int d2, double **array) : dim1(d1), dim2(d2), num(++count) { // принимает аргументы d1, d2 и массив array размером d1xd2
    b = new double *[dim1]; // создаем такого же размера массив и заполняет его значениями из массива array
    for (int i = 0; i < dim1; ++i) { 
      b[i] = new double[dim2];
      for (int j = 0; j < dim2; ++j) {
        b[i][j] = array[i][j];
      }
    }
    cout << "Конструктор матрицы с массивом: объект №" << num << endl;
  }

  ~matr() {
    for (int i = 0; i < dim1; ++i) {
      delete[] b[i];
    }
    delete[] b;
    cout << "Деструктор матрицы: объект №" << num << endl;
    --count;
  }

  void print() const {  // метод не изменяет состояние матрицы
    cout << "Матрица объект №" << num << ":" << endl;
    for (int i = 0; i < dim1; ++i) {
      for (int j = 0; j < dim2; ++j) {
        cout << b[i][j] << " "; // вывод на экран содержимое матрицы( номер объекта, элементы массива) 
      }
      cout << endl;
    }
  }

  // Операторы
  friend matr operator+(const matr &m1, const matr &m2); // m + m
  friend matr operator-(const matr &m1, const matr &m2); // m - m
  matr operator-() const; // -m
  friend matr operator*(const matr &m1, const matr &m2); // m * m
  friend matr operator*(double k, const matr &m); // m * k
  matr &operator=(const matr &m); // m = m
  friend vect operator*(const matr &m, const vect &v); // m * v
  static int getCount() { return count; }
};

int matr::count = 0;

matr operator+(const matr &m1, const matr &m2) { // m + m
  if (m1.dim1 != m2.dim1 || m1.dim2 != m2.dim2) { // проверка на размерность
    cout << "Размерности матриц не совпадают для сложения." << endl;
    exit(1);
  }

  matr result(m1.dim1, m1.dim2);
  for (int i = 0; i < m1.dim1; ++i) {
    for (int j = 0; j < m1.dim2; ++j) {
      result.b[i][j] = m1.b[i][j] + m2.b[i][j]; // создание новой матрицы 
    }
  }

  return result;
}

matr operator-(const matr &m1, const matr &m2) { // m - m
  if (m1.dim1 != m2.dim1 || m1.dim2 != m2.dim2) { // проверка на равенство
    cout << "Размерности матриц не совпадают для вычитания." << endl;
    exit(1);
  }

  matr result(m1.dim1, m1.dim2); // создание новой матрицы
  for (int i = 0; i < m1.dim1; ++i) {
    for (int j = 0; j < m1.dim2; ++j) {
      result.b[i][j] = m1.b[i][j] - m2.b[i][j];
    }
  }

  return result;
}

matr matr::operator-() const { // -m 
  matr result(dim1, dim2); // новая матрица 
  for (int i = 0; i < dim1; ++i) {
    for (int j = 0; j < dim2; ++j) {
      result.b[i][j] = -b[i][j]; // смена знака 
    }
  }

  return result;
}

matr operator*(const matr &m1, const matr &m2) { // m * m 
  if (m1.dim2 != m2.dim1) {
    cout << "Размерности матриц не совпадают для умножения." << endl;
    exit(1);
  }

  matr result(m1.dim1, m2.dim2);
  for (int i = 0; i < result.dim1; ++i) { // проходит по всем элементам первой матрицы и для каждого элемента находит строки и столбца во второй матрице. произведение суммируется
    for (int j = 0; j < result.dim2; ++j) { 
      for (int k = 0; k < m1.dim2; ++k) { 
        result.b[i][j] += m1.b[i][k] * m2.b[k][j]; // создание матрицы. Произведение суммируется.
      }
    }
  }

  return result;
}

matr operator*(double k, const matr &m) { // m * k. Оператор принимает k и const матрицу
  matr result(m.dim1, m.dim2); // создание матрицы 
  for (int i = 0; i < m.dim1; ++i) {
    for (int j = 0; j < m.dim2; ++j) {
      result.b[i][j] = k * m.b[i][j]; // умножение каждого элемента на скаляр k
    }
  }

  return result;
}

matr &matr::operator=(const matr &m) { // m = m копируем содержимое одной матрицы в другую
  if (this != &m) { // проверка на равенство m = m?
    for (int i = 0; i < dim1; ++i) { // очищаем старую матрицу 
      delete[] b[i];
    }
    delete[] b;

    dim1 = m.dim1;
    dim2 = m.dim2;
    b = new double *[dim1]; // создание новой матрицы с таким же размером 
    for (int i = 0; i < dim1; ++i) {
      b[i] = new double[dim2];
      for (int j = 0; j < dim2; ++j) {
        b[i][j] = m.b[i][j]; // копирование данных из исходной матрицы
      }
    }
  }

  return *this; // сыллка на новую матрицу
}

vect operator*(const matr &m, const vect &v) { // m * v
  if (m.dim2 != v.dim) { // проверка на размер 
    cout << "Размерность матрицы и вектора не совпадают для умножения." << endl;
    exit(1);
  }

  vect result(m.dim1); 
  for (int i = 0; i < m.dim1; ++i) {
    for (int j = 0; j < m.dim2; ++j) {
      result.b[i] += m.b[i][j] * v.b[j]; // умнажение матрицы на вектор 
    }
  }

  return result;
}

int main() {
  vect v1(3);
  v1.print();
  cout << endl;

  double arr[] = {1.0, 2.0, 3.0};
  vect v2(3, arr);
  v2.print();
  cout << endl;

  vect v3 = v2;
  v3.print();
  cout << endl;

  vect v4 = v1 + v2;
  cout << "Сложение v1 и v2: " << endl;
  v4.print();
  cout << endl;

  vect v5 = v2 - v1;
  cout << "Вычитание v2 и v1: " << endl;
  v5.print();
  cout << endl;

  cout << "Умножение v2 на скаляр: " << endl;
  vect v6 = 2.0 * v2;
  v6.print();
  cout << endl;

  cout << "Унарный минус v2: " << endl;
  vect v7 = -v2;
  v7.print();
  cout << endl;

  double dotProduct = v2 * v3;
  cout << "Скалярное произведение v2 и v3: " << dotProduct << endl;
  cout << endl;

  cout << "Количество существующих векторов: " << vect::getCount() << endl;

  matr m1(3, 3);
  m1.print();
  cout << endl;

  double arr2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double *pArr[3] = {arr2[0], arr2[1], arr2[2]};
  matr m2(3, 3, pArr);
  m2.print();
  cout << endl;

  cout << "Сложение m1 и m2: " << endl;
  matr m3 = m1 + m2;
  m3.print();
  cout << endl;

  cout << "Вычитание m1 и m2: " << endl;
  matr m4 = m1 - m2;
  m4.print();
  cout << endl;

  cout << "Умножение m2 на скаляр: " << endl;
  matr m5 = 2.0 * m2;
  m5.print();
  cout << endl;

  cout << "Умножение m2 на m5: " << endl;
  matr m6 = m2 * m5;
  m6.print();
  cout << endl;

  cout << "Унарный минус m2: " << endl;
  matr m7 = -m2;
  m7.print();
  cout << endl;
  
  cout << "Умножение m6 на v2: " << endl;
  vect vm = m6 * v2;
  vm.print();
  
  cout << "Количество созданных матриц: " << matr::getCount() << endl;

  return 0;
}