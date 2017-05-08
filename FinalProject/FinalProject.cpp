/*
	Nguyen, Hympert		hympert@csu.fullerton.edu
	Nguyen, Thao		tnguyen29@csu.fullerton.edu
	April 18, 2017
	CPSC 323 - FINAL PROJECT

	Part I Description: Takes an input file "finalv1.txt",
	removes all the comment lines, blank lines, and extra blank spaces,
	leaves one space before and after each token, and copies the new
	version to the output file "finalv2.txt".

	Part II Description: Takes the input file "finalv2.txt" and checks
	whether the grammar is correct for that file. If the grammar is
	wrong, prints out what is wrong with it, i.e. if something is 
	missing, or some word is mispelled.

	Part III Description: If the grammar is correct (as stated in 
	part II, translates the program in "finalv2.txt" into C++ language
	and outputs the translation to "finalv3.cpp"
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <map>
using namespace std;
const int ROW = 23;
const int COL = 30;
bool check[10] = { false };

/*************************************************************************************************/
/*                                                                                               */
/*-----------------------------------------BEGINS Part I-----------------------------------------*/
/*                                                                                               */
/*************************************************************************************************/
//return true if there are 2 consecutive spaces
bool bothAreSpaces(char lhs, char rhs)
{
	return ((lhs == rhs) && ((lhs == ' ') || (lhs == '\t')))
		|| ((lhs == '\t') && (rhs == ' '))
		|| ((lhs == ' ') && (rhs == '\t'));
}

string removeComments(const string& str, bool& comment)
{
	int n = str.length();
	string res;		// result string

	for (int i = 0; i < n; i++)
	{
		// If comment is on, then check for end of it
		if (comment == true && str[i] == '/' && str[i + 1] == '/')
		{
			comment = false;
			i++;
		}
		// If this character is in a comment, ignore it
		else if (comment)
			continue;

		// Check for beginning of comments and set the approproate flags
		else if (str[i] == '/' && str[i + 1] == '/')
		{
			comment = true;
			i++;
		}

		// If current character is a non-comment character, append it to result string
		else
			res += str[i];
	}
	return res;
}

void removeExtraSpaces(string &str)
{
	// remove leading blank spaces
	size_t p = str.find_first_not_of(" \t");
	str.erase(0, p);

	// remove extra blank spaces inside the string
	string::iterator i = unique(str.begin(), str.end(), bothAreSpaces);
	str.erase(i, str.end());
}

bool isOperand(char & a)
{
	return (isalnum(a) || a == '_');
}

// Add space before and after each token
void addSpaceToken(string & str)
{
	int i = 1;
	while (i < str.length())
	{
		// if we found an operator, excluding '.' since 
		// "END." does not have space in between
		if (!isOperand(str[i]) && str[i] != '.')
		{
			// we insert space before and after it
			str.insert(i, " ");
			str.insert(i + 2, " ");
			i += 2;
		}
		++i;
	}
}

// partOne function
void partOne()
{
	// Declare the I/O streams
	ifstream infile;
	ofstream outfile;

	// Declare the I/O file names
	string inFilename = "finalv1.txt";
	string outFilename = "finalv2.txt";

	// Declare the strings needed to process the I/O
	string str, tempStr;

	// Open input file to read from
	infile.open(inFilename.c_str());

	// If cannot open input file
	if (infile.fail()) {
		cout << "\nInvaild file name.\n";
		return;
	}

	// Open output file to write to
	outfile.open(outFilename.c_str());

	// Start processing the input file
	if (infile.is_open())
	{
		cout << "Printing out finalv2.txt" << endl << endl;
		// Flags to indicate that comments have started or not.
		bool comment = false;

		while (getline(infile, tempStr))	// loop till the end of file
		{
			// remove comments from string
			str = removeComments(tempStr, comment);

			// add spaces before and after each token
			addSpaceToken(str);

			// remove extra spaces
			removeExtraSpaces(str);

			// remove blank lines
			if (!str.empty())
			{
				outfile << str << endl;
				cout << str << endl;
			}

		}

		// Close input file
		infile.close();
	}

	// Close output file
	outfile.close();

}
/*************************************************************************************************/
/*                                                                                               */
/*------------------------------------------ENDS Part I------------------------------------------*/
/*                                                                                               */
/*************************************************************************************************/



