
#include <iostream>
using namespace std;

#pragma once
//Node class
class OperatorNode
{
public:
	char data;
	OperatorNode* next = nullptr;

	OperatorNode(char data) {
		this->data = data;
	}

	~OperatorNode() {
		next = nullptr;
	}
};


//OperatorStack class --> using linked list implementation
#pragma once
class OperatorStack
{
	private: 
		OperatorNode* top;
		int size;

	public:
		//default constructor
		OperatorStack() {
			size = 0;
			top = nullptr;
		}
		
		//constructor with parameters
		OperatorStack(OperatorNode* top) {
			size = 0;
			this->top = top;
		}

		//destructor
		~OperatorStack() {
			OperatorNode* temp;
			while (top != nullptr) {
				temp = top;
				top = top->next;
				delete temp;
			}
			size = 0;
		}

		//function that returns the data from top
		char getTopData() {
			if (!isEmpty()) 
				return top->data;
			return NULL;
		}

		//function that pushes elements onto the stack
		void push(char data) {
			if (isEmpty()) {
				top = new OperatorNode(data);
				size++;
				return;
			}

			OperatorNode* temp = new OperatorNode(data);
			temp->next = top;
			top = temp;
			size++;
		}

		//function that removes the 'top' element from stack
		char pop() {
			if (isEmpty()) {
				cerr << "Stack is empty!" << endl;
				return NULL;
			}
			char storedData = top->data;
			OperatorNode* temp = top;
			top = top->next;
			
			delete temp;
			temp = nullptr;

			size--;

			return storedData;
		}

		//function that displays elements on the stack, starting from TOP
		void display() {
			if (isEmpty()) {
				cerr << "Stack is empty!" << endl;
				return;
			}
			cout << "Contents of Stack (Size " << size << "):" << endl;
			cout << "---------------------------" << endl;

			OperatorNode* temp = top;
			while (temp != nullptr) {
				cout << temp->data << endl;
				temp = temp->next;
				if (temp == nullptr)
					cout << "End of stack" << endl;
			}
			cout << endl;
		}

		//function that checks if stack is empty
		bool isEmpty() {
			return (top == nullptr && size == 0);
		}

		int getSize() {
			return size;
		}

};