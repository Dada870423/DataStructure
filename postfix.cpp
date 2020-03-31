#include<iostream>
#include<stack>
#include<queue>
#include<string>
#include<cstring>
#include<vector>
#include <sstream>
using namespace std;

stack<char> S;
stack<int> C;
vector<string> cal;
void compare_op(char );
int priority(char, int ); // 0: in stack 1: new op
void calulate();
void foo(char );
int power(int , int );

int main(void)
{
	int i, j, k;
	string input;
	string out = "";
	string for_input="";
	getline(std::cin,input);
	//cout<<input.length()<<endl;
	for(i=0;i<input.length();i++)
	{
		if((input[i] >= '0' && input[i] <= '9') && (input[i+1] < '0' || input[i+1] > '9'))
		{
			out += input[i];
			cal.push_back(out);
			out = "";
		} 
		else if((input[i] >= '0' && input[i] <= '9')) out += input[i];
		else if(input[i] == ' ') continue;
		else compare_op(input[i]);
	}
	while(!S.empty())
	{
		if(S.top() != '(') cal.push_back(for_input + S.top());
		S.pop();
	}
	
	calulate();
	cout<<C.top()<<endl;
	return 0;
}

void compare_op(char op)
{
	string for_input=""; 
	int priority1, priority2;
	if(S.empty()) S.push(op);
	else if(op == ')')
	{
		while(S.top() != '(')
		{
			cal.push_back(for_input + S.top());
			S.pop();
		}
	}
	else
	{
		//priority1 = priority(S.top());
		//priority2 = priority(op);
		while(!S.empty() && priority(S.top(),0) <= priority(op,1))
		{
			if(S.top() != '(') cal.push_back(for_input + S.top());
			S.pop();
		}
		S.push(op);
	}
}
int priority(char op, int in_out)
{
	int priority;
	if(op == '+' || op == '-') priority = 6;
	else if(op == '*' || op == '/') priority = 5;
	else if(op == '^' && in_out == 0) priority = 4;
	else if(op == '^' && in_out == 1) priority = 3;
	else if(op == '(' && in_out == 0) priority = 12;
	else if(op == '(' && in_out == 1) priority = 1;
	return priority;
}
void calulate()
{
	int i, j, k;
	int b;
	for(i=0;i<cal.size();i++) //cal[cal.size()-i-1]
	{
		if(cal[i] == "+") foo('+');
		else if(cal[i] == "-") foo('-');
		else if(cal[i] == "*") foo('*');
		else if(cal[i] == "/") foo('/');
		else if(cal[i] == "^") foo('^');
		else
		{
			string a = cal[i];
			std::istringstream ( a ) >> b;
			C.push(b);
		}
	}
}
void foo(char op)
{
	int a, b;
	a = C.top();
	C.pop();
	b = C.top();
	C.pop();
	
	if(op == '+') C.push(b+a);
	else if(op == '-') C.push(b-a);
	else if(op == '*') C.push(b*a);
	else if(op == '/') C.push(b/a);
	else if(op == '^') C.push(power(b,a));
		
}
int power(int a, int b)
{
	int i, j, k;
	int ans = 1;
	for(i=0;i<b;i++) ans *= a;
	return ans;
}
