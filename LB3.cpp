#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <iostream>
#include <vector>

class Point { // базоовый класс 
public:
    virtual void draw() const = 0; // изобразить
    virtual void remove() = 0; // убрать
    virtual void move(double dx, double dy) = 0; // перемещение на указанные значения
    virtual void rotate(double angle) = 0; // поворот на указанный угол.
    virtual ~Point() {}
};

class Shape : public Point { // Класс Shape произвольный класс от Point
protected:
    std::vector<std::pair<double, double>> vertices; //  защищенное поле vertices, векторы пар (x, y) координат вершин фигуры.

public:
    void draw() const override { // функция `draw()`выводит координаты вершин фигуры в консоль.
        std::cout << "Drawing a shape with vertices at:" << std::endl;
        for (const auto& vertex : vertices) { //  проходим по каждой паре координат вершин (x, y) в векторе vertices.
            std::cout << "(" << vertex.first << ", " << vertex.second << ")" // функция выводит координаты всех вершин фигуры в консоль.
                << std::endl;
        }
    }

    void remove() override { 
        std::cout << "Removing a shape." << std::endl;
        vertices.clear(); // метод удаляет все вершины из фигуры
    }

    void move(double dx, double dy) override { // перемещает все вершины фигуры на указанное смещение (dx, dy)
        for (auto& vertex : vertices) {
            vertex.first += dx;
            vertex.second += dy;
        }
    }

    void rotate(double angle) override { // переопределение метода rotate() для класса Shape. 
        // Вычисляем центр фигуры
        double centerX = 0.0;
        double centerY = 0.0;
        for (const auto& vertex : vertices) { 
            centerX += vertex.first; // суммирование координат всех вершин
            centerY += vertex.second; 
        }
        centerX /= vertices.size(); // деление на количество вершин. 
        centerY /= vertices.size(); 

        // Поворачиваем каждую точку относительно центра
        double angleRadian = angle * M_PI / 180; 
        for (auto& vertex : vertices) {
            double x = (vertex.first - centerX) * cos(angleRadian) -
                (vertex.second - centerY) * sin(angleRadian) + centerX;
            double y = (vertex.first - centerX) * sin(angleRadian) +
                (vertex.second - centerY) * cos(angleRadian) + centerY;
            vertex.first = x; // новые координаты присваиваются соответствующим вершинам.
            vertex.second = y;
        }
    }
};

class Line : public Shape { // определен класс Line, производным от класса Shape
public:
    Line(std::pair<double, double> start, std::pair<double, double> end) {
        vertices.push_back(start); // начальная точки линии
        vertices.push_back(end); // конечная точки линии 
    }

    void draw() const override { //  Метод draw() для класса Line переопределен для вывода сообщения о рисовании линии
        std::cout << "Drawing a line from (" << vertices[0].first << ", "  // координаты начальной и конечной точек 
            << vertices[0].second << ") to (" << vertices[1].first << ", "
            << vertices[1].second << ")." << std::endl;
    }
};

class Square : public Shape { //  определен класс Square, который является производным от класса Shape
protected:
    double sideLength; // защищенное поле sideLength, представляющее длину стороны квадрата.

public:
    Square(std::pair<double, double> topLeft, double length)
        : sideLength(length) { // координаты длины  
        vertices.push_back(topLeft); // задаются координаты верхнего левого угла квадрата
        vertices.push_back({ topLeft.first + length, topLeft.second }); // вычисляются координаты остальных вершин и добавляются в вектор вершин Square
        vertices.push_back({ topLeft.first + length, topLeft.second - length });
        vertices.push_back({ topLeft.first, topLeft.second - length });
    }

    void draw() const override { // Метод draw() для класса Square переопределен для вывода сообщения о рисовании квадрата
        std::cout << "Drawing a square with side length " << sideLength // с длиной стороны и координатами верхнего левого угла.
            << " and top left vertex at (" << vertices[0].first << ", " 
            << vertices[0].second << ")." << std::endl;
    }
};

class Parallelogram : public Shape {
protected: // защищенные поля sideA, sideB и angle, представляющие длины сторон и угол параллелограмма
    double sideA;
    double sideB;
    double angle;

public:
    Parallelogram(std::pair<double, double> vertex, double a, double b, 
        double ang) // координаты одной из вершин параллелограмма, длины сторон a и b, а также угол
        : sideA(a), sideB(b), angle(ang) { 
        vertices.push_back(vertex); // вычисляются координаты остальных вершин параллелограмма
        vertices.push_back({ vertex.first + sideA, vertex.second });
        vertices.push_back({ vertex.first + sideA - sideB * cos(angle * M_PI / 180),
                            vertex.second - sideB * sin(angle * M_PI / 180) });
        vertices.push_back({ vertex.first - sideB * cos(angle * M_PI / 180),
                            vertex.second - sideB * sin(angle * M_PI / 180) });
    }

