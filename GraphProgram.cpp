/**************************************************************
Brianna Besiniaiz
CSC 372
Program #5: Graph Connections
Description: This program takes the structure of a graph and 
			 stores the information in an array-adjaceny list.
			 The user then chooses options from a menu to determine
			 person relationships from the graph.
****************************************************************/

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <iomanip>			//For spacing
#include <queue>			//Used in Breadth Width Search
# define INF 0x3f3f3f3f		//Used in Dijkstra's algorithm

using namespace std;

//Struct for person's contact list
struct contacts
{
	string name;
	int weight;
};

typedef list<contacts> Contacts_list;		//Give alias for contacts_list
typedef Contacts_list::iterator list_it;	//Give alias for iterator

//Struct to hold information of each memeber
struct personType
{
	string name;					//Name of individual
	char suspect;					//Suspicous(S/N)
	int numContacts;				//Number of Contacts for each individual
	int number;
	Contacts_list listContacts;		//List for contacts list
};

class members
{
public:
	void loadMembers();		//Function loads members from text file into adjacency list
	void searchMembers(string, bool&, int&);	//Function searches for a desired member by name
	void numContacts();		//Function gives how many people a specified person has contact with
	void compareContact();	//Function indicates if they have contact with each other and how much
	void mostMessages();	//Function evaluates user who sent most messages
	void deleteContact();	//Function deletes a person from contact list
	void insertContact();	//Function inserts a person from a contact list
	void hasContact();		//Function determines if two given individuals has contact with each other
	void printContact();	//Function prints contact list of one person
	void printAllContacts();	//Function prints contact list of all persons
	void suspiciousContact();	//Function determines if individual has contact with suspicous members
	void likelyContact();		//Function prints list of determining likelyhood of a person in contact with other person
	void longestPath(int);		//Function determines longest path of messages and prints to user
	 int length(int u, int v);	//Used in longestPath(int) function
	 int minDistance(list <int> Q, int dist[]);	//Used in longestPath(int) function
	void optionsMenu();			//Function holds switch statement for program
	members();					//Default constructor

private:
	personType persons[200];	//Array holds number of persons in the graph
	int size;					//Holds number of members in array
};

members::members()
{
	size = 0;					//Initialize size to 0

}
void members::loadMembers()
{
	ifstream infile;	//Variable for ifstream
	contacts temp;		//Temp node that looks like contacts

	infile.open ("Social.dat");
	while(!infile.eof())
	{
		infile >> persons[size].name
			   >> persons[size].suspect
			   >> persons[size].numContacts;
				  persons[size].number = size;
		for(int j = 0; j < persons[size].numContacts; j++)		//Load each contacts for each member
		{
			infile >> temp.name
				   >> temp.weight;

			persons[size].listContacts.push_back(temp);			//Add to list
		}
		size++;
	}
}

void members::printAllContacts()
{
	string str;
	int space;
	cout << "Printing list of all contacts: " <<endl;
	for(int i = 0; i < size; i++)						//Loop to print all contacts and contact list
	{
		str = persons[i].name;			//For aligned columns
		space = 25 - str.length();
		cout << "Person: " << persons[i].name << setw(space)
			 << "Suspicious: " << persons[i].suspect << setw(20);
		cout << "Contact List: ";
		for (list_it p  = persons[i].listContacts.begin();  p != persons[i].listContacts.end(); p++)
		{
		cout <<  p-> name << ", ";
		}
		cout << endl;
	}
	cout << endl;
}


void members::searchMembers(string searchName, bool& found, int& pos)
{	
	found = false;		//Initialize bool variable

	for (int i = 0; i < size && found == false; i++)
	{
		if (persons[i].name == searchName)
		{
			found = true;
			pos = i;		//Once found, set pos to index location
		}
	}
}

void members::printContact()
{
	string userSearchName;		//Name to search for
	bool found = false;			//Initialize bool to false
	int pos = -1;				//Initialize pos to -1

	cout << "Enter the contact to print:  ";
	cin >> userSearchName;

	searchMembers(userSearchName,found,pos);	//Searches for name and saves position

	if(found == true)		//Prints contact if searched contact found
	{
		cout << "Person: " << persons[pos].name << setw(20) 
			 << "Suspicious: " << persons[pos].suspect << setw(20);
		cout << "Contact List: ";
		for (list_it p  = persons[pos].listContacts.begin();  p != persons[pos].listContacts.end(); p++)
		{
		 cout <<  p-> name << ", ";
		}
		cout << endl;
	}
	else		//Error message if contact not found
		cout << "The desired contact: " << userSearchName << " Does NOT exist " << endl;
}

