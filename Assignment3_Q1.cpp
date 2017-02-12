#include <iostream>
#include <string>
using namespace std;

// Checks if array arr contains string s
bool in_array(const string& s, string arr[], int size);

// Checks if a string s is a number
bool is_number(const string& s);

// global constant used for formatting output
const int W = 12;

int main()
{
	//Given the arrays
	string reservedWords[4] = { "cout<<", "for", "int", "while" };
	string special[8] = { "=", "*", "-", ";", "(", ")", "<=", "+" };

	char option = 'y';
	while (option == 'y' || option =='Y')
	{
		// Read a statement
		cout << "Enter a statement: ";
		string statement;
		getline(cin, statement);
		cout << endl;

		// Process the statement
		string temp = "";
		for (size_t i = 0; i < statement.length(); i++)
		{			
			if (statement[i] != ' ')
			{
				temp += statement[i];	// store each token into temp
			}
			else
			{
				//if token is a reserved word
				if (in_array(temp, reservedWords, (sizeof(reservedWords) / sizeof(*reservedWords))))
				{
					cout.width(W); 
					cout << left << temp << ": " << "reserved word" << endl;
				}					
				//else if token is a special symbol
				else if (in_array(temp, special, (sizeof(special) / sizeof(*special))))
				{
					cout.width(W); 
					cout << left << temp << ": " << "special symbol" << endl;
				}
				//else if the first character of token is a number
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
				//else token is an identifer
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

bool in_array(const string& s, string arr[], int size)
{ 
	for (int i = 0; i < size; ++i)
	{
		if (s.compare(arr[i]) == 0)
			return true;
	}
	return false;
}

bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) 
		++it;
	return (!s.empty() && it == s.end());
}