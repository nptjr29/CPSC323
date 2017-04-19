#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

/*--------------------------PART ONE-------------------------*/

/*---------------Helper Functions for Part One---------------*/

//return true if there are 2 consecutive spaces
bool bothAreSpaces(char lhs, char rhs)
{
	return ((lhs == rhs) && ((lhs == ' ') || (lhs == '\t')))
		|| ((lhs == '\t') && (rhs == ' ')) 
		|| ((lhs == ' ') && (rhs == '\t'));
}

string removeComments(const string& str)
{
	int n = str.length();
	string res;		// result string

	// Flags to indicate that comments have started or not.
	bool comment = false;

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

/*-------------------Function for Part One-------------------*/
void partOne()
{
	ifstream infile;
	ofstream outfile;

	string filename = "finalv1.txt";
	string outFilename = "finalv2.txt";
	string tempFilename = "temp.txt";

	string str, tempStr1, tempStr2;

	infile.open(filename.c_str());
	if (infile.fail()) {
		cout << "\nInvaild file name.\n";
		return;
	}
	outfile.open(tempFilename.c_str());

	if (infile.is_open())
	{
		while (getline(infile, str))
		{
			// copy content of file to tempStr1 line by line
			tempStr1 += str;
			// add a new line at the end of each line
			tempStr1 += "\n";
		}
		// remove comments from tempStr1 and put the rest into tempStr2
		tempStr2 = removeComments(tempStr1);
		// write tempStr2 into a temporary file
		outfile << tempStr2;
		// close the original input file
		infile.close();
	}
	outfile.close();

	infile.open(tempFilename.c_str());
	outfile.open(outFilename.c_str());
	if (infile.is_open())
	{
		while (getline(infile, str))
		{
			// add spaces before and after each token
			addSpaceToken(str);

			// remove extra spaces
			removeExtraSpaces(str);

			// remove blank lines
			if (!str.empty())
				outfile << str << endl;
		}
		infile.close();
	}

	outfile.close();
}

/*------------------------END PART ONE-----------------------*/

int main()
{
	partOne();
	//TODO: partTwo();
	//TODO: partThree();

	//system("Pause");
	return 0;
}
