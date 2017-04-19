/*
	Nguyen, Hympert		hympert@csu.fullerton.edu
	Nguyen, Thao		tnguyen29@csu.fullerton.edu
	April 18, 2017
	CPSC 323 - FINAL PROJECT - Part I
	Description: This program takes an input file "finalv1.txt",
	removes all the comment lines, blank lines, and extra blank spaces,
	leaves one space before and after each token, and copies the new
	version to the output file "finalv2.txt".
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

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

int main()
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
		return 0;
	}

	// Open output file to write to
	outfile.open(outFilename.c_str());

	// Start processing the input file
	if (infile.is_open())
	{
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
				outfile << str << endl;
		}

		// Close input file
		infile.close();
	}

	// Close output file
	outfile.close();

	return 0;
}
