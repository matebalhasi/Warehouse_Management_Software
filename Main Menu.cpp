#include <iostream>
#include <conio.h>
#include <thread>
#include <fstream>
#include <sstream>



using namespace std;

//press key to continue
void pressToContinue()
{
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




//The main menu
void showMainMenu()
{
	cout << "Main Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << " 1. Worker \n 2. Buyer \n 3. Supplier \n 4. Admin \n 5. Exit\n \n Enter a choice (1-5) ";
}
//Sub menu for Admins
void showAdminMenu()
{
	cout << "Admin Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << " 1. Personal Data \n 2. Worker Data \n 3. Storage Data \n 4. Complaints \n 5. Items\n 6. Exit\n \n Enter a choice (1-6) ";
}
//Sub menu for Workers
void showWorkerMenu()
{
	cout << "Worker Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << " 1. Personal Data \n 2. Storage \n 3. Items \n 4. Exit \n  \n Enter a choice (1-4) ";
}
//Sub Menu for Buyers
void showBuyerMenu()
{
	cout << "Buyer Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << " 1. Storage \n 2. Add Item \n 3. Write Complaint \n 4. Exit\n \n Enter a choice (1-5) ";
}
//Sub menu for Suppliers
void showSupplierMenu()
{
	cout << "Supplier Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << " 1. Storage \n 2. Add Item \n 3. Write Complaint \n 4. Exit\n \n Enter a choice (1-5) ";
}

bool loginValidation(const string id, const string password, const char clearance_level )
{

	ifstream users("users.txt");
	if(!users.is_open())
	{
		cout << "Error! The file could not be upened! \n";
		return false;
	}


	string input, userID, userPassword;
	char user_clearance_level;
	while(getline(users, input))
	{
		istringstream iss(input);
		iss >> userID >> userPassword >> user_clearance_level;
		
		if(userID == id && userPassword== password)
		{
			if (user_clearance_level == clearance_level|| user_clearance_level == '4')
			{
				return true;
			}
			
			else
			{
				system("cls");
				cout << "Error! User clearance level does not match!";
				cout << "\n\nPress any key to continue.";
				pressToContinue();
				return false;
					
			}
			
			
		}
	}
	system("cls");
	cout << "Error! User Id and/or password does not match!";
	cout << "\n\nPress any key to continue.";
	pressToContinue();
	return false;

}




int main()
{

	char input;
	string id, password;
	showMainMenu();
	cin >> input;
	while (true)
	{
		//<<



		if (input == '1')
		{
		
			system("cls");

			cout << "Enter userID:";
			cin >> id;
			cout << "\n Enter Password:";
			cin >> password;
			
				
				if(loginValidation(id,password,input))
				{
					system("cls");
					showWorkerMenu();
					cin >> input;
					while (true)
					{
						if (input == '4')
						{
							system("cls");
							showMainMenu();
							break;
						}

					}
				}else
				{
					system("cls");
					showMainMenu();
				}
				

			}
			else if (input == '2')
			{
			
				system("cls");

				cout << "Enter userID:";
				cin >> id;
				cout << "\n Enter Password:";
				cin >> password;


				if (loginValidation(id, password, input))
				{
					system("cls");
					showBuyerMenu();
					cin >> input;
					while (true)
					{

						if (input == '4')
						{
							system("cls");
							showMainMenu();
							break;
						}
					}
				}
				else
				{
					system("cls");
					showMainMenu();
				}
			}
			else if (input == '3')
			{
				
				system("cls");

				cout << " Enter userID:";
				cin >> id;
				cout << "\n Enter Password:";
				cin >> password;
				if (loginValidation(id, password, input))
				{
					system("cls");
					showSupplierMenu();
					cin >> input;
					while (true)
					{
						if (input == '4')
						{
							system("cls");
							showMainMenu();
							break;
						}

					}
				}
				else
				{
					system("cls");
					showMainMenu();
				}
				

			}
			else if (input == '4')
			{
			
				system("cls");
				cout << " Enter userID:";
				cin >> id;
				cout << "\n Enter Password:";
				if(loginValidation(id,password,input))
				{
					system("cls");
					showAdminMenu();
					cin >> input;
					while (true)
					{
						if (input == '6')
						{
							system("cls");
							showMainMenu();
							break;
						}

					}
				}
				else
				{
					system("cls");
					showMainMenu();
				}
				
				

			}
			else if (input == '5')
			{
				system("cls");
				cout << "Exiting";
				for (int i = 0; 3 > i; i++)
				{
					this_thread::sleep_for(chrono::milliseconds(500));
					cout << ".";
				}

				break;
			}
			else
			{
				system("cls");
				cout << "Error: Wrong option.";
				this_thread::sleep_for(chrono::milliseconds(1500));
				system("cls");
				showMainMenu();
				cin >> input;
			}

			cin >> input;

		}
	}
