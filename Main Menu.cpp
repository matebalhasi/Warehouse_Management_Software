#include <iostream>
#include <conio.h>
#include <thread>
#include <fstream>
#include <sstream>



using namespace std;

void showMainMenu()
{
	cout << "Main Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << "1. Worker \n 2. Buyer \n 3. Supplier \n 4. Admin \n 5. Exit\n \n Enter a choice (1-5) ";
}
void showAdminMenu()
{
	cout << "Admin Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << "1. Personal Data \n 2. Worker Data \n 3. Storage Data \n 4. Complaints \n 5. Items\n 6. Exit\n \n Enter a choice (1-6) ";
}
void showWorkerMenu()
{
	cout << "Worker Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << "1. Personal Data \n 2. Storage \n 3. Items \n 4. Exit \n  \n Enter a choice (1-4) ";
}
void showBuyerMenu()
{
	cout << "Buyer Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << "1. Storage \n 2. Add Item \n 3. Write Complaint \n 4. Exit\n \n Enter a choice (1-5) ";
}
void showSupplierMenu()
{
	cout << "Supplier Menu" << endl;
	cout << "-------------" << endl;
	cout << "Select which user you wish to use:" << endl;
	cout << "1. Storage \n 2. Add Item \n 3. Write Complaint \n 4. Exit\n \n Enter a choice (1-5) ";
}

bool loginValidation(string ID, string password, char clearanceLevel, char menuPart)
{
	ifstream users("user.txt");
	if(!users.is_open())
	{
		cerr << "There was an error with the user file \n";
		return false;
	}

	string line, userID, userPassword;
	char userLevel;

	while (getline(users, line))
	{
		istringstream iss(line);
		iss >> userID >> userPassword >> userLevel;

		if (userID == ID && userPassword == password)
		{
			if (userLevel == clearanceLevel)
			{
				if (userLevel == menuPart)
				{
					return true;
				}
				else
				{
					cerr << "Error! User clearance not valid for this menu!";
					return false;
				}
			}
			else
			{
				cerr << "Error! User ID or Password is Invalid";
			}
		}

	}
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
				/*system("cls");
				cout << "Enter user ID:";
				cin >> input;
				cout << "Enter user password:";
				cin >> input;*/
				//if(loginValidation())
				
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

			}
			else if (input == '2')
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
			else if (input == '3')
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
			else if (input == '4')
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
