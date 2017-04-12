#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

const int ROW = 17;
const int COL = 12;
stack<string> myStack;
string grammar[8] = { "E6", "E6", "E2", "T6", "T6", "T2", "F6", "F2" };

string findInTable(const string& rowVal, const string& colVal, const string table[ROW][COL])
{
	int i = 0, j = 0;
	while (i < ROW)
	{
		if (table[i][0] == rowVal)
		{
			while (j < COL)
			{
				if (table[0][j] == colVal)
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
void printStack()
{
	if (myStack.empty())
		cout << "Stack is empty.";
	else
	{
		int size = myStack.size();
		string * arr = new string[size + 1];
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


void Process_s(string b, string c, string s) {
	myStack.push(b);
	myStack.push(c);
	myStack.push(s);
	//printStack();
}

void Process_r(string b, string c, string s, const string parsing_table[ROW][COL]) {
	myStack.push(b);
	int num = stoi(s);
	//cout << "Rule is: " << num << endl;
	int num2 = stoi(grammar[num - 1].substr(1, 1));
	for (int i = 0; i < num2; i++) {
		myStack.pop();
	}
	string e = myStack.top();
	myStack.pop();

	string col = grammar[num - 1].substr(0, 1);
	string d = findInTable(e, col, parsing_table);
	myStack.push(e);
	myStack.push(col);
	myStack.push(d);
}

void Process_num(string b, string c, string s) {
	myStack.push(b);
	myStack.push(c);
	myStack.push(s);
}



int main() {

	string exp;
	cout << "Enter the expression:";
	cin >> exp;
	ifstream input;
	input.open("parsing_table.txt", ios_base::in);
	if (!input) {
		cout << "Cannot open file";
		return 0;
	}

	string a;
	string parsing_table[ROW][COL];
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			input >> a;
			parsing_table[i][j] = a;
		}
	}

	cout << "Printing out the table" << endl;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << setw(8) << parsing_table[i][j] << " ";
		}
		cout << endl;
	}


	string b;
	string c;
	string d;
	int i = 0;
	myStack.push("0");
	if (exp.length() == 1 || exp[0] == '$')
		cout << "Word is rejected.";
	else
	{
		while (i < exp.length())
		{
			b = myStack.top();
			myStack.pop();
			c = exp[i];
			d = findInTable(b, c, parsing_table);
			if (d[0] == 's') {
				Process_s(b, c, d.substr(1, d.length() - 1));
				++i;
			}
			else if (d[0] == 'r') {
				Process_r(b, c, d.substr(1, d.length() - 1), parsing_table);
			}
			else {
				if (d == "0")
				{
					if (c == "+" || c == "-" || c == "*" || c == "/" || c == "(" || c == ")" || c == "$")
						cout << "Word is rejected because it's missing an operand.";
					else
						cout << "Word is rejected because it's missing an operator.";
					break;
				}
				else if (d == "")
				{
					cout << "Rejected because it's gibberish.";
					break;
				}
				else if (d != "acc")
					Process_num(b, c, d);
				else
				{
					cout << "Word is accepted.";
					break;
				}


			}

			printStack();
		}
	}



	

	cout << endl;
	system("Pause");
	return 0;
}