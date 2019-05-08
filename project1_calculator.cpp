#include<iostream>
#include<stack>
#include<string>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

string InfixToPostfix(string expression);  // Input string(infix) to perform shunting algorithm, output string (postfix)

bool HasHigherPrecedence(char operator1, char operator2); // Checks if operator1 has a higher precedence than operator2

bool IsOperator(char C); // Checks if char is an operator
 
bool IsOperand(char C); // Checks if char is an operand

double Eval(double op1, double op2, char op); //  Solves expression involving two operands and one operator

// Splits a string into a vector using space ' ' as the delimiter, used to iterate through values of the postfix string
vector <string> &split(const string &s, char delim, vector<string> &elems) { 
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector <string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

int main() 
{
	
	bool cont = true;
	
	unordered_map <string, double> mp;
	
	while (cont == true) { 
		
		string expression; 
		getline(cin,expression);
		
		if (expression == "quit") { // Option 1: Quit the program
			cont = false;
		}
		else if (expression[0] == 'l' and expression[1] == 'e' and expression[2] == 't' and expression[3] == ' ') { // Option 2: If storing a variable
			
			// Declare necassary vaiables
			vector <string> y = split(expression, ' ');
			char check;
			int slen = expression.length();
			string exp;
			
			for (int i = 0; i < slen; i++) {
				check = expression[i];

				if (check ==  '=') {
					// Declare necassary vaiables
					exp = expression.substr(i+1);
					
					string postfix = InfixToPostfix(exp);
			
					vector <string> x = split(postfix, ' ');
			
					int len = x.size();
			
					stack <double> values;
					
					// Declare necassary vaiables, used to temporarily hold values for ease of type conversion
					string temp;
					char swap;
					double conv;
				
					double ope1;
					double ope2;
				
					double result;
					
					// Special case results
					bool divByZero = false;
					bool undecVar = false;
				
					for (int i = 0; i < len; i++) {
						temp = x[i];

						if (temp ==  "+" or temp == "-" or temp == "*" or temp == "/" or temp == "^") {
							ope2 = values.top();
							values.pop();
							ope1 = values.top();
							values.pop();
							
							swap = temp[0];
							
							if (ope2 == 0 and swap == '/') {
								cout << "Division-By-Zero" << endl;
								divByZero = true;
								break;
							}
							
							result = Eval(ope1,ope2,swap);
							values.push(result);
						}
						
						else {
							swap = temp[0];
							
							if ( isdigit(swap)) {
								conv = atof(temp.c_str());
								values.push(conv);
								result = conv;
							}
							else if (mp.find(temp) == mp.end()){
								cout << "Undeclared-Variable" << endl;
								undecVar = true;
								break;
							}
							else {
								conv = mp[temp];
								values.push(conv);
								result = conv;
							}
							
						}
					
					}
				
					if (divByZero == false and undecVar == false) {
						mp[y[1]] = result;
						
					}
				
				}
			}
			
		}
		
		//////////////////////////////////////////////////////////////////////////////////////////
		
		else { // Option 3: If solving an expression
			string postfix = InfixToPostfix(expression);
			
			vector <string> x = split(postfix, ' ');
			
			int len = x.size();
			
			stack <double> values;
			
			string temp;
			char swap;
			double conv;
			
			double ope1;
			double ope2;
			
			double result;
			bool divByZero = false;
			bool undecVar = false;
			
			for (int i = 0; i < len; i++) {
				temp = x[i];

				if (temp ==  "+" or temp == "-" or temp == "*" or temp == "/" or temp == "^") {
					ope2 = values.top();
					values.pop();
					ope1 = values.top();
					values.pop();
					
					swap = temp[0];
					
					if (ope2 == 0 and swap == '/') {
						cout << "Division-By-Zero" << endl;
						divByZero = true;
						break;
					}
					
					result = Eval(ope1,ope2,swap);
					values.push(result);
				}
				
				else {
					swap = temp[0];
					
					if ( isdigit(swap)) {
						conv = atof(temp.c_str());
						values.push(conv);
						result = conv;
					}
					else if (mp.find(temp) == mp.end()){
						cout << "Undeclared-Variable" << endl;
						undecVar = true;
						break;
					}
					else {
						conv = mp[temp];
						values.push(conv);
						result = conv;
					}
					
				}
				
			}
			
			if (divByZero == false and undecVar == false) {
				cout << result << endl;
			}
		}
	
	}
	return 0;
}

string InfixToPostfix(string expression)
{ 
	stack<char> S;
	string temp = "";
	string postfix = "";

	for(int i = 0;i< expression.length();i++) {

		if(expression[i] == ' ' || expression[i] == ',') continue; 

		else if(IsOperator(expression[i])) 
		{
			// while not empty, not open paren, and has precendence
			
			while(!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(),expression[i]))
			{
				postfix += S.top();
				postfix += " ";
				S.pop();
			}
			
			S.push(expression[i]);
			
		}
		else if(IsOperand(expression[i]))
		{
			if (IsOperand(expression[i+1])) {
				while (IsOperand(expression[i])) {
					temp += expression[i];
					i++;
				}
				i--;
			
				postfix += temp;
				postfix += " ";
			}
			
			else {
				postfix +=expression[i];
				postfix += " ";
			}
			
			
		}

		else if (expression[i] == '(') 
		{
			S.push(expression[i]);
		}

		else if(expression[i] == ')') 
		{
			while(!S.empty() && S.top() !=  '(') {
				postfix += S.top();
				postfix += " ";
				S.pop();
			}
			S.pop();
		}
		else if (!IsOperand(expression[i])) {
			if (!IsOperand(expression[i+1])) {
				while (!IsOperand(expression[i])) {
					temp += expression[i];
					i++;
				}
				i--;
			
				postfix += temp;
				postfix += " ";
			}
			
			else {
				postfix +=expression[i];
				postfix += " ";
			}
			
		}
		temp = "";
		
	}

	while(!S.empty()) {
		postfix += S.top();
		postfix += " ";
		S.pop();
	}

	return postfix;
}

bool IsOperand(char C) 
{
	if(C >= '0' && C <= '9') return true;
	if(C >= 'a' && C <= 'z') return true;
	if(C >= 'A' && C <= 'Z') return true;
	if(C == '.') return true;
	return false;
}

bool IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/' || C== '^')
		return true;

	return false;
}

int IsRightAssociative(char op)
{
	if(op == '^') return true;
	return false;
}

int GetOperatorWeight(char op)
{
	int weight; 
	switch(op)
	{
	case '+':
	case '-':
		weight = 1;
		break;
	case '*':
	case '/':
		weight = 2;
		break;
	case '^':
		weight = 3;
		break;
	}
	return weight;
}

bool HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	if(op1Weight == op2Weight)
	{
		if(IsRightAssociative(op1)) return false;
		else return true;
	}
	return op1Weight > op2Weight ?  true: false;
}

double Eval(double op1, double op2, char op)
{
    double ans;
    switch(op){
    case '+':
        ans = op2 + op1;
        break;
    case '-':
        ans = op1 - op2;
        break;
    case '*':
        ans = op2 * op1;
        break;
    case '/':
		if (op2 == 0) {
			cout << "Division-By-Zero" << endl;
		}
		else {
			ans = op1 / op2;
		}
        
        break;
	case '^':
		ans = pow(op1, op2);
		break;
    }
    return ans;
}