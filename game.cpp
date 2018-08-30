/************************************************************************
Brianna Besinaiz
CSC 361
1/15/17
Program Title: Rock-Paper-Scissors (RPS)
Program Description: Program mimicks the game RPS against a computer.
**************************************************************************/

#include <iostream>		//input,output
#include <string>
#include <locale>		//toupper
#include <iomanip>		//setw
#include <time.h>		//srand, rand
#include <cstdlib>		//system("pause", "cls")

using namespace std;

int titleScreen ();				//Function brings up title screen to. Records user response and returns the response
void gameSetup(string&, int&);	//Function ask user for user name and max points to play
void gamePlay(int&, int&);		//Function ask user for RPS selection and generates computers choice
string numConversion(int);		//Function converts number back to Rock, Paper, Scissor word equivalent
void roundResults(int&, int&, int&, int&, string);	//Function primarily shows output of each round result
void mainGame();				//Function cotains all other functions to play RPS game

int titleScreen ()
{
	int userPick;		//Variable holds user response

	cout << "\n\n\n\n			********************************" << endl;
	cout << "			 Welcome to Rock-Paper-Scissors " << endl;
	cout << "			*********************************\n\n\n" << endl;
	system("pause");
	system ("cls");

	cout << "\nPlease Enter a selection: " << endl;		//Ask user to play new game or to end
	cout << "(1) Play a new game" << endl;
	cout << "(2) Call it Quits" << endl;
	cin >> userPick;

	system("cls");
	return userPick;		//Returns selection
}

void gameSetup(string& userName, int& maxPoints)
{
	cout << "\nTo start, please enter your user name: " <<endl;		//Set user name
	cin >> userName;

	cout << "\nTo setup the game, please enter the max number of points to win (Greater than 5): " << endl;		//Set max Points to win
	cin >> maxPoints;
	while (maxPoints < 5 || (!cin))		//Number Input Validation
	{
		cout << "You need to a number 5 OR GREATER" << endl;
		cin.clear ();					//clears stored string
		cin.ignore(100, '\n');			//ignores initial values
		cin >> maxPoints;				//stores new input into variable
	}
	//Game Rules
	cout << "\n\nGeneral Rules: " << endl;
	cout << "We will play the game of Rock-Paper-Scissors until either one of us reaches [" << maxPoints << "] points" <<endl;
	cout << "Points will be awarded as follows: " <<endl;
	cout << "	-If a rock and scissors are formed, the rock wins, because a rock can smash scissors." << endl;
	cout << "	-If scissors and paper are formed, the scissors win, because scissors can cut paper. " << endl;
	cout << "	-If paper and a rock are formed, the paper wins, because a sheet of paper can cover a rock. " << endl;
	cout << "	**The winner of a round earns one point; if it is a tie, no one earns a point for that round.** " << endl;
	
	cout << "\n\nGame setup SUCCESSFUL. I await to play you on the next screen -->\n\n\n" << endl;
	system("pause");
	system("cls");
}

void gamePlay(int& userChoice, int& compChoice)
{
	char userOption;		//Records user selection
	
	cout <<"\nRock...Paper...Scissors...SHOOT!" << endl;
	cout << "\nEnter one of the following: " <<endl;	//User picks option
	cout << "(R) Rock" <<endl;
	cout << "(P) Paper" <<endl;
	cout << "(S) Scissors" <<endl;
	cin >> userOption;
	userOption = toupper(userOption);		//Converts it to capital letter
	
	switch(userOption){					//Convert character into number
		case 'R': userChoice = 1;
			break;
		case 'P': userChoice = 2;
			break;
		case 'S': userChoice = 3;
			break;
	}
	
	//Computer generated choice
	int compGenerate;		//holds computer generated number

	srand (time(NULL));		//seed the number
	rand () % 1000;
	compChoice = (rand() % 3) + 1;		//generate choice (1-3)
	system("cls");
}

string numConversion(int option)
{
	if(option == 1)		//convets option back to rock, paper, or scissors
		return "Rock";
	else if(option == 2)
		return "Paper";
	else if(option == 3)
		return "Scissors";
}

void roundResults(int& userChoice, int& compChoice, int& userPoints, int& compPoints, string userName)
{
	int round = 1;		//variable to count round

	cout << "\nROUND: " << round << setw(15) << userName << " vs Computer" << endl;		//Heading
	cout << "-----------------------------------\n" << endl;

	if((userChoice == 1 && compChoice == 3) || (userChoice == 2 && compChoice == 1) ||		//Determines who wins
	   (userChoice == 3 && compChoice == 2))
	{
		cout << userName << " Wins!!\n" << endl;
		userPoints++;		//Increments user points
	}
	else if (userChoice == compChoice)
	{
		cout << "Ahh, we have a darn Tie... \n" << endl;
	}

	else
	{
		cout << "I WIN Sucka \n" << endl;
		compPoints++;		//Increments computer points
	}
	
	cout << userName << " Chose: " << numConversion(userChoice) << setw(20)		//Shows what was chosen
	     << "I Chose: " << numConversion(compChoice) << endl;
	round++;

	cout << "\n****************SCORE******************* " << endl;		//Score board
	cout << userName << " Points: " << userPoints 
		 << setw(20) << "My Points: " << compPoints << endl;
	cout << endl;

	system("pause");
	system("cls");
}

void mainGame()
{
	int gameOption = 0;		//Variable to hold choice to play again or quit
	string userName;		//Variable to hold userName
	int maxPoints = -1, userChoice = -1, compChoice = -1;	//Initialize point and choice values

	while(gameOption != 2)		//Loops until user decides to quit
	{
		int userPoints = 0, compPoints = 0;		//Initialize player points

		gameOption = titleScreen();				//Ask user to play or quit
		if(gameOption == 1)
		{
			gameSetup(userName, maxPoints);			//Gets user Name and sets max points
		
			while(userPoints < maxPoints && compPoints < maxPoints)		//Loops until max points reached
			{
				gamePlay(userChoice, compChoice);
				roundResults(userChoice, compChoice, userPoints, compPoints, userName);		
			};
			system("cls");

			//Determine Winner
			if(userPoints > compPoints)
			{
				cout << "\nWow " << userName << ", I'm surprised you beat me. I would love a rematch!" << endl;
				cout << "\nPlease choose: \n(1) To Replay \n(2) To quit" << endl;
			}

			else if(userPoints < compPoints)
			{
				cout << "\nI beat you SIMPLETON!!" << endl;
				cout << "\nPlease choose: \n(1) To TRY regaining your dignity \n(2) To Give up" << endl;
			}
			cin >> gameOption;
			system("cls");
		}
		else if (gameOption == 2)
			cout << "Sorry to see you leave...maybe next time we'll play :(" << endl;
	
	userPoints = 0;		//Reinitialize points to 0
	compPoints = 0;
	}
}

int main ()
{

	mainGame();		//Calls game into action

	system("pause");
	return 0;
}