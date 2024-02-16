#include <iostream>
using namespace std;
#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H
template<typename T>
class CircularQueue
{

private:
		//member variables
		int size;
		int front;
		int back;
		T* circularQueue;
public:
		//default constructor
		CircularQueue() {
			size = 10;
			circularQueue = new T[size];
			front = back = -1;
		}

		//constructor with parameters
		CircularQueue(int size) {
			this->size = size;
			circularQueue = new T[size];
			front = back = -1;
		}

		//destructor
		~CircularQueue() {
			delete[] circularQueue;
			circularQueue = nullptr;
			front = back = size = -1;
		}

		//getter methods
		int getSize() {
			return size;
		}

		int getFront() {
			return front;
		}

		int getBack() {
			return back;
		}

		T* getQueue() {
			return circularQueue;
		}

		//method that checks if queue is empty
		bool isEmpty() {
			if (front < 0)
				return true;
			return false;
		}

		//method that checks if queue is full
		bool isFull() {
			//queue is considered full if 'back' is right behind 'front' or if front is '0' and back has reached the size limit 
			// of the queue
			if ((back == front - 1) || (front == 0 && back == size - 1))
				return true;
			return false;
		}

		//method that adds elements to the queue
		void enqueue(T data) {
			//if full: outputs the following
			if (isFull()) {
				cerr << "ERROR: Queue is full!\n";
				return;
			}
			else if (isEmpty())
				front = back = 0;
			else
				back = (back + 1) % size; //sets the index for back

			//adds elment to back and outputs message
			circularQueue[back] = data;
			cout << "Enqueue [" << back << "]: " << data << endl;
		}

		//method that removes the front element
		T dequeue() {
			T data;
			//if empty: display error message
			//terminate method
			if (isEmpty()) {
				cerr << "ERROR: Queue is empty!\n";
				return T();
			}
			//if queue only has one element, resets queue to empty state
			else if (front == back) {
				data = circularQueue[front];
				front = back = -1;
			}
			//otherwise, moves front forward by one
			else {
				data = circularQueue[front];
				front = (front + 1) % size;
			}

			//displays element that was removed
			cout << "Dequeue: " << data << endl;
			return data;
		}

		//function to display the contents of the queue
		void display() {
			//if empty outputs the following
			if (isEmpty()) {
				cout << "Empty Queue" << endl;
				return;
			}

			//iterator variable, starts at front
			int iterator = front;

			cout << endl << "Displaying Queue: " << endl;
			cout << "-----------------" << endl;
			//while iterator isn't equal to the back index
			while (iterator != (back) % size) {
				if (iterator == front)
					cout << "FRONT: ";

				//display current element
				cout << circularQueue[iterator] << " ";
				//iterate
				iterator = (iterator + 1) % size;
			}

			//if iterator is equal to the back index, print the back of the queue
			if (iterator == back)
				cout << "BACK: " << circularQueue[iterator] << endl;
		}
};
#endif