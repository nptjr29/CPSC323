#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

//return true if there are 2 consecutive spaces
bool bothAreSpaces(char lhs, char rhs) 
{ 
	return (lhs == rhs) && (lhs == ' '); 
}

void removeExtraSpaces(string &str)
{
	//remove leading blank spaces
	size_t p = str.find_first_not_of(" \t");
	str.erase(0, p);

	//remove extra blank spaces inside the string
	string::iterator i = unique(str.begin(), str.end(), bothAreSpaces);
	str.erase(i, str.end());
}

bool isOperand(char & a)
{
	return (isalnum(a) || a == '_');
}

// add space before and after each token
void addSpaceToken(string & str)
{
	int i = 1;
	while (i < str.length())
	{
		// if we found an operator
		if (!isOperand(str[i]))
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
	ifstream infile;
	ofstream outfile;

	string filename = "data.txt";
	string outFilename = "newdata.txt";

	string source, str;

	infile.open(filename.c_str());
	if (infile.fail()) {
		cout << "\nInvaild file name.\n";
		return 1;
	}
	outfile.open(outFilename.c_str());

	if (infile.is_open())
	{
		while (getline(infile, str))
		{
			// remove comments
			while (str.find("//") != string::npos)
			{
				size_t begin = str.find("//");
				str.erase(begin, str.find("\n", begin) - begin);
			}

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

	return 0;
}
