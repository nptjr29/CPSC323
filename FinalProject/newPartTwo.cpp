#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

const int ROW = 23;
const int COL = 30;
bool check[5] = { false };

// Process input file, remove all spaces and carriage return 
// from file and store it in a string
string processInputFile()
{
	fstream ProgramFileInput;
	ProgramFileInput.open("finalv2.txt", ios_base::in);
	if (!ProgramFileInput) {
		cout << "Fail to open program file." << endl;
		return 0;
	}

	string dummyVar = "";
	string input = "";

	while (ProgramFileInput >> dummyVar) 
	{
		if (dummyVar == "PROGRAM") 
		{
			dummyVar = "p";
			check[0] = true;
		}
		else if (dummyVar == "BEGIN") 
		{
			dummyVar = "b";
			check[1] = true;
		}
		else if (dummyVar == "INTEGER") 
		{
			dummyVar = "i";
			check[2] = true;
		}
		else if (dummyVar == "PRINT") 
		{
			dummyVar = "c";
			check[3] = true;
		}
		else if (dummyVar == "END.") 
		{
			dummyVar = "$";
			check[4] = true;
		}
		input += dummyVar;
	}
	return input;	
}

bool checkKeyword()
{
	if (!check[0])
	{
		cout << "PROGRAM is expected. Program is rejected." << endl;
		return false;
	}
	if (!check[1])
	{
		cout << "BEGIN is expected. Program is rejected." << endl;
		return false;
	}
	if (!check[2])
	{
		cout << "INTEGER is expected. Program is rejected." << endl;
		return false;
	}
	if (!check[4])
	{
		cout << "END. is expected. Program is rejected." << endl;
		return false;
	}
	return true;
}

// Converts a character to a string
string charToString(const char& a)
{
	string str = "";
	str += a;
	return str;
}

// Returns the string found at table[rowVal, colVal]; returns "" if not found
string findInTable(const char& rowVal, const char& colVal, const string table[ROW][COL])
{
	int i = 0, j = 0;
	while (i < ROW)
	{
		if (table[i][0] == charToString(rowVal))
		{
			while (j < COL)
			{
				if (table[0][j] == charToString(colVal))
					return table[i][j];
				else
					++j;
			}
			return "";
		}
		++i;
	}
	return "";
}

// Prints stack without removing items
void printStack(stack<char>& myStack)
{
	if (myStack.empty())
		cout << "Stack is empty.";
	else
	{
		int size = myStack.size();
		char * arr = new char[size + 1];
		cout << "Stack is: ";
		for (int i = 0; i < size; ++i)
		{
			arr[i] = myStack.top();
			myStack.pop();
		}
		for (int i = size - 1; i >= 0; --i)
		{
			myStack.push(arr[i]);
			cout << arr[i];
		}
		delete[] arr;
	}
	cout << endl;
}

// Populate table with data in the text file
void populateTable(string table[ROW][COL])
{
	fstream TableFileInput;
	TableFileInput.open("parsing_table.txt", ios_base::in);
	if (!TableFileInput) {
		cout << "Fail to open file" << endl;
		return;
	}
	string s;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			TableFileInput >> s;
			table[i][j] = s;

		}
	}

}

int main()
{
	string input = processInputFile();
	string table[ROW][COL];
	populateTable(table);
	//Testing parse_table
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << setw(5) << table[i][j];
		}
		cout << endl;
	}
	cout << "String is : " << input << endl;

	// Check if any of the keyword is missing from the grammar
	if (!checkKeyword())
	{
		return 0;
	}
	else
	{
		string tmp = "";
		stack<char> myStack;

		myStack.push((table[1][0])[0]);	//push X
		int i = 0;
		bool done = false;
		while (i < input.length() && !done)
		{
			char top = myStack.top();
			myStack.pop();
			if (top != input[i])	// no match found
			{
				tmp = findInTable(top, input[i], table);
				if (tmp == "!" || tmp == "")	//empty cell or invalid symbol
				{
					if (tmp == "!")
					{
						cout << "\nIllegal expression. Program is rejected." << endl;
					}
					else
					{
						cout << "\nUnknown identifier. Program is rejected." << endl;
					}
					
					printStack(myStack);
					cout << "Trigger: " << tmp << " at [" << top << ", " << input[i] << "]\n";
					done = true;
				}
				else if (tmp != "&")
				{
					for (int k = tmp.length() - 1; k >= 0; --k)
						myStack.push(tmp[k]);		//push in reverse
					printStack(myStack);			//print stack after pushing
				}
				tmp = "";	//reset tmp
			}
			else	//found a match
			{
				printStack(myStack);		//print stack after a match
				if (input[i] == '$')
				{
					cout << "\nProgram is accepted." << endl;
					done = true;
				}
				else
					++i;
			}
		}
	}

		
	//system("Pause");
	return 0;
}
