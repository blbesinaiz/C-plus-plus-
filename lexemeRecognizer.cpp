/***********************************************************************
Brianna Besinaiz
CSC 361
2/22/18
Program Title: Lexeme Recognizer
Program Description: This program takes in a string and determines if it
					matches the BNF format:
					id_operator_id_operator..._id
************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>		//setw

using namespace std;

class lexeme
{
public:
	void loadString();				//Gets string of input from user
	void printString();				//Prints string entered
	bool checkLetters(char);		//Checks character to for lower case letter
	bool checkOperators(char);		//Checks character for + or * operator
	bool checkParentheses(char);	//Checks character for ( or )
	char getChar();					//Get char from string at current position
	bool Recognizer();					//Contains if statements to determine if lexeme valid
	lexeme();

private:
	string S;				//Varibable holds string input from user
	int pos;				//Variable keeps track of position in string
};

lexeme::lexeme()
{
	pos = 0;
}

void lexeme::loadString()
{
	cout << "Please enter in a string to analyze: " << endl;
	cin >> S;	
}

void lexeme::printString()
{
	cout << "The sentenced entered: " << S << '\n' << endl;
}


bool lexeme::checkLetters(char c)
{
	if (islower(c))		//Checks to see if lower case letter a...z
			return true;
	else
		return false;
}

bool lexeme::checkOperators(char c)
{
	if ((c == '+') || (c == '-') ||  (c == '*') || (c == '/'))		//Checks to see if + or *
		return true;
	else
		return false;
}


char lexeme::getChar()
{
	char current;	//Variable character value of current position

	current = S.at(pos);		//Set current = to character in string

	return current;

}

bool lexeme::Recognizer()
{
	char checkC;			//Variable holds current character to be anlyzed
		
	checkC = getChar();
	
	if((checkLetters(checkC) == true) && (pos == (S.length() - 1)))
	{
		return true;
	}
	else if(checkLetters(checkC) == true)
	{
		pos++;
		checkC = getChar();
		if(checkOperators(checkC) == true)
		{
			pos++;
			Recognizer();
		}
	}
	else
		return false;
}
	
	
int main()
{
	lexeme analyzer;

	analyzer.loadString();
	analyzer.printString();
	
	if(analyzer.Recognizer() == true)
		cout << "S is a valid sentence in this grammar" << endl;
	else
		cout << "S is not a valid sentence in this grammar" << endl;

	system("pause");

	return 0;       
}