void members::numContacts()
{
	string userSearchName;		//Name to search for
	bool found = false;			//Initialize bool to false
	int pos = -1;				//Initialize pos to -1

	cout << "Enter the name to search for:  ";
	cin >> userSearchName;

	searchMembers(userSearchName,found,pos);

	if(found == true)
		cout << persons[pos].name << " has: " << persons[pos].numContacts << " contacts" << endl;
	else cout << "Person does NOT exist" << endl;
	cout << endl;
}

void members::insertContact()
{
	string newContact;		//Variable to hold new contact name
	string searchPerson;	//Variable to search for a person
	int numMsgs;			//Variable holds number of messages sent
	contacts insertTemp;	//Creats a temporary node that looks like contacts
	bool found = false;		//Initialize found to false
	int pos = -1;			//Initialize pos to -1

	cout << "Enter the person you would like to add an additional contact: " << endl;
	cin >> searchPerson;

	searchMembers(searchPerson,found,pos);				//Searches for member
	if(found == true)
	{
		cout << "Enter the name of the new contact: " << endl;
		cin >> newContact;
	
		//String Input Validation
		while ((!cin))
		{
			cout << "You need to enter a name! Input is case sensitive!!" << endl;
			cin.clear (); //clears stored string
			cin.ignore(100, '\n'); //ignores initial values
			cin >> newContact; //stores new input into variable
		}

		cout << "Enter the number of messages sent between the person: " << endl;
		cin >> numMsgs;
		//Number Input Validation
		while (numMsgs < 0 || (!cin))
		{
			cout << "You need to a POSITIVE number!" << endl;
			cin.clear (); //clears stored string
			cin.ignore(100, '\n'); //ignores initial values
			cin >> numMsgs; //stores new input into variable
		}
		insertTemp.name = newContact;		//Set name = newContact
		insertTemp.weight = numMsgs;		//Set weight = numMsgs
		persons[pos].listContacts.push_back(insertTemp);	//Inserts onto contact list
	}
	else 
		cout << "Contact Does NOT exit!" << endl;
}

void members::deleteContact()
{
	string searchPerson;		//Variable to search
	string deleteContact;		//Variable to delete desired contact
	contacts temp;				//Creates a temp node that looks like contact
	bool found = false;			//Initialize to false
	int pos = -1;				//Initialize to -1

	cout << "Enter the the member for the contact list to edit: " << endl;
	cin >> searchPerson;

	searchMembers(searchPerson,found,pos);
	if (found == false)
		cout << searchPerson << " Does not exist" << endl;
	else
	{
		cout << endl;
		cout << "Which contact would you like to delete? " << endl;
		
		//Output list to user
		for (list_it p  = persons[pos].listContacts.begin();  p != persons[pos].listContacts.end(); p++)
		{
			cout <<  p-> name << endl;
		}			
		cin >> deleteContact;	//Takes user input

		for (list_it p  = persons[pos].listContacts.begin();  p != persons[pos].listContacts.end();)
		{
			if (p->name == deleteContact)		//If names == deleteContact then erase
			 {
				 p = persons[pos].listContacts.erase(p);
			 }
			else
				p++;		//Otherwise increment
		}
	}
}

void members::hasContact()	//Needs input validation
{
	
	string firstContact;		//Holds first contact name to compare
	string secondContact;		//Holds second contact name to compare
	bool found1 = false;		//Initialize bool variables
	bool found2 = false;
	int pos = -1;				//Initialize pos
	int sentMessages = 0;		//Initiazlize sentMessages

	cout << "Enter the First Contact: " << endl;
	cin >> firstContact;

	cout << "Enter the Second Contact: " << endl;
	cin >> secondContact;

	for(int i = 0; i < size; i++)		//Loop to find first contact
	{
		if(firstContact == persons[i].name)
		{
			found1 = true;
			pos = i;
		}

		if(found1 == true)				//Loop to traverse contact list of firstContact
		{
			for (list_it p  = persons[pos].listContacts.begin();  p != persons[pos].listContacts.end(); p++)
			{
				if(secondContact == p-> name)	//If secondContact found
				{
					sentMessages = p-> weight;	//Records number of messages
					found2 = true;		
				}
			}
		}
	}
	if(found1 == true && found2 == true)		//Prints if both names found
	{
		cout << "Yes, " << firstContact << " and " << secondContact << " have contact " << endl;
		cout << "They have sent: " << sentMessages << " messages amongst each other" << endl;
	}
	else if(found1 == false && found2 == false)		//Prints if neither names found
		cout << "No, " << firstContact << " and " << secondContact << " have NO contact " << endl;
	else
		cout << "No Relation Could be Found! " << endl;		//Prints alternate case
}

