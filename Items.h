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
			: id(id), name(name), type(type), quantity(quantity) {};

		bool operator==(const Item& other) const {
			return id == other.id &&
				name == other.name &&
				type == other.type &&
				quantity == other.quantity;
		}
		
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
	void saveItemData() {
		ofstream file("items.txt");
		if (!file.is_open()) {
			cout << "Error! Could not open file for writing: " << filePath << endl;
			return;
		}

		for (const auto& item : ItemLists) {
			file << item.id << " " << item.name << " " << item.type <<" " << item.quantity << "\n";
			
		}
		file.close();
	}

	void editItems(const string, const string& itemName, const string& itemtype, const string& itemQuantity)
	{
		string targetCode;
		bool itemFound = false;

		cout << "Enter the code of the item you want to edit: ";
		cin >> targetCode;
		int targetID;
		try
		{
			targetID = stoi(targetCode);
		}
		catch (const invalid_argument& e) {
			cout << "Invalid item ID format.\n";
			return;
		}
		catch (const out_of_range& e) {
			cout << "Item ID is out of range.\n";
			return;
		}


		for (auto& item : ItemLists) {
			if (item.id == targetID) {
				itemFound = true;
				cout << "Editing item: " << item.id << " (" << item.name << ")\n";

				cout << "Enter new name (or press Enter to keep the current): ";
				string newName;
				cin.ignore();
				getline(cin, newName);
				if (!newName.empty()) {
					item.name = newName;
				}

				cout << "Enter new type: ";
				string newType;
				cin >> newType;
				if (!newType.empty()) {
					item.type = newType;
				}

				cout << "Enter new quantity (-1 to keep the current quantity): ";
				int newQuantity;

				cin >> newQuantity;

				if (newQuantity >= 0) {
					item.quantity = newQuantity;
				}

				
				saveItemData();
				cout << "\nItem updated successfully!\n";
				break;
			}
		}
	}


	void listItems()
	{
		if(ItemLists.empty())
		{
			cout << "No items in the system.\n";
			return;
		}

		cout << "Items in the system currently: " << "\n ID\tName\t\tType\tQuantity" << "\n------------------------------\n";


		for(auto& item:ItemLists)
		{
			cout << item.id << "\t" << item.name << "\t" << item.type << "\t" << item.quantity << "\n";
		}


	}

};


//<<