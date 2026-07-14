#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct Expense
{
    int id;
    string type, category, title, priority;
    float amount;
    string date;
};

int MAX_RECORDS = 50;
Expense *records = NULL;
int record_count = 0;
string fileName = "MyMoneyMap.txt";

bool login();
void loadFromFile();
void saveToFile();
void addRecord();
void viewRecords();
void updateRecord();
void deleteRecord();
void summary();
void menu();
bool returnToMenu();

void menu()
{
    system("cls");
    cout << "======== MoneyMap ========\n";
    cout << "-- 1. Add Record\n";
    cout << "-- 2. View Records\n";
    cout << "-- 3. Update Record\n";
    cout << "-- 4. Delete Record\n";
    cout << "-- 5. Summary\n";
    cout << "-- 0. Exit\n";
}

int main()
{
    records = new Expense[MAX_RECORDS]; // dynamic memory allocation
    login();
    loadFromFile();
    int choice;
    bool backToMenu = true;
    while (backToMenu)
    {
        menu();
        cout << "\n=== Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            viewRecords();
            break;
        case 3:
            updateRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            summary();
            break;
        case 0:
            saveToFile();
            cout << "\n----- Program Exited -----" << endl;
            return 0;
        default:
            cout << "-- Invalid choice! --" << endl;
        }
        backToMenu = returnToMenu();
    }
    cout << "\n----- Program Exited -----" << endl;
    delete[] records; // free dynamic memory
    return 0;
}