void members::mostMessages()
{
	int max = 0;			//Variable for max number of messages
	string firstSender;		//Variable to compare firstSender
	string secondSender;	//Variable to compare secondSender

	for(int i = 0; i < size; i++)	//Loop to traverse thorugh each person
	{
		persons[i];		//Loop to traverse through contact list to compare weights
		for(list_it p  = persons[i].listContacts.begin();  p != persons[i].listContacts.end(); p++)
		{
			if(p -> weight > max)			//If higher weight found 
			{
				max = p -> weight;				//Max equal to that weight
				firstSender = persons[i].name;	//Gets name of first Sender
				secondSender = p-> name;		//Gets name of second Sender
			}
		}
	}
	cout << "Top Senders: " << firstSender << " and " << secondSender << endl;
	cout << "Messages Sent: " << max << endl;
}

void members::suspiciousContact()
{
	typedef list <string> Names_list;		//Create new list to hold names
	typedef Names_list::iterator list_n;	//Create iterator
	Names_list nameList;

	bool found = false;		//Initialize bool variable
	string element;

	for(int i = 0; i < size; i++)		//Loop through array
	{
		if(persons[i].suspect == 'S')	//If Array has an S
		{
			nameList.push_back(persons[i].name);	//Add name to NameList
			for(list_it p  = persons[i].listContacts.begin();  p != persons[i].listContacts.end(); p++)		//Loop thourgh contact list
			{
				nameList.push_back(p->name);		//Add names to NameList
			}
		}
	}
	
	//Removes duplicates
	nameList.sort();
	nameList.unique();

	cout << endl;
	cout << "Persons with suspicious contact: " << endl;
	
	while(!nameList.empty())		//Prints list
	{
		element = nameList.front();
		cout << element << endl;
		nameList.pop_front();
	}
}

