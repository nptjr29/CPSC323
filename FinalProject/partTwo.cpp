#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
using namespace std;

const int ROW = 24;
const int COL = 31;

// Process input file, remove all spaces and carriage return 
// from file and store it in a string
string processInputFile()
{
	map<string, string> myMap;
	map<string, string>::iterator it = myMap.begin();
	myMap.insert(it, pair<string, string>("PROGRAM", "p"));
	myMap.insert(it, pair<string, string>("BEGIN", "b"));
	myMap.insert(it, pair<string, string>("END.", "$"));
	myMap.insert(it, pair<string, string>("INTEGER", "i"));
	myMap.insert(it, pair<string, string>("PRINT", "c"));

	// Declare the I/O streams
	ifstream infile;

	// Declare the I/O file names
	string inFilename = "finalv2.txt";

	// Declare the strings needed to process the I/O
	string temp, token, str;

	// Open input file to read from
	infile.open(inFilename.c_str());

	// If cannot open input file
	if (infile.fail()) {
		cout << "\nInvaild file name.\n";
		return 0;
	}

	// Start processing the input file
	if (infile.is_open())
	{
		while (getline(infile, temp))	// loop till the end of file
		{
			if (myMap.find(temp) != myMap.end())
			{
				str += myMap.find(temp)->second;
			}
			else
			{
				for (int i = 0; i < temp.length(); ++i)
				{
					if (temp[i] != ' ')
					{
						token += temp[i];
					}
					else
					{
						if (myMap.find(token) != myMap.end())
							str += myMap.find(token)->second;
						else
							str += token;
						token = "";
					}
				}
			}
		}
	}
	return str;
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
void populateTable(string parseTable[ROW][COL])
{
	// Declare the I/O streams
	ifstream infile;

	// Declare the I/O file names
	string inFilename = "parsing_table.txt";

	// Declare the strings needed to process the I/O
	string str, token;
	int rowNum = 0;
	int colNum = 0;

	// Open input file to read from
	infile.open(inFilename.c_str());

	// If cannot open input file
	if (infile.fail()) {
		cout << "\nInvaild file name.\n";
		return;
	}

	// Start processing the input file
	if (infile.is_open())
	{
		while (getline(infile, str))	// loop till the end of file
		{
			for (int i = 0; i < str.length(); ++i)
			{
				if (str[i] != '\t')
				{
					token += str[i];
				}
				else
				{
					parseTable[rowNum][colNum] = token;
					colNum++;
					token = "";
				}
			}
			rowNum++;
			colNum = 0;
		}
	}
}

int main()
{
	string input = processInputFile();
	string parseTable[ROW][COL];
	populateTable(parseTable);
	//Testing parse_table
	//for (int i = 0; i < ROW; ++i)
	//{
	//	for (int j = 0; j < COL; ++j)
	//	{
	//		cout << parseTable[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	cout << "String is : " << input << endl;
	string tmp = "";
	stack<char> myStack;
	//myStack.push('$');		//push $
	myStack.push((parseTable[1][0])[0]);	//push X
	int i = 0;
	bool done = false;
	while (i < input.length() && !done)
	{
		char top = myStack.top();
		myStack.pop();
		if (top != input[i])	// no match found
		{
			tmp = findInTable(top, input[i], parseTable);
			if (tmp == "!" || tmp == "")	//empty cell or invalid symbol
			{
				cout << "\nStatement is rejected." << endl;
				printStack(myStack);
				cout << "Cell is at [" << top << ", " << input[i] << "]\n";
				done = true;
			}
			else if (tmp != "&" && tmp != "!")
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
				cout << "\nStatement is accepted." << endl;
				done = true;
			}
			else
				++i;
		}
	}
	
	system("Pause");
	return 0;
}
