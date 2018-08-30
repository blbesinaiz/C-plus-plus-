/**************************************************************************
Brianna Besinaiz
CSC 372
10/22/17
Program Title: Process Program (STL List Implemented)
Description: This program manages an I/O process list and a ready process
			 list for an OS. The program will manipulate the lists based
			 on a process requirements from a loaded file.
***************************************************************************/

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <time.h>
#include <sstream>

using namespace std;

struct processType
{
	unsigned int id;		//Process ID
	string name;			//Process name
	unsigned int runTime;	//Process Running Time
	void createProcess();	//Function to create a new process

	 bool operator == (const processType& p)	//Overload "is equal to" operator
	  {
        if (id == p.id)
           return true;
        else
            return false;
       } 
};

typedef list<processType> Process_list;		//Create alias for "list<processType> Process_list"
typedef Process_list:: iterator list_it;	//Create alias for the iterator used in loops

class processes
{
public:
	
	void loadList();						//Load process lists into list array
	void insertList(int, string, int);		//Insert a process into a process list
	void deleteProcess(int);				//Delete a process from a process list
	void retrieveProcess(int);				//Retrieve and print an individual a process from a process list
	void printProcessList();				//Prints a proces from a process list
	processes();							// Default Constructor

private:

	Process_list listProcess;		//STL list name
	void printList();				//Prints processes of a list
};

processes::processes()
{
	
}

void processes::loadList()
{
	ifstream infile;
	string filename;

	//cout << "Enter the file you wish to load: " << endl;		//Program asks user in main
	cin >> filename;

	infile.open(filename);
	
	processType temp;		//Temp variable to hold info from text file
	while (!infile.eof())		
	{
		infile >> temp.id >> temp.name >> temp.runTime;		//Place data from text file into node
		listProcess.push_back(temp);						//Build list in order
	}
	infile.close();
}

void processes::printList()
{
	for (list_it p  = listProcess.begin();  p != listProcess.end(); p++)
	cout << "ID: " << p->id				
			<< " Name: " << p->name
			<< " Run Time: " << p->runTime << endl;
}

void processes::printProcessList()
{
	printList();
	cout << endl;
}


void processes::insertList(int tempID, string tempName, int tempRT)
{
	processType temp;					//Temp variable to hold info from text file

		temp.id = tempID;
		temp.name = tempName;
		temp.runTime = tempRT;			//Place data from text file into node
		listProcess.push_back(temp);
}

void processes::deleteProcess(int delProcess)
{
	processType temp;			//Declare a node temp to look like processType
	temp.id = delProcess;		
	listProcess.remove(temp);	//Remove function deletes whole node from list
}

void processes::retrieveProcess(int retrieveID)
{
	for(list_it p = listProcess.begin(); p != listProcess.end(); p++)
	{
		if (p -> id == retrieveID)			//Compare id with ID's in the list
		{
			cout << "ID: " << p->id			//Prints once found		
			<< " Name: " << p->name
			<< " Run Time: " << p->runTime << endl;
		}
	}
}


void processType::createProcess()
{
	int listOption;

	processType pro;					//Declare object of process
	
	//Create process ID
	pro.id = rand() % 100;				//ID range 0 - 99

	//Create Process Name
	stringstream ss;
	ss << pro.id;						//Convert ID to string
	string str = ss.str();
	pro.name = 'p' + str;				//Concatenate p + string ID
	
	//Create Process Run Time
	pro.runTime = rand () % 1000;		//Run Time range 0 - 999

	//Create list Option (I/O or Ready)
	listOption = rand() % 2;			//Range 0 - 1
	
	cout << "ID: " << pro.id << " Name: " << pro.name << " Run Time: " 
		 << pro.runTime << " List " << listOption << endl;
}
			
int main()
{
	
	processes IO;				//Declare object for IO list
	processes Ready;			//Declare object for Ready list
	processType newProcess;		//Declare object for new process to be created

	int size;
	ifstream infile;
	int list = -1;				//Deterimines which process list

    char opCode = ' ';			//Initializing opcode variable

	srand (time(NULL));			//Initializes seed

	cout << "To begin, enter the Input/Ouput process file name: " << endl;
	IO.loadList();		//Load IO list file

	cout << "Now, enter the Ready process file name: " << endl;
	Ready.loadList();	//Load Ready list file
	cout << endl;

	infile.open("process.DAT");		//Open Process File

	while(!infile.eof())
	{
		infile >> opCode;			//Reads in first character and saves into opcode

		if(opCode == 'i')
		{
			int ID, RunTime;
			string name;
			
			infile >> ID;		
			infile >> name;
			infile >> RunTime;
			infile >> list;

			if(list == 0)
			{
				IO.insertList(ID, name, RunTime);
				cout << endl;
			}
			else if(list == 1)
			{
				Ready.insertList(ID, name, RunTime);
				cout << endl;
			}
		}

		else if (opCode == 'd')
		{
			int delCode;
			infile >> delCode;
			infile >> list;

			if(list == 0)
			{
				IO.deleteProcess(delCode);
			}
			else if(list == 1)
			{
				Ready.deleteProcess(delCode);
			}
			
		}

		else if(opCode == 'r')
		{
			int retrieve;
			infile >> retrieve;
			infile >> list;

			cout << "Retrive: " << endl;
			if(list == 0)
			{
				IO.retrieveProcess(retrieve);
			}
			else if(list == 1)
			{
				Ready.retrieveProcess(retrieve);
			}
			cout << endl;
		}

		else if(opCode == 'p')
		{
			cout << "Print" << endl;

			infile >> list;

			if(list == 0)
			{
				IO.printProcessList();
			}
			else if(list == 1)
			{
				Ready.printProcessList();
			}
		}
		
		else if(opCode == 'c')
		{
			cout << "Create Process" << endl;
			newProcess.createProcess();
		}
		opCode = ' ';		//Resets opcode to a space
	};
	system("pause");
	return 0;
}