/*************************************************************************************************/
/*                                                                                               */
/*-----------------------------------------BEGINS Part II----------------------------------------*/
/*                                                                                               */
/*************************************************************************************************/

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
		else if (dummyVar == "END")
		{
			check[5] = true;
		}
		input += dummyVar;
	}
	ProgramFileInput.close();
	return input;
}

// Checks if PROGRAM, BEGIN, END., and INTEGER is missing or mispelled
bool checkKeyword()
{
	if (check[5])
	{
		cout << ". is expected. Program is rejected." << endl;
		return false;
	}
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

// Analyzes to see what is missing from the program and issues
// the corresponding error messages
void analyzeError(const string& item, const char& rowVal, const char& colVal, const char& input)
{
	if (input == 'i' && colVal != ':')
	{
		cout << ": is missing.";
	}
	else if (check[6])
	{
		cout << "; is missing.";
	}
	else if (rowVal == '=' || rowVal == ')' || rowVal == '(')
	{
		cout << rowVal << " is missing.";
	}
	else if (item == "!" || check[7])
	{
		cout << "\nIllegal expression.";
	}
	else if (rowVal == 'M' && isupper(colVal))
	{
		cout << "PRINT is mispelled.";
	}
	else if (item == "")
	{
		cout << "\nUnknown identifier.";
	}
	cout << " Program is rejected." << endl;
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

// Populates table with data in the text file
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

// Checks if a semicolon is missing from the program
void checkMissingSemiColon()
{
	fstream ProgramFileInput;
	ProgramFileInput.open("finalv2.txt", ios_base::in);
	if (!ProgramFileInput)
	{
		cout << "Fail to open program file." << endl;
		return;
	}
	string str = "";

	while (getline(ProgramFileInput, str))
	{
		size_t i = str.find(";");
		if (i == std::string::npos)	// if no ; is found
		{
			if (str.find("BEGIN") == std::string::npos && str.find("END.") == std::string::npos)
				check[6] = true;
		}
		else // if ; is found
		{
			if (str.find("BEGIN") != std::string::npos || str.find("END.") != std::string::npos)
				check[7] = true;
		}
		str = "";
	}
	ProgramFileInput.close();
}

int partTwo()
{
	string input = processInputFile();
	checkMissingSemiColon();
	string table[ROW][COL];
	populateTable(table);

	//Testing parse_table
	//for (int i = 0; i < ROW; i++) {
	//	for (int j = 0; j < COL; j++) {
	//		cout << setw(5) << table[i][j];
	//	}
	//	cout << endl;
	//}
	//cout << "String is : " << input << endl;

	// Check if any of the keyword is missing from the grammar
	if (!checkKeyword())	// if a keyword is missing
	{
		return -1;
	}
	else	// if it's not missing
	{
		string tmp = "";
		stack<char> myStack;

		myStack.push((table[1][0])[0]);		//push X or the begin state
		int i = 0;		// counter to read input
		bool done = false;		// flag to see if the program is done processing
		while (i < input.length() && !done)
		{
			char top = myStack.top();
			myStack.pop();		// pop the stack
			if (top != input[i])	// no match found
			{
				tmp = findInTable(top, input[i], table);	// find the value at [top, input[i]] in parsing table
				if (tmp == "!" || tmp == "")	// empty cell or invalid symbol
				{
					printStack(myStack);
					//cout << "Input is " << input[i - 1] << endl;
					//cout << "Trigger: " << tmp << " at [" << top << ", " << input[i] << "]\n";
					cout << endl;
					analyzeError(tmp, top, input[i], input[i - 1]);	// analyze and print what is missing
					done = true;
					return -1;
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
					if (!myStack.empty() || i < input.length() - 1)
					{
						//stack is not empty or there are more input after END.
						cout << "Illegal expression." << endl;
						return -1;
					}
					else
					{
						cout << "\nProgram is accepted." << endl;
						return 0;
					}
					done = true;
				}
				else
					++i;	// read next input character
			}
		}
	}
	return 0;
}
/*************************************************************************************************/
/*                                                                                               */
/*------------------------------------------ENDS Part II-----------------------------------------*/
/*                                                                                               */
/*************************************************************************************************/




/*************************************************************************************************/
/*                                                                                               */
/*----------------------------------------BEGINS Part III----------------------------------------*/
/*                                                                                               */
/*************************************************************************************************/

void partThree()
{
	map<string, string> myMap;
	map<string, string>::iterator it = myMap.begin();
	myMap.insert(it, pair<string, string>("PROGRAM S2017 ; ", "#include<iostream>\nusing namespace std;"));
	myMap.insert(it, pair<string, string>("BEGIN", "int main()\n{"));
	myMap.insert(it, pair<string, string>("END.", "return 0;\n}"));
	myMap.insert(it, pair<string, string>("INTEGER", "int "));
	myMap.insert(it, pair<string, string>("PRINT", "cout <<"));

	// Declare the I/O streams
	ifstream infile;
	ofstream outfile;

	// Declare the I/O file names
	string inFilename = "finalv2.txt";
	string outFilename = "finalv3.cpp";

	// Declare the strings needed to process the I/O
	string str;

	// Open input file to read from
	infile.open(inFilename.c_str());

	// If cannot open input file
	if (infile.fail()) {
		cout << "\nInvaild file name.\n";
		return;
	}

	// Open output file to write to
	outfile.open(outFilename.c_str());

	// Start processing the input file
	if (infile.is_open())
	{
		while (getline(infile, str))	// loop till the end of file
		{
			if (myMap.find(str) != myMap.end())
			{
				cout << myMap.find(str)->second << endl;
				outfile << myMap.find(str)->second << endl;
			}

			else
			{
				int n = str.length();
				int i = 0;
				string tempStr = "";
				while ((i < n) && (str[i] != ' '))
				{
					tempStr += str[i];
					++i;
				}
				if (myMap.find(tempStr) != myMap.end())
				{
					cout << myMap.find(tempStr)->second;
					outfile << myMap.find(tempStr)->second;
					if (myMap.find(tempStr)->first == "PRINT")
					{
						cout << str.substr(i + 2, n - (i + 2) - 4) << ";" << endl;
						outfile << str.substr(i + 2, n - (i + 2) - 4) << ";" << endl;
					}
					else
					{
						cout << str.substr(i + 2, n - (i + 2)) << endl;
						outfile << str.substr(i + 2, n - (i + 2)) << endl;
					}

				}
				else
				{
					cout << str << endl;
					outfile << str << endl;
				}

			}

		}
	}

}

/*************************************************************************************************/
/*                                                                                               */
/*-----------------------------------------ENDS Part III-----------------------------------------*/
/*                                                                                               */
/*************************************************************************************************/

// Main program
int main()
{
	cout << "Part I - Processing finalv1.txt..." << endl;
	partOne();

	cout << "\n\nPart II - Processing finalv2.txt..." << endl;
	cout << "Printing out the stack after every push." << endl;
	int valid = partTwo();
	if (valid == 0)
	{
		cout << "\n\nPart III - Translating to C++..." << endl << endl;
		partThree();
	}
	else
		cout << "Program does not follow grammar. Cannot translate to C++." << endl;

	cout << endl;
	return 0;
}
// Ends main program
