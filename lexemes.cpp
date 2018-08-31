#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

class grammar 
{
	
private:
	int c;
	int size;
	char bigWord[200];
public:
		grammar();
		void load_Array();
		void print_Array();
		bool word_check();
		bool check_letters(char);
		bool check_par();
		bool check_operations();
		bool check_lower();
		char getCharAry(int pos);
};

grammar::grammar()
{
	size = 0;	
}

void grammar::load_Array()
{
	string word;
	cout << endl;
	cout << " Please input a word to check: \n";
	//cin >> word;
	//cout << endl;
	word = "jhu*)";

	//int size = 0; // this access the counter the amount of elements in the array. //Does NOT need to be redeclared
	//inputing the string into the array
	for(int i = 0; i<word.length(); i++)
	{
		bigWord[i] = word.at(i);
		size++;
	}
}

void grammar::print_Array()
{
	
	cout << " The word you inputed was: " << endl;
	for(int i = 0; i < size; i++){
	cout << bigWord[i];
	}
	cout << endl;
}

/***************************
Need a function to get a single character of the array
There is no built in C++ function for this so we'll make our own
*******************************/

char grammar::getCharAry(int pos)
{
	char currentChar;				//Variable holds current character
	currentChar = bigWord[pos];		//Gets the current character based on position
	return currentChar;				//Returns current character
}

//Now we want to go character by character to see if it passes the word check

bool grammar::word_check()
{	
	bool checkLetters = false;
	bool checkPar = false;
	bool checkOperations = false;
	bool checkLower = false;

	/*checkLetters = check_letters();		Can't lump these all together without a loop
	checkPar = check_par();
	checkOperations = check_operations();
	checkLower = check_lower();*/

	int pos = 0;
	char current;
	bool analyzeLexme = false;
	
	//while (!check_letters() == false)		Omited this: Loop does not serve a good purpose
	while(pos < size)			//Loop until get to end of the word
	{
		current = getCharAry(pos);		//Variable holds current character

		analyzeLexme = check_letters(current);

		if(analyzeLexme == false)
			cout << current << "	NOT VALID!" << endl;
		
		pos++;
	};

	return true;		//I only returned true for testing purposes

		/*if	(checkLetters == true && checkPar == true &&		//Can't pack into all if statement since
			checkOperations == true && checkLower == true)			//We need to check each letter
		{															//Needs to be nested if statement
			cout << endl;				
			cout << " YASSSSSSSSSS!!!!!!!! " << endl;
		}
		else 
		{
			cout << endl;
			cout << " NOO NOOO NOO !!!!! " << endl;
		}*/
}

bool grammar::check_letters(char check)
{
	char c = check;	
	if(islower(c))
	{
		cout << c << "		letter. " << endl;
		return true;
	}
	else
	{
		return false;
	}
}
/*
bool grammar::check_par()
{
	c = getchar();
	putchar
	while (c != '(' | ')' )
	{
		if(islower(c))
		{
			cout << endl;
			cout << putchar(c) << "\t Is a left or right Parenthesis. " << endl;
			return true;
		}
		else
		{
			cout << endl;
			cout  << putchar(c) << "\t NOT VALID!!! " << endl;
			return false;
		}
	}
}
bool grammar::check_symbols()
{
	char c = getchar();
	putchar(c);

	while( c != '+' | '*' )
	{
		if(islower(c))
		{
			cout << endl;
			cout << putchar(c) << "\t Is a symbol. " << endl;
			return true;
		}
		else
		{
			cout << endl;
			cout  << putchar(c) << "\t NOT VALID!!! " << endl;
			return false;
		}
	}
}
*/
int main()
{
	grammar check;  //object

	//ask the user to input a word to check
	cout << " Please input a word or symbol using";
	cout << " +, *, (),  " << endl;
	
	check.load_Array();
	check.print_Array();
	check.word_check();


	//set up input
	/*if(! check.word())
	{
		cout << " NO! " << endl;
	}
	else
	{
		cout << " YES!!! " << endl;
	}*/
	system ("pause");
	return 0;
}