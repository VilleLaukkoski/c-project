
// Project.cpp : Defines the entry point for the console application.
//
#include "pch.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
using namespace std;

class Repair {
public:
	Repair(string  value, string value2);
	void setClient(const string value);
	void setDescription(const string value);
	void setJob(const string value);
	void setTime(const int value);
	void setStatus(const string value);
	string stringValue();
	int* getTime() { return &time; }
	string* getStatus() { return &status; }
	void display();
	~Repair();

private:
	string client;
	string description;
	string workDone;
	int time;
	string status;
};
Repair::Repair(string value, string value2) {
	client = value;
	description = value2;
	workDone = "-";
	time = 0;
	status = "pending";
}
void Repair::setClient(const string value) {
	client = value;
}
void Repair::display() {
	cout << "client " << client << " - description " << description << " - work done " << workDone << " - time " << time << " - status " << status << endl;
}
string Repair::stringValue() {
	string value = client + "\n" + description + "\n" + workDone + "\n" + to_string(time) + "\n" + status + "\n";
	return value;
}
void Repair::setDescription(const string value) {
	description = value;
}
void Repair::setJob(const string value) {
	workDone = value;
}
void Repair::setTime(const int value) {
	time = value;
}
void Repair::setStatus(const string value) {
	status = value;
}
bool compareTimes(Repair &a, Repair &b) {
	return (*a.getTime() > *b.getTime());
}
bool compareStatus(Repair &a, Repair &b) {
	string aArvo = *a.getStatus();
	string bArvo = *b.getStatus();
	return (aArvo < bArvo);
}
Repair::~Repair() {

}
int main()
{
	int valueSwitch = 0;
	vector<Repair> repairs;
	string clientValue = "";
	string descriptionValue = "";
	Repair job(clientValue, descriptionValue);
	int jobFix = 99;
	string jobFixValue = "";
	int jobTimeValue = 0;
	ofstream out;
	ifstream inFile;
	vector<Repair> topRepairs;
	string line;
	string word;
	string valueWord[10];
	int words=0;
	while (true) {
		switch (valueSwitch) {
		case 0:
			cout << "This is computer repair shop" << endl;
			valueSwitch = 99;
			break;
		case 1:
			repairs.clear();
			out.open("jobs.txt");
			out << "";
			out.close();
			valueSwitch = 99;
			break;
		case 2:
			out.open("jobs.txt");
			//fstream::app
			for (int i = 0; i < repairs.size(); i++) {
				out << repairs[i].stringValue();
			};
			out.close();
			repairs.clear();
			valueSwitch = 99;
			break;
		case 3:
			inFile.open("jobs.txt");
			repairs.clear();
			while (!inFile.eof()) {
				if (words == 0) {
					inFile >> word;
					job.setClient(word);
				}
				else if (words == 1) {
					inFile >> word;
					job.setDescription(word);
				}
				else if (words == 2) {
					inFile >> word;
					job.setJob(word);
				}
				else if (words == 3) {
					inFile >> jobTimeValue;
					job.setTime(jobTimeValue);
				}
				else {
					inFile >> word;
					job.setStatus(word);
					repairs.push_back(job);
				};
				if (words < 4) {
					words++;
				}
				else {
					words = 0;
				};
			};
			inFile.close();
			valueSwitch = 99;
			break;
		case 4:
			clientValue = "";
			descriptionValue = "";
			cout << "Input new repair" << endl;
			cout << "Give client name (2-30 characters):" << endl;
			while (size(clientValue) < 2 || size(clientValue) > 30) {
				cin >> clientValue;
				if (size(clientValue) < 2 || size(clientValue) > 30) {
					cout << "Name must be between 2-30 characters, enter a new one" << endl;
				};
			};
			cout << "Give job description (5-100 characters):" << endl;
			while (size(descriptionValue) < 5 || size(descriptionValue) > 100) {
				cin >> descriptionValue;
				if (size(descriptionValue) < 5 || size(descriptionValue) > 100) {
					cout << "Description must be between 5-100 characters, enter a new one" << endl;
				};
			};
			job.setClient(clientValue);
			job.setDescription(descriptionValue);
			repairs.push_back(job);
			valueSwitch = 99;
			break;
		case 5:
			if (repairs.size() > 0) {
				cout << "What repair would you like to do? (input 1-" << repairs.size() << ")" << endl;
				while (jobFix < 1 || jobFix > repairs.size()) {
					while (!(cin >> jobFix)) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input.  Try again: ";
					}
				}
				jobFix--;
				cout << "input work done" << endl;
				while (size(jobFixValue) < 5 || size(jobFixValue) > 100) {
					cin >> jobFixValue;
					if (size(jobFixValue) < 5 || size(jobFixValue) > 100) {
						cout << "Work description must be between 5-100 characters, enter a new one" << endl;
					};
				};
				repairs[jobFix].setJob(jobFixValue);
				cout << "input time (hours)" << endl;
				while (!(cin >> jobTimeValue)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input.  Try again: ";
				}
				repairs[jobFix].setTime(jobTimeValue);
				repairs[jobFix].setStatus("done");
			}
			valueSwitch = 99;
			break;
		case 6:
			topRepairs.erase(topRepairs.begin(), topRepairs.end());
			for (int i = 0; i < repairs.size(); i++)
				topRepairs.push_back(repairs[i]);
			sort(topRepairs.begin(), topRepairs.end(), compareTimes);
			for (int i = 0; i < 3; i++) {
				if (i < repairs.size()) {
					topRepairs[i].display();
				}
			};
			valueSwitch = 99;
			break;
		case 7:
			topRepairs.erase(topRepairs.begin(), topRepairs.end());
			for (int i = 0; i < repairs.size(); i++)
				topRepairs.push_back(repairs[i]);
			sort(topRepairs.begin(), topRepairs.end(), compareStatus);
			for (int i = 0; i < topRepairs.size(); i++) {
				topRepairs[i].display();
			};
			valueSwitch = 99;
			break;
		case 8:

			//for checking memory leaks
		/*{
			return 0;
			_CrtDumpMemoryLeaks();

		}*/
		return 0;
		default:
			cout << "-----------------" << endl;
			cout << "Input 1-8 to advance" << endl; //done
			cout << "1. clear repairs from history" << endl; //done
			cout << "2. save repair records to disk" << endl; //done
			cout << "3. read repair records from disk" << endl; //done
			cout << "4. Enter new repair" << endl; //done
			cout << "5. Perform fix" << endl; //done
			cout << "6. top 3 Most difficult repairs based on time" << endl; //done
			cout << "7. Repairs (done / pending)" << endl; //done
			cout << "8. exit" << endl; //done
			while (!(cin >> valueSwitch)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input.  Try again: ";
			}
			cout << "-----------------" << endl;
			break;
		};
	}
	return 0;
}