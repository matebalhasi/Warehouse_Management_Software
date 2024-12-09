#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


using namespace  std;

struct ResuplyLog
{
	string id;
	string name;
	int quantity;
};


void logResuply(const string& filename ,const ResuplyLog& log)
{
	ofstream logger(filename, ios::app);
	if (logger.is_open())
	{
		logger << "ID: " << log.id << std::endl;
		logger << "Name: " << log.name << std::endl;
		logger << "Quantity: " << log.quantity << std::endl;
		logger << std::endl;
		logger.close();
	}
	else
	{
		cerr << "Unable to open log file for writing" << std::endl;
	}
}

void loadLogs(vector<ResuplyLog>& logs)
{
	ifstream logReader("resuplylogs.txt");
	string line;
	ResuplyLog log;

	if(logReader.is_open())
	{
		while(getline(logReader,line))
		{
			size_t delimiter_pos = line.find(": ");

			if (delimiter_pos != std::string::npos) {
				std::string key = line.substr(0, delimiter_pos);
				std::string value = line.substr(delimiter_pos + 2);

				if (key == "ID") {
					log.id = value;
				}
				else if (key == "Name") {
					log.name = value;
				}
				
				else if (key == "Quantity") {
					log.quantity = std::stoi(value);
				}
			}
			if(line.empty()&&!log.id.empty())
			{
				logs.push_back(log);
				log = ResuplyLog();
			}
		}
		logReader.close();
	}
	else
	{
		cerr << "There was an error with opening the file for reading\n"	;
	}
}

void displayUserLogs(const vector<ResuplyLog>& logs, const string& username)
{
	cout << "\nHere are the ResuplyLogs for: " << username << "\n";
	for(const auto&log:logs)
	{
		if(log.id == username)
		{
			cout << "Name: " << log.name << endl;
			cout << "Quantity: " << log.quantity << endl;
			cout << std::endl;
		}
	}
}