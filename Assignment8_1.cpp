#include <iostream>
#include <string>
#include <stack>
using namespace std;
using std::cin;
using std::cout;
const int ROW = 6;	//adjust this according to the parse table
const int COL = 9;	//adjust this according to the parse table

// Converts a character to a string
string charToString(const char& a)
{
	string str = "";
	str += a;
	return str;
}

// Returns the string found at table[rowVal, colVal]
string findInTable (const char& rowVal, const char& colVal, const string table[ROW][COL])
{
	int i = 0, j = 0;
	string temp = "";
	while (i < ROW)
	{
		if (table[i][0] == charToString(rowVal))
		{
			while (j < COL)
			{
				if (table[0][j] == charToString(colVal))
					temp = table[i][j];
				else
					++j;
			}
		}
		++i;
	}
	return temp;
}

void printStack(stack<char>& myStack)
{
	char * arr = new char[];
	int size = myStack.size();
	cout << "Stack is: ";
	//stack is {$ E Q}
	for (int i = 0; i < size; ++i)
	{
		arr[i] = myStack.top();
		myStack.pop();
		// array is {Q E $}
		cout << arr[i] << " ";
	}
	for (int i = size - 1; i >= 0; --i)
	{
		//stack is {$ E Q}
		myStack.push(arr[i]);
	}
	cout << endl;
}

int main()
{
	//Input parse_table
	string parseTable[ROW][COL] = {
		{"states", "i", "+", "-", "*", "/", "(", ")", "$" },
		{ "E", "TQ", "0", "0", "0", "0", "TQ", "0", "0" },
		{ "Q", "0", "+TQ", "-TQ", "0", "0", "0", "lambda", "lambda" },
		{ "T", "FR", "0", "0", "0", "0", "FR", "0", "0" },
		{ "R", "0", "lambda", "lambda", "*FR", "/FR", "0", "lambda", "lambda" },
		{ "F", "i", "0", "0", "0", "0", "(E)", "0", "0" }
	};

	// Testing parse_table
	//for (int i = 0; i < ROW; ++i)
	//{
	//	for (int j = 0; j < COL; ++j)
	//	{
	//		cout << parseTable[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	//Input statement to trace
	cout << "Please input a statement: ";
	string input;
	cin >> input;
	string tmp = "";
	stack<char> myStack;
	myStack.push('$');		//push $
	myStack.push((parseTable[1][0])[0]);	//push E
	int i = 0;
	bool done = false;
	while (i < input.length() && !done)
	{
			char top = myStack.top();
			myStack.pop();
			if (top != input[i])	// no match found
			{
				tmp = findInTable(top, input[i], parseTable);
				if (tmp != "lambda" && tmp != "0")
				{
					for (int k = tmp.length() - 1 ; k >= 0; --k)
						myStack.push(tmp[k]);		//push in reverse
					printStack(myStack);			//print stack after pushing
				}
				else if (tmp == "0")
				{
					cout << "Statement is rejected." << endl;
					done = true;
				}
				tmp = "";	//reset tmp
			}
			else	//found a match
			{
				if (input[i] == '$')
				{
					cout << "Statement is accepted." << endl;
					done = true;
				}						
				else
					++i;
			}
		}

	cout << endl;
	system("Pause");  //only needed for visual studio
	return 0;
}
