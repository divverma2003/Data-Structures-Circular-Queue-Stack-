#include <iostream>
#include <string>
#include "CircularQueue.h"
using namespace std;

int main() {

	cout << "Welcome to Circular Queue:" << endl;
	cout << "--------------------------" << endl;


	//asks user for their preferred queue size
	cout << "What is the size of your queue?" << endl;
	int userQueueSize = -1;
	cin >> userQueueSize;

	//input validation
	if (cin.fail()) {
		cout << "ERROR: Terminating Program" << endl;
		return 0;
	}

	while (userQueueSize < 1) {
		cout << "Invalid size." << endl;
		cout << "What is the size of your queue?" << endl;
		cin >> userQueueSize;
	}

	//creates queue of chosen size
	CircularQueue<int> userQueue(userQueueSize);

	int userSelection = 0;

	//do-while loop that will allow user to build their custom queue
	do {
		cout << endl << "Here are your options: " << endl;
		cout << "1 Enqueue" << endl;
		cout << "2 Dequeue" << endl;
		cout << "3 Display" << endl;
		cout << "4 Exit" << endl;
		cout << "Enter Number: ";
		cin >> userSelection;
		
		//terminates program if user enters a non-integer value
		if (cin.fail()) {
			cout << "ERROR: Terminating Program" << endl;
			return -1;
		}

		//switch case statements to handle user requests
		switch (userSelection) {
			case 1:
				cout << "Enter an integer to enqueue: " ;
				int val;
				cin >> val;
				userQueue.enqueue(val);
				break;
			case 2:
				userQueue.dequeue();
				break;
			case 3:
				userQueue.display();
				break;
			case 4:
				cout << "PROGRAM_FIN" << endl;
				break;
			default:
				cout << "Invalid selection." << endl;
				break;
			}

	} while (userSelection != 4);

	return 0;
}