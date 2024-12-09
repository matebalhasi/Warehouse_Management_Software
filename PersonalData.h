#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>


using namespace std;

class PersonalData
{
private:
	struct Worker
	{
		string userID;
		string name;
		string position;
		string hoursWorked;
		string PTORemaining;
	};
	unordered_map<std::string, Worker> workers;
	string filePath;

	
public:
	PersonalData(const string& filePath) {
		loadWorkerData(filePath);
	}
	void loadWorkerData(const string& filePath) {
		fstream file(filePath);
		if (!file.is_open()) {
			cout << "Error! File could not be opened: " << filePath << endl;
			return;
		}

		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			Worker worker;
			if (!(iss >> worker.userID >> worker.name >> worker.position >> worker.hoursWorked >> worker.PTORemaining)) {
				cout << "Error! Malformed line in " << filePath << endl;
				continue;
			}
			workers[worker.userID] = worker;
		}

		file.close();
	}
	void saveWorkerData(const string& filePath){
		ofstream file(filePath);
        if (!file.is_open()) {
            cout << "Error! Could not open file for writing: " << filePath << endl;
            return;
        }

        for (const auto& pair : workers) {
            const Worker& worker = pair.second;
            file << worker.userID << " " << worker.name << " " << worker.position << " "
                 << worker.hoursWorked << " " << worker.PTORemaining << endl;
        }
		file.close();
	}
	

	string getWorkerInfo(string userID)const
	{
		auto it = workers.find(userID);
		if (it != workers.end()) {
			const Worker& worker = it->second;
			ostringstream oss;
			oss << "Name: " << worker.name
				<< "\nPosition: " << worker.position
				<< "\nHours Worked: " << worker.hoursWorked
				<< "\nPTO Remaining: " << worker.PTORemaining;
			return oss.str();
		}
		else {
			return "Error: Worker not found";
		}
		
	}
	void listWorkers(const string& currentUserID) const {
		cout << "Worker List :" << endl;
		for (const auto& pair : workers) {
			const auto& worker = pair.second;
			const auto& userID = pair.first;

			if (userID != currentUserID) {
				cout << "UserID: " << userID
					<< ", Name: " << worker.name
					<< ", Position: " << worker.position
					<< ", Hours Worked: " << worker.hoursWorked
					<< ", PTO Remaining: " << worker.PTORemaining << endl;
			
			}
		}
	}
	void editWorkerInfo(const string& userID, const string& newName, const string& newPosition,
		const string& newHoursWorked, const string& newPTORemaining) {
		auto it = workers.find(userID);
		if (it != workers.end()) {
			it->second.name = newName;
			it->second.position = newPosition;
			it->second.hoursWorked = newHoursWorked;
			it->second.PTORemaining = newPTORemaining;

			saveWorkerData("worker_data.txt");
			cout << "Worker information updated successfully." << endl;
		}
		else {
			cout << "Error: Worker not found." << endl;
		}
	}
		

	
};

//Ez it azert van mert nem tudja ezt a karaktert valahogy a billentyuzetem kiirni.
//<<