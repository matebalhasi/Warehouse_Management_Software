#include <iostream>
#include <conio.h>
#include <thread>
#include <fstream>
#include <sstream>
#include "PersonalData.h"

using namespace std;

// Press key to continue
void pressToContinue() {
#ifdef _WIN32
    _getch();
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

// Main menu
void showMainMenu() {
    cout << "Main Menu\n"
        << "-------------\n"
        << "Select which user you wish to use:\n"
        << " 1. Worker\n 2. Buyer\n 3. Supplier\n 4. Admin\n 5. Exit\n"
        << "\n Enter a choice (1-5): ";
}

// Submenus
void showWorkerMenu() {
    cout << "Worker Menu\n"
        << "-------------\n"
        << " 1. Personal Data\n 2. Storage\n 3. Items\n 4. Exit\n"
        << "\n Enter a choice (1-4): ";
}

void showBuyerMenu() {
    cout << "Buyer Menu\n"
        << "-------------\n"
        << " 1. Storage\n 2. Add Item\n 3. Write Complaint\n 4. Exit\n"
        << "\n Enter a choice (1-4): ";
}

void showSupplierMenu() {
    cout << "Supplier Menu\n"
        << "-------------\n"
        << " 1. Storage\n 2. Add Item\n 3. Write Complaint\n 4. Exit\n"
        << "\n Enter a choice (1-4): ";
}

void showAdminMenu() {
    cout << "Admin Menu\n"
        << "-------------\n"
        << " 1. Personal Data\n 2. Worker Data\n 3. Storage Data\n"
        << " 4. Complaints\n 5. Items\n 6. Exit\n"
        << "\n Enter a choice (1-6): ";
}

// Validate login credentials
bool loginValidation(const string& id, const string& password, char clearance_level) {
    ifstream users("users.txt");
    if (!users.is_open()) {
        cout << "Error! The file could not be opened!\n";
        return false;
    }

    string input, userID, userPassword;
    char user_clearance_level;
    while (getline(users, input)) {
        istringstream iss(input);
        iss >> userID >> userPassword >> user_clearance_level;

        if (userID == id && userPassword == password) {
            if (user_clearance_level == clearance_level || user_clearance_level == '4') {
                return true;
            }
            else {
                system("cls");
                cout << "Error! User clearance level does not match!\n\nPress any key to continue.";
                pressToContinue();
                return false;
            }
        }
    }

    system("cls");
    cout << "Error! User ID and/or password do not match!\n\nPress any key to continue.";
    pressToContinue();
    return false;
}


int main() {
    PersonalData personalData("worker_data.txt");
    char input;
    string id, password;

    showMainMenu();
    cin >> input;

    while (true) {
        system("cls");
        switch (input) {
            //worker Menu
        case '1': { 
            cout << "Enter userID: ";
            cin >> id;
            cout << "\nEnter Password: ";
            cin >> password;

            if (loginValidation(id, password, input)) {
                system("cls");
                showWorkerMenu();
                cin >> input;

                while (true) {
                    if (input == '1') { 
                        system("cls");
                        cout << "Fetching Personal Data";
                        for (int i = 0; i < 3; ++i) {
                            this_thread::sleep_for(chrono::milliseconds(500));
                            cout << ".";
                        }
                        system("cls");
                        cout << personalData.getWorkerInfo(id) << endl;
                        pressToContinue();
                        system("cls");
                        showWorkerMenu();
                        cin >> input;
                    }
                    else if (input == '4') { 
                        system("cls");
                        showMainMenu();
                        break;
                    }
                }
            }
            else {
                showMainMenu();
            }
            break;
        }
                //buyer Menu
        case '2': { 
            cout << "Enter userID: ";
            cin >> id;
            cout << "\nEnter Password: ";
            cin >> password;

            if (loginValidation(id, password, input)) {
                system("cls");
                showBuyerMenu();
                cin >> input;

                while (true) {
                    if (input == '4') {
                        system("cls");
                        showMainMenu();
                        break;
                    }
                }
            }
            else {
                showMainMenu();
            }
            break;
        }
                //supplier Menu
        case '3': {
            cout << "Enter userID: ";
            cin >> id;
            cout << "\nEnter Password: ";
            cin >> password;

            if (loginValidation(id, password, input)) {
                system("cls");
                showSupplierMenu();
                cin >> input;

                while (true) {
                    if (input == '4') {
                        system("cls");
                        showMainMenu();
                        break;
                    }
                }
            }
            else {
                showMainMenu();
            }
            break;
        }
                //admin Menu
        case '4': { 
            cout << "Enter userID: ";
            cin >> id;
            cout << "\nEnter Password: ";
            cin >> password;

            if (loginValidation(id, password, input)) {
                system("cls");
                showAdminMenu();
                cin >> input;

                while (true) {

                    
                   if(input== '1')
                   {
						system("cls");
                        cout << "Fetching Personal Data";
                        for (int i = 0; i < 3; ++i) {
                            this_thread::sleep_for(chrono::milliseconds(500));
                            cout << ".";
                        }
                        system("cls");
                        cout << personalData.getWorkerInfo(id) << endl;
                        pressToContinue();
                        system("cls");
                        showAdminMenu();
                        cin >> input;
                   }

                  
                        
                
                   
                    

                	if(input == '6')
                	{
                		system("cls");
                        showMainMenu();
                        break;
                	}
                }
            }
            else {
                showMainMenu();
            }
            break;
        }

        case '5': { 
            system("cls");
            cout << "Exiting";
            for (int i = 0; i < 3; ++i) {
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << ".";
            }
            exit(1);
        }

        default: {
            cout << "Error: Invalid option. Try again.\n";
            this_thread::sleep_for(chrono::milliseconds(1500));
            showMainMenu();
            cin >> input;
            break;
        }
        }
        cin >> input;
    }
}

//Ez azert van itt mert Mate billentyuzete szar
//<<