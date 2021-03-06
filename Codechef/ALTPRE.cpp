// Codechef problem name: ALTPRE.  @Author :Ghazi-Khan
/*
 **************************************************************************************************
  *                                                                                                *
   *                                                                                                *
    *   *****************   *             *    ***************         **************** ***********  *
      *  *               *   *             *    *             *                      *       *        *
       *  *               *   *             *    *             *                    *         *        *
        *  *                   *             *    *             *                  *           *        *
         *  *                   *             *    *             *                *             *        *
          *  *      *********    ***************    ***************              *               *        *
           *  *              *    *             *    *             *            *                 *       *
            *  *              *    *             *    *             *          *                   *       *
             *  *              *    *             *    *             *        *                     *       *
              *  *              *    *             *    *             *      *                       *       *
               *  *              *    *             *    *             *    *                         *       *
                *  ****************    *             *    *             *  *****************     ************  *
                 *                                                                                              *
                  *                                                                                              *
                   ************************************************************************************************

*/
#include <iostream>
#include <string>
#include <stack>
#define ll long long 
#define out cout<<
#define in cin>>
#define nl <<endl
using namespace std;

stack<int> values;		//Store operends
stack<char> operators;		//Store operators

//Process the top 2 operands of values stack and one operator of operators stack 
ll solve()
{
	ll operend1,operend2;
	char top_operator;
	operend2 = values.top();
	values.pop();
	operend1 = values.top();
	values.pop();
	top_operator = operators.top();
	operators.pop();
	switch(top_operator){
	case '+': return operend1+operend2;
	case '-': return operend1-operend2;
	case '*': return operend1*operend2;
	case '/': return operend1/operend2;
	}
}

//Precedence of operators
int checkPre(char c){
	if(c=='+' || c=='-')
		return 3;
	if(c=='*' || c=='/')
		return 2;

	return 1;			
}

//Utill funtion
ll solvePre(string s)
{
	for(int i=0;i< s.length();i++)
	{
		//If space is encounter then just ignore it.
		if(s[i] == ' ')
			continue;
		//Valid number is encounter 
		else if(s[i] >= '0' && s[i] <= '9')
		{
			ll operend=0;
			//The number may contain multiple digits, obtainning actual number
			while(s[i] >= '0' && s[i] <= '9' && i < s.length())
			{
				operend = (operend*10) + (s[i] - '0');
				i++;
			}
			// Push the number on to the value stack
			values.push(operend);			
			//Decrement the counter i so that it point back to last char
			i--;
		}
		//if left parentheses is encounter then only push on the operator stack
		else if(s[i] == '(')
			operators.push(s[i]);
		//When right parentheses encounter solve the entire equation which is inside the 
		//opening and closing parentheses e.g (x+y)
		else if(s[i] == ')')
		{
			while(operators.top() !='(' && !operators.empty())
				values.push(solve());
			//pop out the right parentheses
			operators.pop();		
		}
		else{
			//s[i] contains the operator, compare it with the operator on the top of stack
			//if opereator on the top of the stack having higher or equal precedence than s[i] operator then
			//process the operator which is on the top of stack,check untill there is an opereator with less precedence.
			//when condiotion is become false push the s[i] on to the stack.
			//else directly push s[i] on the stack. 
			while(!operators.empty() && checkPre(s[i]) <= checkPre(operators.top()))
				values.push(solve());	
			operators.push(s[i]);
		}
	}
	//Finally the entire string is processed,now solve 
	//remaining operators.  
	while(!operators.empty())
			values.push(solve());

	return values.top();
}
int main(int argc, char const *argv[])
{
	ll t;
	string s;
	in t;
    cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	while(t--)
	{
		in s;
		out solvePre(s) nl; 
	}
	return 0;
}
