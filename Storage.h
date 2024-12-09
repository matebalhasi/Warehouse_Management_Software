#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

// Adatokat tároló struktúra
struct Data {
    std::string id;
    std::string name;
    int quantity;
    std::string location;
};

// Adatok beolvasása a fájlból
void loadData(const std::string& filename, std::vector<Data>& dataVec) {
    std::ifstream infile(filename);
    std::string line;

    if (infile.is_open()) {
        Data data;
        while (std::getline(infile, line)) {
            size_t delimiter_pos = line.find(": ");
            if (delimiter_pos != std::string::npos) {
                std::string key = line.substr(0, delimiter_pos);
                std::string value = line.substr(delimiter_pos + 2);

                if (key == "ID") {
                    data.id = value;
                }
                else if (key == "name") {
                    data.name = value;
                }
                else if (key == "quantity") {
                    data.quantity = std::stoi(value);
                }
                else if (key == "location") {
                    data.location = value;
                }
            }
            if (line.empty()) {  // Új rekord kezdete
                dataVec.push_back(data);
                data = Data();  // Nullázzuk az aktuális adatot
            }
        }
        if (!data.id.empty()) {  // Utolsó rekord hozzáadása, ha nincs üres sor a végén
            dataVec.push_back(data);
        }
        infile.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

// Adatok mentése a fájlba
void saveData(const std::string& filename, const std::vector<Data>& dataVec) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const auto& data : dataVec) {
            outfile << "ID: " << data.id << std::endl;
            outfile << "name: " << data.name << std::endl;
            outfile << "quantity: " << data.quantity << std::endl;
            outfile << "location: " << data.location << std::endl;
            outfile << std::endl;  // Üres sor az új rekordhoz
        }
        outfile.close();
    }
    else {
        std::cerr << "Unable to open file for writing" << std::endl;
    }
}

// Adatok megjelenítése a konzolon
void displayData(const std::vector<Data>& dataVec) {
    for (const auto& data : dataVec) {
        std::cout << "ID: " << data.id << std::endl;
        std::cout << "Name: " << data.name << std::endl;
        std::cout << "Quantity: " << data.quantity << std::endl;
        std::cout << "Location: " << data.location << std::endl;
        std::cout << std::endl;
    }
}

// Adatok módosítása
void manageData(std::vector<Data>& dataVec) {
    bool running = true;
    while (running) {
        std::cout << "\nCurrent data:\n";
        displayData(dataVec);

        std::cout << "Select a record to modify (1-" << dataVec.size() << "), or 0 to exit: ";
        int record;
        std::cin >> record;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (record == 0) {
            running = false;
            continue;
        }

        if (record < 1 || record > dataVec.size()) {
            std::cout << "Invalid record number, please try again.\n";
            continue;
        }

        Data& data = dataVec[record - 1];

        std::cout << "\nModify record " << record << ":\n";
        std::cout << "1. Change ID\n";
        std::cout << "2. Change Name\n";
        std::cout << "3. Change Quantity\n";
        std::cout << "4. Change Location\n";
        std::cout << "5. Save and Exit\n";
        std::cout << "6. Exit without saving\n";
        std::cout << "Select an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            std::cout << "Enter new ID: ";
            std::getline(std::cin, data.id);
            break;
        case 2:
            std::cout << "Enter new Name: ";
            std::getline(std::cin, data.name);
            break;
        case 3:
            std::cout << "Enter new Quantity: ";
            std::cin >> data.quantity;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        case 4:
            std::cout << "Enter new Location: ";
            std::getline(std::cin, data.location);
            break;
        case 5:
            saveData("adatok.txt", dataVec);
            running = false;
            break;
        case 6:
            running = false;
            break;
        default:
            std::cout << "Invalid option, please try again.\n";
            break;
        }
    }
}

#endif // DATA_MANAGER_H