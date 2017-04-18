/*
	Hympert Nguyen
	Thao Nguyen

	CPSC 323
	Programming Assignment 2
	February 6, 2017
*/

#include <string>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::getline;

bool isOperator(const char& a);
int evaluate(int a, int b, const char& x);

int main()
{
	struct ExpVariable
	{
		string var;
		int length;
		int value;
	};

	int i = 0;
	stack<int> varStack;
	vector<ExpVariable> varList;
	string tempStr;
	int tempVal = 0;
	string exp;

	char cont = 'y';
	while (cont == 'y' || cont == 'Y')
	{
		i = 0;
		tempStr = "";
		tempVal = 0;
		exp = "";
		cout << "Enter a postfix expression: ";
		getline(cin, exp);

		while (exp[i] != '$')	// while the end isn't reached
		{			
			if (exp[i] != ' ' && !isOperator(exp[i]))
				tempStr += exp[i];
			else
			{
				if (!isOperator(exp[i]))
				{
					//search for variable in the list
					bool found = false;
					int j = 0;
					while (j < varList.size())
					{
						if (varList[j].var == tempStr)
						{
							found = true;
							tempVal = varList[j].value;
						}
						++j;
					}
					//if variable isn't already defined
					if (!found)
					{
						// if variable is a digit
						if (isdigit(tempStr[0]))
						{
							// convert the variable to its numeric value
							tempVal = stoi(tempStr);
						}
						else	// if variable is a string
						{
							cout << "	Enter the value of " << tempStr << ": ";

							cin >> tempVal;
							cin.ignore();
						}
						
						//add variable with its value to the list
						ExpVariable newVar;
						newVar.var = tempStr;
						newVar.length = tempStr.size();
						newVar.value = tempVal;
						varList.push_back(newVar);
					}

					varStack.push(tempVal);
					tempStr = "";
				}
				else
				{
					int var1 = varStack.top();
					varStack.pop();
					int var2 = varStack.top();
					varStack.pop();
					int tempVar = evaluate(var2, var1, exp[i]);
					varStack.push(tempVar);
					++i;	// ignore space after an operator
				}
				
			}			
			++i;
		}

		cout << "		Final value = " << varStack.top() << endl;
		cout << "Continue(y/n)? ";
		cin >> cont;
		cin.ignore();

		varStack.pop();		//clear stack
		varList.clear();	//clear variable list
		
		cout << endl;
	}

	cout << endl;
	system("Pause");
	return 0;
}

bool isOperator(const char& a)
{
	return (a == '+' || a == '-' || a == '*' || a == '/');
}

int evaluate(int a, int b, const char& x)
{
	int result = 0;
	switch (x)
	{
	case '+':
		result = a + b;
		break;
	case '-':
		result = a - b;
		break;
	case '*':
		result = a * b;
		break;
	case '/':
		result = a / b;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}