    void draw() const override { // вывод сообщения о рисовании параллелограмма с координатами вершин. 
        std::cout << "Drawing a parallelogram with vertices:" << std::endl; // 
        for (const auto& vertex : vertices) {
            std::cout << "(" << vertex.first << ", " << vertex.second << ")"
                << std::endl;
        }
    }
};

class Rhombus : public Shape {
protected:
    double sideLength; // длину стороны 
    double angle;// угол ромба

public:
    Rhombus(std::pair<double, double> vertex, double length, double ang)
        : sideLength(length), angle(ang) { // координаты одной из вершин ромба, длина стороны и угол
        vertices.push_back(vertex); 
        vertices.push_back({ vertex.first + sideLength, vertex.second }); // добавляется первая вершина ромба с координатами vertex в вектор vertices
        vertices.push_back( // вычисление трех вершин ромба на основе длины стороны и угла, и они добавляются в вектор vertices.
            { vertex.first + sideLength - sideLength * cos(angle * M_PI / 180),
             vertex.second - sideLength * sin(angle * M_PI / 180) });
        vertices.push_back({ vertex.first - sideLength * cos(angle * M_PI / 180),
                            vertex.second - sideLength * sin(angle * M_PI / 180) });
    }

    void draw() const override {
        std::cout << "Drawing a rhombus with vertices:" << std::endl;
        for (const auto& vertex : vertices) {
            std::cout << "(" << vertex.first << ", " << vertex.second << ")"
                << std::endl;
        }
    }
};

class Rectangle : public Shape {
protected:
    double width;
    double height;

public:
    Rectangle(std::pair<double, double> topLeft, double w, double h)
        : width(w), height(h) { // ширина и высота прямоугольника 
        vertices.push_back(topLeft); 
        vertices.push_back({ topLeft.first + w, topLeft.second }); // задаются координаты верхнего левого угла прямоугольника, ширина и высота
        vertices.push_back({ topLeft.first + w, topLeft.second - h }); // вычисляются координаты остальных вершин
        vertices.push_back({ topLeft.first, topLeft.second - h }); //и добавляются в вектор вершин Rectangle 
    }

    void draw() const override { // метод для вывода сообщения о рисовании прямоугольника с указанием ширины, высоты и координат верхнего левого угла
        std::cout << "Drawing a rectangle with width " << width << ", height "
            << height << " and top left vertex at (" << vertices[0].first
            << ", " << vertices[0].second << ")." << std::endl;
    }
};

// Класс для квадрата, который также является параллелограммом
class SquareParallelogram : public Rectangle { // прямоугольник и параллелограмм, который является квадратом, если ширина и высота равны
public:
    SquareParallelogram(std::pair<double, double> topLeft, double sideLength) //  принимает координаты верхнего левого угла и длину стороны
        : Rectangle(topLeft, sideLength, sideLength) {} // вызывается конструктор базового класса Rectangle, чтобы задать параметры прямоугольника

    void draw() const override { // квадрат параллелограмм является частным случаем прямоугольника, где ширина и высота равны, что соответствует длине стороны квадрата.
        std::cout << "Drawing a square parallelogram with side length " << width
            << " and top left vertex at (" << vertices[0].first << ", "
            << vertices[0].second << ")." << std::endl;
    }
};

// Пример использования вращения
void rotateShape(Point& shape, double angle) {
    shape.rotate(angle);
}

int main() {
    Line line({ 0, 0 }, { 1, 1 });
    Square square({ 0, 0 }, 2);

    Parallelogram parallelogram({ 0, 0 }, 3, 2, 45);
    Rhombus rhombus({ 0, 0 }, 2, 60);

    line.draw();
    line.move(1, 1);
    line.draw();

    square.draw();
    square.move(2, 2);
    square.draw();

    parallelogram.draw();
    parallelogram.move(1, 1);
    parallelogram.draw();
    rotateShape(parallelogram, 30);
    parallelogram.draw();

    rhombus.draw();
    rhombus.move(2, 2);
    rhombus.draw();
    rotateShape(rhombus, -45);
    rhombus.draw();

    return 0;
}
