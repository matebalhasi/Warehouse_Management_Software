#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "ResuplyLogger.h"
#include "Storage.h"



using namespace std;

class Items
{
private:


	struct Item
	{
		int id, quantity;
		string name, type;

		Item() :id(0), quantity(0), name(""), type(""){}

		Item(int id, const string& name, const string& type, int quantity)
			: id(id), name(name), type(type), quantity(quantity) {}
		
	};
	vector<Item> ItemLists;

	int nextFreeID;

	
	string filePath = "items.txt";
	
	void loadItems()
	{
		ifstream itemFile(filePath);
		if(!itemFile.is_open())
		{
			cout << "An error has occured! The items could not be loaded";
			return;
		}


		string line;
		while (getline(itemFile, line)) {
			istringstream iss(line);
			Item item;
			if (iss >> item.id>>item.name>>item.type>>item.quantity) {

				ItemLists.push_back(item);
				if (item.id >= nextFreeID)
				{
					nextFreeID = item.id + 1
						;
				}
			}
		}
		itemFile.close();
	}

	
	int getMaxID() const {
		int maxID = 0;
		for (const auto& item : ItemLists) {
			if (item.id > maxID) {
				maxID = item.id;
			}
		}
		return maxID;
	}

	bool isItemInStorage(const string& itemName, const vector<Data>& storageData) {
		for (const auto& data : storageData) {
			if (data.name == itemName) {
				return true;
			}
		}
		return false;
	}

public:
	Items(): nextFreeID(1)
	{
		loadItems();
	}


	void addPurchase(vector<Data>& storageData)
	{
		
		string itemName, itemCategory;
		int quantity;
	
		int newID = getMaxID() + 1;
		cout << "Enter item name: ";
		cin >> itemName;
		cout << "Enter quantity: ";
		cin >> quantity;

		if(!isItemInStorage(itemName,storageData))
		{
			cout << "Error! Item does not exist in storage. Purchase canceled.\n";
			return;
		}



		ofstream file("items.txt", ios::app); 
		if (!file) {
			cout << "Error opening file for writing!" << endl;
			return;
		}
		file << newID<< " "<<  itemName << " " << "Purchase" << " " << quantity << endl;

		cout << "Item added successfully!" << endl;

		

	}
	void addResuply(string& username)
	{
		
		string itemName, itemCategory;
		int quantity;

		int newID = getMaxID() + 1;
		cout << "Enter item name: ";
		cin >> itemName;
		cout << "Enter quantity: ";
		cin >> quantity;

		ofstream file("items.txt", ios::app);
		if (!file) {
			cout << "Error opening file for writing!" << endl;
			return;
		}
		file << newID << " " << itemName << " Resuply " << quantity << endl;
		file.close();

		ResuplyLog log;
		log.id = username;
		log.name = itemName;
		log.quantity = quantity;

		const string logFilename = "resuplylogs.txt";
		logResuply(logFilename, log);
		cout << "Item added successfully!" << endl;



	}


	void listItems()
	{
		if(ItemLists.empty())
		{
			cout << "No items in the system.\n";
			return;
		}

		cout << "Items in the system currently: " << "\n ID\tName\t\tType\tQuantity" << "------------------------------\n";


		for(auto& item:ItemLists)
		{
			cout << item.id << "\t" << item.name << "\t" << item.type << "\t" << item.quantity << "\n";
		}


	}

};


//<<