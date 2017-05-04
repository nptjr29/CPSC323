#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	map<string, string> myMap;
	map<string, string>::iterator it = myMap.begin();
	myMap.insert(it, pair<string, string>("PROGRAM S2017 ; ", "#include<iostream>\nusing namespace std;"));
	myMap.insert(it, pair<string, string>("BEGIN", "int main() {"));
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
		return 0;
	}

	// Open output file to write to
	outfile.open(outFilename.c_str());

	// Start processing the input file
	if (infile.is_open())
	{
		while (getline(infile, str))	// loop till the end of file
		{
			if (myMap.find(str) != myMap.end())
				outfile << myMap.find(str)->second << endl;
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
					outfile << myMap.find(tempStr)->second;
					if (myMap.find(tempStr)->first == "PRINT")
					{
						outfile << str.substr(i + 2, n - (i + 2) - 4) << ";" << endl;
					}
					else
					{
						outfile << str.substr(i + 2, n - (i + 2)) << endl;
					}
					
				}
				else
					outfile << str << endl;
			}
			
		}
	}


	//system("Pause");
	return 0;
}
