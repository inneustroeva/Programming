#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct MovieSession { // структура MovieSession
    string id;
    string title;
    string time;
    string date;
    string hall;

    string to_string() { // метод возвращает строку с информацией о сеансе 

        return id + "|" + title + "|" + time + "|" + date + "|" + hall;
    }
};
// Чтение и загрузка данных о киносеансах из файла в массив структур. (Имя файла, указатель на массив структур и кол-во сессий. 

void loadDatabase(const string& filename, MovieSession*& sessions, int& count) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return;
    }
 // Считывание всех строк из файла и счетчик для каждой строки, для определения размера массива
    count = 0; 
    string line; 
    while (getline(file, line)) {
        count++;
    }
    file.clear(); // возвращение потока в исходное состояние для повторного чтения
    file.seekg(0, ios::beg); // указатель чтения в начало файла.

// Выделение памяти для массива и чтение данных из него
    sessions = new MovieSession[count];  
    int index = 0; // инициали-ия переменной для индексации элементов массива.
    while (getline(file, line)) { // цикл читает каждую строку из файла.
        stringstream ss(line); // создается объект ss класса stringstream
        getline(ss, sessions[index].id, '|'); // из потока ss считывается поле id до символа |.Считанные символы их строки line сох-ся в поле id структур 
        getline(ss, sessions[index].title, '|');
        getline(ss, sessions[index].time, '|');
        getline(ss, sessions[index].date, '|');
        getline(ss, sessions[index].hall, '|');
        index++;
    }
    file.close(); // файл закрывается 
}
// Функцию saveDatabase для сохранения данных о киносеансах в файл
void saveDatabase(const string& filename, MovieSession* sessions, int count) {
    ofstream file(filename); //  объект file класса ofstream, поток связывается с файлом, указанным в переменной filename.
    if (!file.is_open()) { // проверка открытия файла
        cerr << "Unable to open file" << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        file << sessions[i].to_string() << endl; // запись данных в файл. Цикл по всем элементам массива с методом. 
    }
    file.close();
}
// Функция для добавления нового киносеанса в существующий массив сеансов.
void addSession(MovieSession*& sessions, int& count) { // ссылка на полнный массив и кол-во элементов 
    MovieSession* newSessions = new MovieSession[count + 1]; // память для нового массива(старый массив + новые сеансы)

    for (int i = 0; i < count; i++) { // копирование старого массива в новый
        newSessions[i] = sessions[i];
    }
// Ввод новых данных, сохраняются в послнднем элементе массива.
    cout << "Enter session ID: ";
    cin >> newSessions[count].id;
    cout << "Enter movie title: ";
    cin.ignore();
    getline(cin, newSessions[count].title);
    cout << "Enter session time: ";
    getline(cin, newSessions[count].time);
    cout << "Enter session date: ";
    getline(cin, newSessions[count].date);
    cout << "Enter hall: ";
    getline(cin, newSessions[count].hall);

    delete[] sessions; 
    sessions = newSessions; // обнавление указателя на новый массив 
    count++; // добавление нового сеанса 
}
// Изменение существующих сеансов
void editSession(MovieSession* sessions, int count) { 
    string id;
    cout << "Enter session ID to edit: "; // ввод ID сеанса, который нужно отредактировать
    cin >> id;

    for (int i = 0; i < count; i++) { // Затем поиск сеанса с совпадающим ID:
        if (sessions[i].id == id) {
            cout << "Enter new movie title: ";  // Если сеанс найден, вводим новые значения
            cin.ignore();
            getline(cin, sessions[i].title);
            cout << "Enter new session time: ";
            getline(cin, sessions[i].time);
            cout << "Enter new session date: ";
            getline(cin, sessions[i].date);
            cout << "Enter new hall: ";
            getline(cin, sessions[i].hall);
            return;
        }
    }
    cout << "Session ID not found." << endl; // ошибка если не найден
}

// функцию deleteSession, для удаления сеанса кино из массива сеансов
void deleteSession(MovieSession*& sessions, int& count) { 
    string id;
    cout << "Enter session ID to delete: ";
    cin >> id; // ввод ID сеанса, который хотим удалить

    int index = -1; 
    for (int i = 0; i < count; i++) {
        if (sessions[i].id == id) { // итерация по массиву sessions для поиска индекса сеанса с совпадающим ID:
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Session ID not found." << endl; // ошибка по поиску сеанса по его ID
        return;
    }

    MovieSession* newSessions = new MovieSession[count - 1]; // Если найден сеанс, создаем новый массив newSessions размером count - 1, копируем все сеансы из массива sessions, кроме удаленного сеанса
    for (int i = 0, j = 0; i < count; i++) {
        if (i != index) {
            newSessions[j++] = sessions[i];
        }
    }

    delete[] sessions; //  освобождаем память, под массив sessions 
    sessions = newSessions; // запоминается адрес созданного массива newSessions, обновляется счетчик count
    count--;
}
// функцию searchSession для поиска сеанса кино по его ID в массиве сеансов
void searchSession(const MovieSession* sessions, int count) {
    string id;
    cout << "Enter session ID to search: ";
    cin >> id; //  вводим ID сеанса, который хотим найти

    for (int i = 0; i < count; i++) {
        if (sessions[i].id == id) { // итерация по массиву sessions для поиска сеанса с совпадающим ID
            cout << "ID: " << sessions[i].id << endl; //  вывод данных о сеансе
            cout << "Title: " << sessions[i].title << endl;
            cout << "Time: " << sessions[i].time << endl;
            cout << "Date: " << sessions[i].date << endl;
            cout << "Hall: " << sessions[i].hall << endl;
            return;
        }
    }
    cout << "Session ID not found." << endl; // ошибка по поиску сеанса по его ID
}
// функцию printSessions для вывода информации о всех сеансах кино в массиве структур MovieSession
void printSessions(const MovieSession* sessions, int count) { // указатель на массив sessions структур MovieSession и количество сеансов count 
    for (int i = 0; i < count; i++) {
        cout << "ID: " << sessions[i].id << endl; // вывод информации по сеансам 
        cout << "Title: " << sessions[i].title << endl;
        cout << "Time: " << sessions[i].time << endl;
        cout << "Date: " << sessions[i].date << endl;
        cout << "Hall: " << sessions[i].hall << endl;
        cout << "---------------------" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    MovieSession* sessions = nullptr;
    int count = 0;
    const string filename = "database.txt"; // загрузка данных о сеансах из файла базы данных
    loadDatabase(filename, sessions, count);

    while (true) { //  бесконечный цикл для предоставления пользователю различных опций:
        cout << "1. Add session" << endl;
        cout << "2. Edit session" << endl;
        cout << "3. Delete session" << endl;
        cout << "4. Search session" << endl;
        cout << "5. Print all sessions" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addSession(sessions, count);  // вызов функции по добавлению нового сеанса
            saveDatabase(filename, sessions, count); // сохранение изменений
            break;
        case 2:
            editSession(sessions, count); // редактирование сеанса
            saveDatabase(filename, sessions, count);
            break;
        case 3:
            deleteSession(sessions, count); // удаление сеанса
            saveDatabase(filename, sessions, count);
            break;
        case 4:
            searchSession(sessions, count); // поиск сеанса 
            break;
        case 5:
            printSessions(sessions, count); // вывод сеансов 
            break;
        case 6:
            delete[] sessions; // выход из программы
            return 0;
        default:
            cout << "Invalid choice, try again." << endl; 
        }
    }
    return 0;
}
