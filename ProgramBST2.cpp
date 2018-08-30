/**************************************************************************
CSC 372
10/31/17
Program Title: Process Program (Binary Search Tree)
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

ifstream infile;
string filename;


struct processType
{
	unsigned int id;		//Process ID
	string name;			//Process name
	unsigned int runTime;	//Process Running Time
	void createProcess();	//Function to create a new process
};

struct tree_node;				//Create tree struct
typedef tree_node * tree_ptr;	//Create tree pointer
struct tree_node
{
	tree_ptr left;				//Points left
	processType data;			//Holds data/information
	tree_ptr right;				//Points right

};

class processes
{
public:
	
	void insertNode(tree_ptr &T, processType item);
	void insert_Tree(processType);						//Function inserts values into tree
	void buildTreeProc();					//Loads process from text file and builds into a tree
	
	tree_ptr find_Min(tree_ptr T);
	void delete_node(tree_ptr &T, int deleteID);
	void deleteProcess(int);				//Delete a process from a process list
	
	void retrieve_Tree(tree_ptr T, int retrieveNode);
	void retrieveProcess(int);				//Retrieve and print an individual a process from a process list
	
	void print_Tree(tree_ptr T);
	void printProcessList();				//Prints a proces from a process list
	
	//processes();							// Default Constructor
	

private:
	tree_ptr T;
	void printTree() const;			//Prints processes of a list
	processType pos;				//Holds first root of tree
};

void processes::insertNode(tree_ptr &T, processType item)	//Internal function that inserts node into tree
{
	
	if(T == NULL) //if sub tree is empty
	{
		T = new tree_node;
		T->left = NULL;
		T->right = NULL;
		T->data = item;
	}
	
	else
	{
		if(item.id < T->data.id)		//Compares node with what in tree and sorts left or right
			insertNode(T->left,item);
	
		else
			insertNode(T->right, item);
	}
}

//Function acts as "dummy" function as allows insert_Tree to be called in main
//Main can't "see" T
//Allows function to get item value from main and calls insertNode to actually insert into tree
void processes::insert_Tree(processType item)	//Calls insetNode function to insert node
{
	insertNode(T, item);
}


void processes::buildTreeProc()
{
	T = NULL;													//Initialize T pointer to NULL
	//cout << "Enter the file you wish to load: " << endl;		//Program asks user in main
	cin >> filename;

	infile.open(filename);
	processType data;
	while(!infile.eof())
	{
		infile >> data.id >> data.name >> data.runTime;
		insertNode(T,data);
	}

	infile.close();
}

void processes::print_Tree(tree_ptr T)
{
	if (T != NULL)
	{
 
		print_Tree(T->left);
		print_Tree(T->right);
		cout << "ID: " << T->data.id 
			 << " Name: " << T->data.name
			 << " Run Time: " << T->data.runTime <<endl;
		
	}
}

void processes::printProcessList()	//Function called in main
{
	print_Tree(T);
	cout << endl;
}

tree_ptr processes::find_Min(tree_ptr T)
{
	if (T== NULL)
		return NULL;
	if (T->left == NULL)
		return T;
	return find_Min (T->left);
}

//This function deletes a node from a binary tree

void processes::delete_node(tree_ptr &T, int deleteID)
{
	if (T == NULL)
	   return;
	if (deleteID < T->data.id)
		delete_node(T->left, deleteID);
	else if (deleteID > T->data.id)
		delete_node(T->right, deleteID);
	else if (T->left != NULL && T->right != NULL) //two children
	{
		
		T->data.id = find_Min(T->right)->data.id; //find smallest on right and copies to root
		delete_node(T->right, T->data.id); //delete that minimum value from the right sub-tree
	}
	else // node has one child or less
	{
		tree_ptr old_node = T;
		if (T->left != NULL)
			T = T->left;
		else
			T = T->right;

		delete old_node;
	}
}

void processes::deleteProcess(int delProcess)
{
	delete_node(T, delProcess);
}


void processes::retrieve_Tree(tree_ptr T, int retrieveNode)
{
	if(T != NULL)
	{
		retrieve_Tree(T->left, retrieveNode);
		if(retrieveNode == T->data.id)
			cout << "ID: " << T->data.id 
				 << " Name: " << T->data.name
				 << " Run Time: " << T->data.runTime <<endl;
		retrieve_Tree(T->right, retrieveNode);
	}
}


void processes::retrieveProcess(int retrieveID)
{
	retrieve_Tree(T, retrieveID);
}

void processType::createProcess()
{
	int listOption;

	processType p;					//Declare object of process
	
	//Create process ID
	p.id = rand() % 100;			//ID range 0 - 99

	//Create Process Name
	stringstream ss;
	ss << p.id;						//Convert ID to string
	string str = ss.str();
	p.name = 'p' + str;				//Concatenate p + string ID
	
	//Create Process Run Time
	p.runTime = rand () % 1000;		//Run Time range 0 - 999

	//Create list Option (I/O or Ready)
	listOption = rand() % 2;		//Range 0 - 1
	
	cout << "ID: " << p.id << " Name: " << p.name << " Run Time: " 
		 << p.runTime << " List " << listOption << endl;
}
			
int main()
{
	
	processes IO;				//Declare object for IO list
	processes Ready;			//Declare object for Ready list
	processType newProcess;		//Declare object for new process to be created

	ifstream infile;
	int list = -1;				//Deterimines which process list

    char opCode = ' ';			//Initializing opcode variable

	srand (time(NULL));			//Initializes seed

	cout << "To begin, enter the Input/Ouput process file name: " << endl;
	IO.buildTreeProc();		//Load IO list file

	cout << "Now, enter the Ready process file name: " << endl;
	Ready.buildTreeProc();	//Load Ready list file

	infile.open("process.DAT");		//Open Process File


	while(!infile.eof())
	{
		infile >> opCode;			//Reads in first character and saves into opcode

		if(opCode == 'i')
		{
			int ID, RunTime;
			string name;
			processType item;
			
			infile >> item.id;		
			infile >> item.name;
			infile >> item.runTime;
			infile >> list;

			if(list == 0)
			{
				IO.insert_Tree(item);
				cout << endl;
			}
			else if(list == 1)
			{
				Ready.insert_Tree(item);
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
				cout << "Deleting Process: " << delCode << endl;
				cout << endl;
				IO.deleteProcess(delCode);
			}
			else if(list == 1)
			{
				cout << "Deleting Process: " << delCode << endl;
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