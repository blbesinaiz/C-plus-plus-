/**************************************************************************
Brianna Besinaiz
CSC 372
10/22/17
Program Title: Process Program (Linked List Implementation)
Description: This program manages an I/O process list and a ready process
			 list for an OS. The program will manipulate the lists based
			 on a process requirements from a loaded file.
***************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <sstream>

using namespace std;

struct processType;					//Allows definition of processPtr, not defined yet
typedef processType * processPtr;	//Typedef creates an alias, node & *nodeptr is equivalent

struct processType			//Contains 4 parts of data
{
	unsigned int id;		//Process ID
	string name;			//Process name
	unsigned int runTime;	//Process Running Time
	void createProcess();	//Function to create a new process

	processPtr next;		//Pointer to point to next next
};

class processes
{
public:
	
	void loadList();						//Load process lists into list array
	void insertList(int, string, int);		//Insert a process into a process list
	void searchLlist (int age, bool & done, processPtr & prev,		//Searches linked list
					  processPtr & pos);
	void deleteProcess(int);				//Delete a process from a process list
	void retrieveProcess(int);				//Retrieve and print an individual a process from a process list
	void printProcessList();				//Prints a proces from a process list
	processes();							// Default Constructor

private:

	
	processPtr ProcessList;			//Declare list to pass amongst functions
	int size;						//Variable to hold size of arrays
	void printList() const;			//Prints processes of a list
};

processes::processes()				//DO NO NEED??
{
	processPtr next = NULL;
}

void processes::loadList()			//Loads program in reverse order for now
{														
	ifstream infile;
	string filename;

	//cout << "Enter the file you wish to load: " << endl;		//Program asks user in main
	cin >> filename;
	infile.open(filename);

	ProcessList = NULL;			//Set empty list to point to NULL
	processType temp;			//Creat a pointer called temp
	processPtr tempPtr;			//name temp pointer
	while (!infile.eof())		
	{
		tempPtr = new processType;		//create new node that looks like processType		
		infile >> tempPtr->id			//Inputs data from text file into node
				>> tempPtr->name
				>> tempPtr->runTime;
		tempPtr->next = ProcessList;	//Sets new node to point to what ProcessList points to (NULL)
		ProcessList = tempPtr;			//ProcessList now points to new node
	}

	infile.close();
}

void processes::printList() const
{
	cout << "Print list of Processes" << endl;
	for (processPtr p = ProcessList; p !=NULL; p = p->next)		//Loop to print contents of list
	{
		cout << "ID: " << p->id				
			 << " Name: " << p->name
			 << " Run Time: " << p->runTime << endl;
	}
}

void processes::printProcessList()
{
	printList();
	cout << endl;
}

void processes::insertList(int tempID, string tempName, int tempRT)
{
	processType temp;			//Create a pointer called temp
	processPtr tempPtr;			//name temp pointer

	tempPtr = new processType;		//create new node that looks like processType		
	tempPtr->id = tempID;			//Inputs data from passed values into node
	tempPtr->name = tempName;
	tempPtr->runTime = tempRT;

	tempPtr->next = ProcessList;	//Sets new node to point to what ProcessList points to (NULL)
	ProcessList = tempPtr;			//ProcessList now points to new node
}

void processes::searchLlist (int searchID, bool & done, processPtr & prev,
				   processPtr & pos)
{
	done = false;		//Initialize to false
	pos = NULL;			//Initialize to point to NULL
	prev = NULL;
	for (processPtr p = ProcessList;  (p != NULL) && (done == false); p= p->next)	//Loop to search list
	{
		if (p->id == searchID)		//When p->id matches search ID
		{
			done = true;
			pos = p;
		}
		else
			prev = p;				//If never found then p points to list??
	}
}
void processes::deleteProcess(int delProcess)
{
	
	bool done = false;
	processPtr prev;
	processPtr pos;

	searchLlist (delProcess, done, prev, pos);

	if (prev == NULL)
		ProcessList  = ProcessList->next;		//delete first node
	else if (pos == NULL)
		prev->next = NULL;						//delete last node
	else
		prev->next = pos->next;					
}

void processes::retrieveProcess(int retrieveID)
{

	bool done = false;
	processPtr prev;
	processPtr pos;

	searchLlist (retrieveID, done, prev, pos);		//Searches the list
	if (done = true)								//Prints once found
	{
		cout << "ID: " << pos->id
			 << " Name: " << pos-> name 
			 << " Run Time: " << pos->runTime <<endl;
		cout << endl;
	}
}


void processType::createProcess()
{
	int listOption;

	processType p;					//Createa a pointer called p
	processPtr proPtr;				//name the p pointer

	proPtr = new processType;			//create new node that looks like processType	
	//Create process ID
	proPtr-> id = rand() % 100;			//ID range 0 - 99
	
	//Create Process Name
	stringstream ss;
	ss << proPtr->id;						//Convert ID to string
	string str = ss.str();
	proPtr->name = 'p' + str;				//Concatenate p + string ID
	
	//Create Process Run Time
	proPtr->runTime = rand () % 1000;		//Run Time range 0 - 999

	//Create list Option (I/O or Ready)
	listOption = rand() % 2;		//Range 0 - 1
	
	cout << "ID: " << proPtr->id << " Name: " << proPtr->name << " Run Time: " 
		 << proPtr->runTime << " List " << listOption << endl;
}

int main()
{
	
	processes IO;				//Declare object for IO list
	processes Ready;			//Declare object for Ready list
	processType newProcess;		//Declare object for new process to be created
	processPtr prev;
	processPtr pos;

	int size;
	ifstream infile;
	int list = -1;				//Deterimines which process list
	bool done;

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
			}
			else if(list == 1)
			{
				Ready.insertList(ID, name, RunTime);
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
		}

		else if(opCode == 'p')
		{

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
			cout << endl;
		}
		opCode = ' ';		//Resets opcode to a space
	};

	system("pause");
	return 0;
}
