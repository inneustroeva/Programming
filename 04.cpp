#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct MovieSession { // ��������� MovieSession
    string id;
    string title;
    string time;
    string date;
    string hall;

    string to_string() { // ����� ���������� ������ � ����������� � ������ 

        return id + "|" + title + "|" + time + "|" + date + "|" + hall;
    }
};
// ������ � �������� ������ � ����������� �� ����� � ������ ��������. (��� �����, ��������� �� ������ �������� � ���-�� ������. 

void loadDatabase(const string& filename, MovieSession*& sessions, int& count) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return;
    }
 // ���������� ���� ����� �� ����� � ������� ��� ������ ������, ��� ����������� ������� �������
    count = 0; 
    string line; 
    while (getline(file, line)) {
        count++;
    }
    file.clear(); // ����������� ������ � �������� ��������� ��� ���������� ������
    file.seekg(0, ios::beg); // ��������� ������ � ������ �����.

// ��������� ������ ��� ������� � ������ ������ �� ����
    sessions = new MovieSession[count];  
    int index = 0; // ��������-�� ���������� ��� ���������� ��������� �������.
    while (getline(file, line)) { // ���� ������ ������ ������ �� �����.
        stringstream ss(line); // ��������� ������ ss ������ stringstream
        getline(ss, sessions[index].id, '|'); // �� ������ ss ����������� ���� id �� ������� |.��������� ������� �� ������ line ���-�� � ���� id �������� 
        getline(ss, sessions[index].title, '|');
        getline(ss, sessions[index].time, '|');
        getline(ss, sessions[index].date, '|');
        getline(ss, sessions[index].hall, '|');
        index++;
    }
    file.close(); // ���� ����������� 
}
// ������� saveDatabase ��� ���������� ������ � ����������� � ����
void saveDatabase(const string& filename, MovieSession* sessions, int count) {
    ofstream file(filename); //  ������ file ������ ofstream, ����� ����������� � ������, ��������� � ���������� filename.
    if (!file.is_open()) { // �������� �������� �����
        cerr << "Unable to open file" << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        file << sessions[i].to_string() << endl; // ������ ������ � ����. ���� �� ���� ��������� ������� � �������. 
    }
    file.close();
}
// ������� ��� ���������� ������ ���������� � ������������ ������ �������.
void addSession(MovieSession*& sessions, int& count) { // ������ �� ������� ������ � ���-�� ��������� 
    MovieSession* newSessions = new MovieSession[count + 1]; // ������ ��� ������ �������(������ ������ + ����� ������)

    for (int i = 0; i < count; i++) { // ����������� ������� ������� � �����
        newSessions[i] = sessions[i];
    }
// ���� ����� ������, ����������� � ��������� �������� �������.
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
    sessions = newSessions; // ���������� ��������� �� ����� ������ 
    count++; // ���������� ������ ������ 
}
// ��������� ������������ �������
void editSession(MovieSession* sessions, int count) { 
    string id;
    cout << "Enter session ID to edit: "; // ���� ID ������, ������� ����� ���������������
    cin >> id;

    for (int i = 0; i < count; i++) { // ����� ����� ������ � ����������� ID:
        if (sessions[i].id == id) {
            cout << "Enter new movie title: ";  // ���� ����� ������, ������ ����� ��������
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
    cout << "Session ID not found." << endl; // ������ ���� �� ������
}

// ������� deleteSession, ��� �������� ������ ���� �� ������� �������
void deleteSession(MovieSession*& sessions, int& count) { 
    string id;
    cout << "Enter session ID to delete: ";
    cin >> id; // ���� ID ������, ������� ����� �������

    int index = -1; 
    for (int i = 0; i < count; i++) {
        if (sessions[i].id == id) { // �������� �� ������� sessions ��� ������ ������� ������ � ����������� ID:
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Session ID not found." << endl; // ������ �� ������ ������ �� ��� ID
        return;
    }

    MovieSession* newSessions = new MovieSession[count - 1]; // ���� ������ �����, ������� ����� ������ newSessions �������� count - 1, �������� ��� ������ �� ������� sessions, ����� ���������� ������
    for (int i = 0, j = 0; i < count; i++) {
        if (i != index) {
            newSessions[j++] = sessions[i];
        }
    }

    delete[] sessions; //  ����������� ������, ��� ������ sessions 
    sessions = newSessions; // ������������ ����� ���������� ������� newSessions, ����������� ������� count
    count--;
}
// ������� searchSession ��� ������ ������ ���� �� ��� ID � ������� �������
void searchSession(const MovieSession* sessions, int count) {
    string id;
    cout << "Enter session ID to search: ";
    cin >> id; //  ������ ID ������, ������� ����� �����

    for (int i = 0; i < count; i++) {
        if (sessions[i].id == id) { // �������� �� ������� sessions ��� ������ ������ � ����������� ID
            cout << "ID: " << sessions[i].id << endl; //  ����� ������ � ������
            cout << "Title: " << sessions[i].title << endl;
            cout << "Time: " << sessions[i].time << endl;
            cout << "Date: " << sessions[i].date << endl;
            cout << "Hall: " << sessions[i].hall << endl;
            return;
        }
    }
    cout << "Session ID not found." << endl; // ������ �� ������ ������ �� ��� ID
}
// ������� printSessions ��� ������ ���������� � ���� ������� ���� � ������� �������� MovieSession
void printSessions(const MovieSession* sessions, int count) { // ��������� �� ������ sessions �������� MovieSession � ���������� ������� count 
    for (int i = 0; i < count; i++) {
        cout << "ID: " << sessions[i].id << endl; // ����� ���������� �� ������� 
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
    const string filename = "database.txt"; // �������� ������ � ������� �� ����� ���� ������
    loadDatabase(filename, sessions, count);

    while (true) { //  ����������� ���� ��� �������������� ������������ ��������� �����:
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
            addSession(sessions, count);  // ����� ������� �� ���������� ������ ������
            saveDatabase(filename, sessions, count); // ���������� ���������
            break;
        case 2:
            editSession(sessions, count); // �������������� ������
            saveDatabase(filename, sessions, count);
            break;
        case 3:
            deleteSession(sessions, count); // �������� ������
            saveDatabase(filename, sessions, count);
            break;
        case 4:
            searchSession(sessions, count); // ����� ������ 
            break;
        case 5:
            printSessions(sessions, count); // ����� ������� 
            break;
        case 6:
            delete[] sessions; // ����� �� ���������
            return 0;
        default:
            cout << "Invalid choice, try again." << endl; 
        }
    }
    return 0;
}
