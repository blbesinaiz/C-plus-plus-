/*********************************************************
Brianna Besinaiz
CSC 361
2/1/18
Program Title: Phone Number Verification
Program Description: This program verifies if a US 
					 phone number is valid
**********************************************************/

#include <iostream>
#include <string>

using namespace std;

class usPhone
{
public:
	void loadNumber();		//Function loads phone number from user
	void printNumber();		//Function prints loaded number
	bool checkLength();		//Function checks to length of phone number for validity
	bool checkFormat();		//Function checks to make sure phone number has proper symbols
	bool checkDigits();		//Function checks phone number for integers
	bool checkZeroDigit();	//Function checks if 0 is 1st digit in Area code or Extension
	bool numEvaluation();	//Function calls in all functions to evaluate phone number

private:
	string phoneNumber;		//Holds variable of phone number
};

void usPhone::loadNumber()
{
	
	//Enter in a phone number
	cout << "Please enter a phone number:" << endl;		//Prompts user
    cin >> phoneNumber;		//Saves input into phoneNumber
}

void usPhone::printNumber()
{
	//Print phone number
	cout << "\n\nPhone Number: " << phoneNumber << endl;
}

bool usPhone::checkLength()
{
	int length;							//variable holds length of phone number
	length = phoneNumber.length();		//Get length of phone number

	if(length == 12)			//number length for (###)###-####
		return true;		

	else if(length == 13)		//number length for ###-###-####
		return true;

	else
		return false;
}

bool usPhone::checkFormat()			//Don't need to be bool
{
	char secondParen;			//Variable for )
	char firstSeperator;		//Variabe for first occurece of - or . in number
	char secondSeperator;		//Variable for second occurence of - or . in number
	bool find = false;			//Variable to find symbols

	if(phoneNumber.front() == '(')		//Conditional for number with (   )
	{
		secondParen = phoneNumber.at(4);	//find = true if ) in correct spot
		if(secondParen == ')')
		{
			find = true;
		}
		else
			return false;
		if(find == true)
		{
			secondSeperator = phoneNumber.at(8);	//Returns ture if - in right spot
			if(secondSeperator == '-')
			{
				return true;
			}
			else
				return false;
		}
	}

	else if(phoneNumber.front() > 48 || phoneNumber.front() <= 57)		//Conditional for number with - or .
	{
		firstSeperator = phoneNumber.at(3);			//Stores characters at locations
		secondSeperator = phoneNumber.at(7);
		if((firstSeperator == '-' && secondSeperator == '-') ||		//Checks to make sure - of . in right place
			(firstSeperator == '.' && secondSeperator == '.'))
		{
			return true;
		}
		else
			return false;
	}

	else
		return false;
}


bool usPhone::checkDigits()
{
	int length;					//Variable to hold length of number
	char digit;					//Variable to hold digit value
	bool digitCheck = false;	//Variable to hold flag of whether digit is an int or not

	if(phoneNumber.front() == '(')		//Erases seperator symbols from (   ) number
	{
		phoneNumber.erase(0,1);
		phoneNumber.erase(3,1);
		phoneNumber.erase(6,1);
	}

	else if(phoneNumber.front() > 48 || phoneNumber.front() <= 57)		//Erases seperator symbols from number
	{
		phoneNumber.erase(3,1);
		phoneNumber.erase(6,1);
	}

	length = phoneNumber.length();		//Records lenth of string

	for(int i = 0; i < length; i++)		//For loop cycles through each character to determine if int or not
	{
		digit = phoneNumber.at(i);
		if(digit >= 48 && digit <=57)
		{
			digitCheck = true;
		}
		else
		{
			digitCheck = false;
			break;
		}
	}

	if(digitCheck == true)
	{
		return true;
	}
	else
		return false;
}

bool usPhone::checkZeroDigit()
{
	char areaDigit1;		//Variable holds value of first digit of area code
	char extensionDigit1;	//Variable holds value of second digit of area code

	areaDigit1 = phoneNumber.at(0);			//Get value of first digit of area
	extensionDigit1 = phoneNumber.at(3);	//Gets value of first digit of extension

	if(areaDigit1 != 48 && extensionDigit1 != 48)		//Checks to make sure not 0
	{
		return true;
	}

	else
		return false;
}

bool usPhone::numEvaluation()
{
	bool valid = false;		//Variable holds flag if phone number meets all the conditionals

	if(checkLength() == true)
	{
		if(checkFormat() == true)
		{
			if(checkDigits() == true)
			{
				if(checkZeroDigit() == true)
				{
					valid = true;
				}
				else
					valid = false;
			}
			else 
				valid = false;
		} else 
			valid = false;
	}
	else 
		valid = false;
	
	return valid;
}

int main()
{
	char response;			//Variable holds user response to continue or terminate loop
	char upper = ' ';				//Variable to hold conversion of response to upper case
	bool number = false;	//Flag to see if number met all the conditionals
	usPhone	phone;			//Object of usPhone
	
	cout << "Welcome to the Phone Number Format Checker\n" << endl;
	while(upper != 'N')
	{

		phone.loadNumber();		//Load Number
		phone.printNumber();	//Display entered number

		if(phone.numEvaluation() == true)	//Conditional if phone number in correct format
		{
			cout << "Yes: This is a valid US Phone Number" << endl;
		}

		else if(phone.numEvaluation() == false)		//Conditional if phone number invalid
		{
			cout << "No: This is NOT a valid US Phone Number" << endl;
		}
		
		cout << "\n\nWould you like to try phone number?" << endl;		//Prompts user to enter another number or quit
		cout << "(Y)es to continue" << endl;
		cout << "(N)o to Exit" << endl;
		cin >> response;

		upper = toupper(response);
		system("cls");

	};

	system("pause");
	return 0;
}