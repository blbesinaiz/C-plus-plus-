

/*Asks the user for the name of an input file and a "key"
Encrypts the file using the key and the xor function. (Note: The program should handle all standard alphanumeric characters.)
Your program should save the results of the encryption into a new file with the same base name, but with a ".xor" file extension.
Program should also provide an option to decrypt a given file*/

#include <iostream>
#include <iomanip>	// Access manipulators
#include <string>
#include <fstream>  // Access file i/o functions
#include <sstream>

using namespace std;

string loadMessage()		//Function loads message into an array
{
	ifstream inData;    // Link to output file
    string infilename;  // Output text file name
    ofstream outData;	// Link to output file

	// Prompt user for output file name
    cout << "Enter a file name: ";
    cin >> infilename;

	// Open input file
    inData.open(infilename.c_str());

	ifstream file(infilename.c_str());		//Gets each character from file
    stringstream buffer;					//Stores into string stream buffer
		
    buffer << file.rdbuf();					//Buffer function form string stream libary
    string messageString = buffer.str();	//Stores string from buffer into variable messageString
    cout << messageString << endl;
	return messageString;					//Returns string obtained from file
}

string encryptDecrypt(string toEncrypt) {
    
    char key = 'BB';
	string output = toEncrypt;		//Initialize output to string to encrypt
    
    for (int i = 0; i < toEncrypt.size(); i++)		//Loops until all variables of string encrypted
        output[i] = toEncrypt[i] ^ key;				//Encrypts character by character
    
    return output;
}

int main()
{
	string encrypted;	//Variable holds encrypted word
	string decrypted;	//Variable holds decryption of encrypted word
	string messageString;

	string toEncrypt = loadMessage();

	cout << "Encrypting: " << toEncrypt << endl;
	encrypted = encryptDecrypt(toEncrypt);			//Pass string to be encrypt and then gets encrypted
    cout << "Encrypted:" << encrypted << "\n\n";		//Outpus encrypted string
    
	cout << "Decrypting: " << encrypted << endl;
    decrypted = encryptDecrypt(encrypted);			//pass encrypted variable again to decrypted
    cout << "Decrypted:" << decrypted << "\n";		//Output decrypted string
    
	system("pause");
    return 0;
}
