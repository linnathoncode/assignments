
#include <iostream>
#include <sstream>
#include <stack>
#include <limits>
#include <string>
#include <cmath>

using namespace std;

//takes the last the number added to the stack
//and does the calculation
int calc(int numberOne, int numberTwo, char postfix){
	int temp = 0;
	
	switch(postfix){
		case '+':
			temp = numberOne + numberTwo;
			break;
		case '-':
			temp = numberOne - numberTwo;
			break;
		case '/':
			if(numberTwo!= 0){
				temp = numberOne / numberTwo;
			}
			else{
				cout<< "Error: Division by zero."<<endl;
				invalid = true;
			}
		case '*':
			temp = numberOne * numberTwo;
			break;	
		case '^':
			temp = pow(numberOne, numberTwo);
			break;
	}
	return temp;
}


int main() {
	string postfix;
	int x;
	stringstream parser;
	bool invalid = false;
	
	cout<< "Enter a postfix expression:"<<endl;
	getline(cin, postfix);
	
	stack<int> operand_stack;
	int operandOne = 0;
	int operandTwo = 0;
	
	for(int i = 0; i < postfix.length(); i++){
		//if the index is neither an operator nor a blank
		//converts the char into int and pushes the to stack
		if(postfix[i] != '+'&& postfix[i] != '-' && postfix[i] != '/' && postfix[i] != '*' &&
		postfix[i] != '^' && postfix[i] != ' '){
			
			//converts char into int
			parser << postfix[i];
			parser>> x;
			
			operand_stack.push(x);
			//stringstream func
			//clears the 'parser' string 
			parser.clear();
		}
		
		//if the index is operator
		//pops two from the stack 
		//and sends them to calc func with the operator
		else if(postfix[i] != ' '){
			if(operand_stack.size()< 2){
				cout<<"Error: Invalid postfix expression.";
				invalid= true;
			}
			else {
			operandTwo = operand_stack.top();
			operand_stack.pop();
			operandOne = operand_stack.top();
			operand_stack.pop();
			
			operand_stack.push(calc(operandOne, operandTwo, postfix[i]));
			}
			
		}
		
	}
	
	//result
	if(!invalid){
	cout<< operand_stack.top();
	}
	
	    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    fflush(stdin); 
    getchar(); 
    return 0;
}
