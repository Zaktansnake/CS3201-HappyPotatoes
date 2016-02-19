#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../AutoTester/source/TestWrapper.h"

using namespace std;

void printResult(vector<string> result);
void printExit();

int main() {
	string fileName = "../Testing/testcases/testIndex.txt";
	TestWrapper w;
	cout << "*********************************" << endl;
	cout << "*        SPA Tool v1.0.0        *" << endl;
	cout << "*    Happy Potatoes - Team 1    *" << endl;
	cout << "*********************************" << endl;
	cout << endl;

	while (true) {
		cout << ">> Please input the full filepath to the SIMPLE source code:" << endl;
		cout << ">> If you do not wish to input a filepath, simply press 0 to exit." << endl;
		getline(cin, fileName);
		if (fileName == "0") { printExit(); return 0; }
		try {
			w.parse(fileName);
			cout << "Parse OK." << endl << endl;
			break;
		}
		catch (exception& e)
		{
			cout << e.what() << endl << endl;
		}
	}

	string q; list<string> result;
	cout << ">> Please enter your PQL queries here:" << endl;
	cout << ">> If you do not wish to enter any queries, simple press 0 to exit." << endl;
	while (true) {
		cout << ">> ";
		getline(cin, q);
		if (q == "0") { printExit(); return 0; }
		try {
			w.evaluate(q, result);
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
		cout << endl;
	}
	printExit();
	return 0;
}

void printResult(vector<string> result) {
	if (result.size() == 0) cout << "none" << endl;
	else {
		for (unsigned i = 0; i < result.size(); i++) {
			if (i) cout << ", ";
			cout << result[i];
		}
		cout << endl;
	}
}

void printExit() {
	cout << "Thank you for using Happy Potatoes SPA Tool! Have a nice day!" << endl;
}