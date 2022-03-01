#include "d_tnodel.h"
#include <iostream>
#include "inf2pstf.h"

using namespace std;

tnode<char> *buildExpTree(const string&exp);

//******************************************NEW CODE********************************//
void prefixoutput(tnode<char> *exp){
if(exp != nullptr){
    cout << exp->nodeValue << " ";
    prefixoutput(exp->left);
    prefixoutput(exp->right);
}
}

void postfixoutput(tnode<char> *exp){
if(exp != nullptr){
    postfixoutput(exp->left);
    postfixoutput(exp->right);
    cout << exp->nodeValue << " ";
}
}

int main(){
string example = "(a+b)/c";
infix2Postfix test = infix2Postfix(example);
example = test.postfix();
tnode<char> *charRoot = buildExpTree(example);
prefixoutput(charRoot);
cout << endl;
postfixoutput(charRoot);
cout << endl;
displayTree(charRoot,1);
cout << endl;
return 0;
}


//************************************REPURPOSED CODE(function from lab material)******************************//

// build an expression tree from a postfix expression.
// the operands are single letter identifiers in the range from
// 'a' .. 'z' and the operators are selected from the characters
// '+', '-', '*' and '/'
tnode<char> *buildExpTree(const string& exp)
{
	// newnode is the address of the root of subtrees we build
	tnode<char> *newnode, *lptr, *rptr;
	char token;
	// subtrees go into and off the stack
	stack<tnode<char> *> s;
	int i = 0;


	// loop until i reaches the end of the string
	while(i != exp.length())
	{
		// skip blanks and tabs in the expression
		while (exp[i] == ' ' || exp[i] == '\t'){
			i++;
        }
		// if the expression has trailing whitespace, we could
		// be at the end of the string
		if (i == exp.length()){
			break;
        }
		// extract the current token and increment i
		token = exp[i];
		i++;

		// see if the token is an operator or an operand
		if (token == '+' || token == '-' || token == '*' || token == '/')
		{
			// current token is an operator. pop two subtrees off
			// the stack.
			rptr = s.top();
			s.pop();
			lptr = s.top();
			s.pop();
		
			// create a new subtree with token as root and subtees
			// lptr and rptr and push it onto the stack
			newnode = new tnode<char>(token,lptr,rptr);
			s.push(newnode);
		}
		else // must be an operand
		{
			// create a leaf node and push it onto the stack
			newnode = new tnode<char>(token);
			s.push(newnode);
		}
	}

	// if the expression was not empty, the root of the expression
	// tree is on the top of the stack
	if (!s.empty()){
		return s.top();
    }
    else{
		return NULL;
    }
}
