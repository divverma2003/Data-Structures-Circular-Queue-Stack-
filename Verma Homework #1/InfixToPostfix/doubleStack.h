#include <iostream>
using namespace std;

//Node class
#pragma once
class Node
{
	public:
		double data;
		Node* next = nullptr;

		Node(double data) {
			this->data = data;
		}

		~Node() {
			next = nullptr;
		}
};

#pragma once
//DoubleStack class --> using linked list implementation
class DoubleStack
{
private:
	Node* top;
	int size;

public:
	//default constructor
	DoubleStack() {
		size = 0;
		top = nullptr;
	}

	//constructor with parameters
	DoubleStack(Node* top) {
		size = 0;
		this->top = top;
	}

	//destructor
	~DoubleStack() {
		Node* temp;
		while (top != nullptr) {
			temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}

	//function that returns the data from top
	double getTopData() {
		if (!isEmpty())
			return top->data;
		return NULL;
	}

	//function that pushes elements onto the stack
	void push(double data) {
		if (isEmpty()) {
			top = new Node(data);
			size++;
			return;
		}

		Node* temp = new Node(data);
		temp->next = top;
		top = temp;
		size++;
	}

	//function that removes the 'top' element from stack
	double pop() {
		if (isEmpty()) {
			cerr << "Stack is empty!" << endl;
			return NULL;
		}
		double storedData = top->data;
		Node* temp = top;
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

		Node* temp = top;
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