#include <iostream>
#include <string>
using namespace std;

// Check if string s is in an array arr
bool is_in_array(const string& s, char * arr, int row, int col);

// Checks if a string s is a number
bool is_number(const string& s);

// global constant used for formatting output
const int W = 12;

// Begin main() program
int main()
{
	// Given the following arrays
	char reservedWords[4][10] = { "cout<<", "for", "int", "while" };
	char special[8][3] = { "=", "*", "-", ";", "(", ")", "<=", "+" };

	// Option to continue or not
	char option = 'y';

	while (option == 'y' || option =='Y')
	{
		// Read a statement
		cout << "Enter a statement: ";
		string statement;
		getline(cin, statement);
		cout << endl;

		// Process the statement; everytime we encounter a space, store the token
		string temp = "";
		for (size_t i = 0; i < statement.length(); i++)
		{			
			if (statement[i] != ' ')
			{
				temp += statement[i];	// store token
			}
			else
			{
				//if token is a reserved word
				if (is_in_array(temp, (char *)reservedWords, 4, 10))
				{
					cout.width(W); 
					cout << left << temp << ": " << "reserved word" << endl;
				}					
				//if token is a special symbol
				else if (is_in_array(temp, (char *)special, 8, 3))
				{
					cout.width(W); 
					cout << left << temp << ": " << "special symbol" << endl;
				}
				//if the first character of token is a number
				else if (isdigit(temp[0]))
				{
					//token is a number
					if (is_number(temp))
					{
						cout.width(W); 
						cout << left << temp << ": " << "number" << endl;
					}
					//token is not an identifier
					else
					{
						cout.width(W); 
						cout << left << temp << ": " << "not identifier" << endl;
					}
				}
				//token is an identifer
				else
				{
					cout.width(W); 
					cout << left << temp << ": " << "identifier" << endl;
				}
				
				temp = "";	// Reset token
			}	
		}

		cout << endl;
		cout << "CONTINUE (y/n)? ";
		cin >> option;
		cin.ignore();
		cout << endl;

	}

	cout << endl;
	system("Pause");
	return 0;
}
// Ends of main() program

// Checks if a string s is in an array arr
bool is_in_array(const string& s, char * arr, int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		int j = 0;
		string temp = "";
		while (*((arr + i*col) + j) != '\0')
		{
			temp += *((arr + i*col) + j);
			++j;
		}
		if (s.compare(temp) == 0)
			return true;
	}
	return false;
}

// Checks if a string s is a number
bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) 
		++it;
	return (!s.empty() && it == s.end());
}
