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

void login();
void loadFromFile();
void saveToFile();
void addRecord();
void viewRecords();
void updateRecord();
void deleteRecord();
void summary();
void menu();
bool returnToMenu();

void login()
{
    string username, password;
    const string correctUser = "SmartSaver";
    const string correctPass = "12345";
    system("cls");
    cout << "===============================================\n";
    cout << "               WELCOME TO MoneyMap             \n";
    cout << "===============================================\n\n";
    do
    {
        cout << "Enter Username: ";
        getline(cin, username);

        cout << "Enter Password: ";
        getline(cin, password);
        if (username != correctUser || password != correctPass)
        {
            cout << "\n-- Invalid credentials! Please try again. --\n\n";
        }
    } while (username != correctUser || password != correctPass);
    cout << "\n------------------------------------------------\n";
    cout << "--------------- Login Successful!---------------\n";
    cout << "------------- Welcome, " << username << "! -------------\n";
    cout << "-- Manage your finances smartly with MoneyMap --\n";
    cout << "\n================================================\n\n";
    system("pause");
}

bool returnToMenu() {
    char choice;
    cout<<"\n=== Do you want to return to menu? (y/n): ";
    cin>>choice;
    if (choice == 'y' || choice == 'Y')
    {return true;
	} else
    return false;
}

void loadFromFile() 
{
    ifstream file(fileName.c_str()); // --> old compiler c_str converts string into const char
    if (!file) {
        return;  }
    record_count=0;
    while (record_count<MAX_RECORDS && file>>records[record_count].id) {
        file.ignore();
        getline(file, records[record_count].type);
        getline(file, records[record_count].category);
        getline(file, records[record_count].title);
        getline(file, records[record_count].priority);
        file>>records[record_count].amount;
        file.ignore();
        getline(file, records[record_count].date);
        record_count++; 
		}
    file.close(); 
}

void saveToFile()
{
    ofstream file(fileName.c_str());
    for (int i = 0; i < record_count; i++) {
        file<<records[i].id<<endl;
        file<<records[i].type<<endl;
        file<<records[i].category<<endl;
        file<<records[i].title<<endl;
        file<<records[i].priority<<endl;
        file<<records[i].amount<<endl;
        file<<records[i].date<<endl; 
		}
    file.close(); 
}

void addRecord() {
	system("cls");
    if (record_count>=MAX_RECORDS) {
        cout<<"\n== Record limit reached! ==\n" << endl;
        return; }
    cout<<"========== ADD NEW RECORD ==========\n\n";
    Expense e;
    e.id= record_count+1;
    cout<< "== Enter Type (Income/Expense): ";
    cin>> e.type;
    cout<< "== Enter Category: ";
    cin.ignore();
    getline(cin, e.category);
    cout<< "== Enter Title: ";
    getline (cin, e.title);
    cout << "== Enter Priority (High/Medium/Low): ";
    cin >> e.priority;
    do {
    cout << "== Enter Amount: ";
    cin >> e.amount;
    if (e.amount <= 0)
        cout << "Invalid amount! Try again.\n";
} while (e.amount <= 0);
    cout << "== Enter Date (dd-mm-yyyy): ";
    cin.ignore();
    getline(cin, e.date);
    records[record_count]=e;
    record_count++;
    saveToFile();
    cout<<"\n---Record added successfully!---" << endl;
    if (e.priority=="High" || e.priority=="high" || e.priority =="1" ) {
    cout<<"\n--High priority expense added!--"<<endl;
	} else if (e.priority=="Medium" || e.priority=="medium" || e.priority =="2" ) {
    cout<<"\n--Medium priority expense added!--"<<endl;
	} else if 
	(e.priority=="Low" || e.priority=="low" || e.priority =="3" ) {
	cout<<"\n--Low priority expense added!--"<<endl; 
   } else 
   {
   cout<<"\n-- No priority added! --\n";}
}
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