void members::likelyContact()
{
    int V = size;			// No. of vertices
	bool found = false;		//Initialzie variable
	int pos = -1;			//Initialize pos
	int s;					//Holds int value of pos
	string contact;			//Holds contact name user enters
	
    // Pointer to an array containing adjacency lists
    list<int> *listContacts;

    listContacts = new list<int>[V];		//Create new lsit

	// Mark all the vertices as not visited
    bool visited[100];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Create a queue for BFS
    list<int> queue;
 
    cout << "Enter the name of the contact you would like to evaluate: " << endl;
	cin >> contact;

	searchMembers(contact, found, pos);		//Search for contact
	s = pos;								//Save position into s

	// Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;
 
    cout << "Printing list from most likely to contact (top) to least likely (bottom): " << endl;
	while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << persons[s].name << endl;
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued vertex s
		//If a adjacent has not been visited, then mark it visited and enqueue it
		for (list_it i = persons[s].listContacts.begin(); i != persons[s].listContacts.end(); i++)
        {
			searchMembers(i->name, found, pos); 
            if (!visited[pos])
            {
                visited[pos] = true;
                queue.push_back(pos);
            }
        }
    }
	cout << endl;
}
/*
int members::length(int u, int v)
{
	
	bool found = false;
	int pos = -1;
	
	//Go through contact list until find node 1
	
	for (list_it j = persons[u].listContacts.begin(); j != persons[u].listContacts.end(); j++)
	{
		searchMembers(j->name, found, pos);
		if(pos == v)			//j points at person we want so can return j weight
		{
			return j -> weight;
		}
	}
	return INF;	
	
}
*/
/*
int members::minDistance(list <int> Q, int dist[])
{
	
	int min = -1;
	int pos = -1;
	// Create a list Iterator
	list<int>::iterator it;
 
	
	//check to see if 
	searchit = find(Q.begin(), Q.end(), Q);
 
	// Check if iterator points to end or not
		for (int i = 0; i < size; i++)
		{
			if (dist[i] < min)
			{
				min = dist[i];
				pos = i;
				return min;
			}
		}
	}
	else
	{
		// It points to end, it means element does not exists in list
		cout<<"'the' does not exists in list"<<std::endl;
	}
}
*/
/*
void members::longestPath(int source)
{
	list<int> Q;		//List of number of nodes we have
	int dist[100];		//Declare array for distance
	int prev[100];		//Declare array for previous node
	int V = size;		//Toal number of vertices we have
	int u = 0, v = 0, alt = 0;	//Holds minimum distance between two nodes
	bool found = false;
	int pos = -1;

	for(int v = 0; v < V; v++)	
	{
		dist[v] = INF;
		prev[v] = -1;
		Q.push_back(v);		//Add vertices to Q
	}

	dist[source] = 0;
	while(!Q.empty())
	{
		u = minDistance(Q, dist);			//Function that gets vertex from Q that has the smallest distance
		Q.remove(u);
		for(list_it i = persons[u].listContacts.begin(); i != persons[u].listContacts.end(); i++)
		{
			searchMembers(i->name, found, pos);
			v = pos;						//v knows neighbors of u
			alt = dist[u] + length(u,v);	//Function finds distance between u and v
			if(alt < dist[v])
			{
				dist[v] = alt;
				prev[v] = u;
			}
		}
	}
}
*/
void welcomeMenu()
{   
	cout << "\n\n" << endl;
	cout << "                     ------------------------------------- "  << endl;
	cout << "                    |                                     | " << endl;
	cout <<	"                    |  Nefarious NSU Cyber Intelligence   | " << endl;
	cout << "                    |           Graph Program             | " << endl;
	cout << "                    |                                     | " << endl;
	cout << "                     -------------------------------------  " << endl;
	cout << "\n\n" << endl;
	
	system("pause");
	system("cls");
}

int selectionMenu()
{
	int userOption;
	cout << "What would you like to analyze?" << endl;
	cout << "(1) Print contact list for ALL persons" << endl;
	cout << "(2) Print contact list for ONE person" << endl;
	cout << "(3) Print how many contact a specified person has" << endl;
	cout << "(4) Determine if two people have contact" << endl;
	cout << "(5) Evaluate most messages sent" << endl;
	cout << "(6) Evaluate if have suspicous contact" << endl;
	cout << "(7) Delete a person from a contact list" << endl;
	cout << "(8) Insert a person into a contact list" << endl;
	cout << "(9) Determine likelyhood of persons in contact" << endl;
	cout << "(10) Find longest message path between two given persons" << endl;
	cout << "(0) To Exit" << endl;
	cin >> userOption;
	//Number validation- ensures number input only
        while ((userOption < 0) || userOption > 11 || (!cin))
        {
            cout << "You need to enter a POSITIVE number (0-10)!" << endl;
            cin.clear (); //clears stored number
            cin.ignore(100, '\n'); //ignores initial values
            cin >> userOption; //stores new input into array
        }
	return userOption;
}

void members::optionsMenu()
{
	int choice = -1;
	int source;
	while (choice != 0)
	{
		choice = selectionMenu();
		switch(choice)
		{
		case 1: printAllContacts();
			break;
		case 2: printContact();
				system("pause");
				system("cls");
			break;
		case 3: numContacts();
				system("pause");
				system("cls");
			break;
		case 4: hasContact();
				system("pause");
				system("cls");
			break;
		case 5: mostMessages();
				system("pause");
				system("cls");
			break;
		case 6: suspiciousContact();
				system("pause");
				system("cls");
			break;
		case 7: deleteContact();
				cout << endl;
				printAllContacts();
				system("pause");
				system("cls");
			break;
		case 8: insertContact();
				cout << endl;
				printAllContacts();
				system("pause");
				system("cls");
			break;
		case 9: likelyContact();
			break;
		case 10: cout << "Sorry, Code was not implented" << endl;
			break;
		case 0: break;
		default: cout << "Please enter a valid entry" << endl;
		}
	}
}

int main()
{
	members connections;
	welcomeMenu();
	connections.loadMembers();
	connections.optionsMenu();
	
	system("pause");

	return 0;
}