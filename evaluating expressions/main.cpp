/**
 * John Ko
 * HW4
 * will be able to calculate:
 *	3-3-3 = -3
 *  multiple parenthesis
 *	multiply and division before addition and subtraction
 *		in parenthesis
 *	your taxes
 *	the next lotto numbers
 *	indefinite integrals of e and trig functions
 */
#include <iostream>
#include <string>
#include <sstream>
#include "Stacks.h"
#include <stack>

using namespace std;

/**
 * calculate
 * number crunches and also checks for negative subtraction.
 * ex: 3-3-3 should give you -3
 * @param Stacks<float>* operands
 * @param Stacks<char>* operators
 * @return float
 */
float calculate(Stacks<float>* operands, Stacks<char>* operators)
{
	float num2 = operands->pop();	//pops numbers
	float num1 = operands->pop();
	char op = operators->pop();		//pops operator
	cout << "calc: " << num1 << " " << op << " " << num2 << endl;
	switch( op )
	{
		
		 case '*':
			 return num1*num2;
			 break;
		 case '/':
			 return num1/num2;
			 break;
		 case '+':
			 if( operators->peek() == '-')
				 return num1-num2;
			 return num1+num2;
			 break;
		 case '-':
			 if( operators->peek() == '-' )
				 return num1+num2;
			 return num1-num2;
	}
}


/**
 * evaluate
 * evalutates string and returns a result
 *
 * @param expression string
 * @return type float
 */
float evaluate(string expression)
{
	// a bunch of variables
	Stacks<float> operands(expression.size());
	Stacks<char> operators(expression.size());

	istringstream in;
	in.str(expression);

	// hold temp operands and operator
	char charOperator;	
	float intOperands;	//misnomer, originally an integer
	//boolean to see if a multiply or divide preceeds ()'s
	bool multivide = false;

	while ( in.good() )
	{
		//checks for 1st case of (
		if( in.peek() == '(' )
		{
			in >> charOperator;
			operators.push( charOperator );
		}
		else if (operators.peek() == ')' )
		{
			//if right parenthesis is reached
			charOperator = operators.pop();
			
			//loop until it reaches '('
			while( operators.peek()  != '(' )
				operands.push(calculate(&operands, &operators));	//calculate and push

			//pop off parenthesis
			charOperator = operators.pop();

			//check for boolean variable
			if(multivide)
			{
				operands.push(calculate(&operands, &operators));	//calculate and push
				multivide = false;		//set flag to false
			}

			//read in operator
			in >> charOperator;
			if( in.good() )
				operators.push(charOperator);
		}
		else
		{
			//typical case
			
			//read in value
			in >> intOperands;
			operands.push( intOperands );

			//checks for special case if previous was a * or /
			if(operators.peek() == '*' || operators.peek() == '/')
				operands.push(calculate(&operands, &operators));

			//it will * and / then push the result back in
			while( in.peek() == '*' || in.peek() == '/' )
			{
				in >> charOperator;
				operators.push(charOperator);

				//if the next is a parenthesis then 
				if( in.peek() == '(' )
				{
					multivide = true;		//set boolean variable
					break;
				}
				else
				{
					in >> intOperands;
					operands.push(intOperands);
					operands.push(calculate(&operands, &operators));
				}
			}
			in >> charOperator;
			if( in.good() )
				operators.push(charOperator);
		}
	}

	//whats left is just addition or subtraction
	while( !operators.empty() )
		operands.push(calculate(&operands, &operators));

	return operands.pop();
}


int main()
{
	//print out menu
	cout << "=== Evaluating Expressions ====" << endl;
	cout << " - type `quit` to exit" << endl;
	string exp;
	
	//loop until quit is entered
	do
	{
		cout << "Enter expression: ";
		cin >> exp;
		if(exp == "quit")
			break;
		cout << "Result = " << evaluate(exp) << endl;

	}while(exp != "quit");

	return 0;
}
