#include <iostream>
#include <string>
#include <cmath>
#include "operatorStack.h"
#include "doubleStack.h"
using namespace std;

//function headers
int precedence(char currOperator);
bool isOperand(char currElement);
bool isOperator(char currElement);
string convertToPostFix(string infixExpression);
double evaluatePostFix(string postfixExpression);


int main() {
    //demo to test the functonality
    cout << "Welcome to Infix to Postfix." << endl;
    cout << "----------------------------" << endl << endl;
    string infix = "5-4+3*(4-2+8/2*3)+(8-2)^2";
    string postfix = convertToPostFix(infix);
  
    cout << "Here's a demo:" << endl; 
    cout << "INFIX: " << infix << endl;
    cout << "POSTFIX: " << postfix << endl;
    cout << "EVALUATION: " << evaluatePostFix(postfix) << endl;
    cout << "DEMO_FIN" << endl << endl;

    //variable to track user input
    string userInfix;
  
    //do while loop to allow user to try different operations
    do {
        cout << endl << "Enter an expression, or '~' to terminate (No spaces or non-numeric operands): " << endl;
        getline(cin, userInfix);

        if (userInfix != "~") {
            string userPostFix = convertToPostFix(userInfix);
            cout << "To postfix: " << userPostFix << endl;
           
            if(userPostFix != "Invalid Input!")
                cout << "Evaluation: " << evaluatePostFix(userPostFix) << endl;
        }
       
    } while (userInfix != "~");

    cout << "PROG_FIN";
        
    return 0;
}


//function to test operator precedence
int precedence(char currOperator) {
    if (currOperator == '+' || currOperator == '-')
        return 1;
    else if (currOperator == '*' || currOperator == '/')
        return 2;
    else if (currOperator == '^')
        return 3;
    return -1;
}


//function to test if scanned char is an operand
bool isOperand(char currElement) {
    for (int num = 0; num <= 9; num++) {
        if (currElement == '0' + num) {
            return true;
        }
    }
    return false;
}

//function to test if scanned char is an operator
bool isOperator(char currElement) {
    return (currElement == '+' || currElement == '-' || currElement == '*' || currElement == '/' || currElement == '^');
}

//function to test if scanned char is a parenthesis
bool isParenthesis(char currElement) {
    return (currElement == '(' || currElement == ')');
}

//function that will convert expression from infix to postfix
string convertToPostFix(string infixExpression) {
    //track size of initial string
    int SIZE = infixExpression.size();
    //string to hold postfix expression
    string postfixExpression = "";
    OperatorStack* stack = new OperatorStack;
   
    //for each loop that parses through infix string
    for (char currElement : infixExpression) {
        //if string contains invalid characters, outputs the following
        if (!isOperand(currElement) && !isOperator(currElement) && !isParenthesis(currElement))
            return "Invalid Input!"; 
        //is string is an operand, appends it to 'postfix'
        else if (isOperand(currElement)) 
            postfixExpression += currElement;
        //if stack is empty, pushes element onto stack --> unless its ')'
        else if (stack->isEmpty()) {
            if (currElement != ')')
                stack->push(currElement);
        }
        //checks if element is a parenthesis
        else if (isParenthesis(currElement)) {
            //if element is ')' searches for it's matching '(' by popping elements and adding them to 'postfix'
            if (currElement == ')') {
                while (!stack->isEmpty() && stack->getTopData() != '(') {
                    postfixExpression += stack->getTopData();
                    stack->pop();
                }
                //pops the ')' out of the stack without adding it
                stack->pop();
            }
            //if the element isn't a closing parenthesis, pushes onto the stack
            else
                stack->push(currElement);
        }
        //for all other operators
        else {
            //while the precedence of the current element is less than or equal to the precedence of the top element of the stack
            //appends current element to 'postfix'
            //pops the stack
            while (!stack->isEmpty() && precedence(currElement) <= precedence(stack->getTopData())) {
                postfixExpression += stack->getTopData();
                stack->pop();
            }
            //if the precedence of the current element is greater than the precedence of the top of the stack,
            //push it onto the stack 
            stack->push(currElement);
        }
    }

    //removes any remaining elements pushed to the stack
    while (!stack->isEmpty()) {
        //adds these elements to 'postfix'
        postfixExpression += stack->getTopData();
        stack->pop();
    }
    
    //free up memory
    delete stack;
    stack = nullptr;

    return postfixExpression;
}

double evaluatePostFix(string postfixExpression) {
    int SIZE = postfixExpression.size();
    DoubleStack* stack = new DoubleStack;

    for (char currElement : postfixExpression) {
        //pushes operand onto the stack after converting it to double
        if (isOperand(currElement)) {
            stack->push((double)currElement - '0');
        }
        //if stack is empty, the expression had the wrong number of operators
        //displays error message
        else if (stack->isEmpty()) {
            cerr << "Operand/Operator Mismatch" << endl;
            return NULL;
        }
        //otherwise: pops the top 2 operands from the stack
        //stores the popped operands
        else {
            double val1 = stack->pop();      
            
            double val2 = stack->pop();
            
            //performs the appropriate operation
            //adds the results of that operation onto the stack
            switch (currElement) {
                case '^':
                    stack->push(pow(val2,val1));
                    break;
                case '*':
                    stack->push(val2 * val1);
                    break;
                case '/':
                    if (val1 != 0)
                        stack->push(val2 / val1);
                    else {
                        cerr << "Divide by zero error" << endl;
                        exit(0);
                    }
                    break;
                case '+':
                    stack->push(val2 + val1);
                    break;
                case '-':
                    stack->push(val2 - val1);
                    break;
                }
        }
    }

    //the top element remaining in the stack becomes the result
    double result = stack->getTopData();
    //free up memory
    delete stack;
    stack = nullptr;

    //return result
    return result;
}