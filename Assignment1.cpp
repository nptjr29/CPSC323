/*
	Hympert Nguyen
	Thao Nguyen
	Roya Askari

	CPSC 323
	Programming Assignment 1
	January 30, 2017
*/

#include <string>
#include <stack>
#include <map>
#include <iostream>
using namespace std;

bool isOperator(const char& a);
int evaluate(int a, int b, const char& x);

int main()
{
	char cont = 'y';
	while (cont == 'y' || cont == 'Y')
	{
		cout << "Enter a postfix expression: ";
		char * exp = new char[];
		cin >> exp;
		int i = 0;
		stack<int> varStack;
		map<char, int> varMap;

		while (exp[i] != '$')
		{
			if (!isOperator(exp[i]))
			{
				if (varMap.find(exp[i]) == varMap.end()) // returns false if value has already been added
				{
					cout << "	Enter the value of " << exp[i] << ": ";
					int tempVar = 0;
					cin >> tempVar;
					varMap.insert(std::pair<char, int>(exp[i], tempVar));
					varStack.push(tempVar);
				}
				else
				{
					varStack.push(varMap.find(exp[i])->second);
				}				
			}
			else
			{
				int var1 = varStack.top();
				varStack.pop();
				int var2 = varStack.top();
				varStack.pop();
				int tempVar = evaluate(var2, var1, exp[i]);
				varStack.push(tempVar);
			}
			++i;
		}
		cout << "		Final value = " << varStack.top() << endl;
		cout << "Continue(y/n)? ";
		cin >> cont;
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