#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include<cstring>
#include<stack>
#include<map>

#include "./Header/Patterns.h"

using namespace std;

map<int, string> FinalPatternTable;

int getWeight(string ch);
string infix2postfix(vector<string> infix);

Patterns::Patterns() {
}

Patterns::~Patterns() {
}

enum operator_code {
	ePlus,
	eMinus,
	eTimes,
	eNormal
};

bool Patterns::compareAssignments(string assignment1, string assignment2, int stmtNum) {
	string s1, s2;
	vector<string> assig1 = Patterns::getRidOfWhiteSpaces(assignment1);
	vector<string> assig2 = Patterns::getRidOfWhiteSpaces(assignment2);

	if (FinalPatternTable.count(stmtNum)) {
		s1 = FinalPatternTable[stmtNum];
		s2 = infix2postfix(assig2);
	}
	else {
		s1 = infix2postfix(assig1);
		FinalPatternTable.insert(pair<int, string>(stmtNum, s1));
		s2 = infix2postfix(assig2);
	}

	if (s1.find(s2) != std::string::npos) {
		return true;
	}
	return false;
}


string infix2postfix(vector<string> infix) {
	stack<string> s;
	int weight;
	int i = 0;
	int k = 0;
	string tempStr, finalString = "";

	while (i < infix.size()) {
		tempStr = infix[i];
		if (tempStr.compare("(") == 0) {
			s.push(tempStr);
			i++;
			continue;
		}
		if (tempStr.compare(")") == 0) {
			while (!s.empty() && s.top().compare("(") != 0) {
				finalString.append(s.top());
				s.pop();

			}
			if (!s.empty()) {
				s.pop();
			}
			i++;
			continue;
		}
		weight = getWeight(tempStr);
		if (weight == 0) {
			finalString.append(tempStr);

		}
		else {
			if (s.empty()) {
				s.push(tempStr);
			}
			else {
				while (!s.empty() && (s.top().compare("(") != 0) && weight <= getWeight(s.top())) {
					finalString.append(s.top());
					s.pop();
				}
				s.push(tempStr);
			}
		}
		i++;
	}
	while (!s.empty()) {
		finalString.append(s.top());
		s.pop();
	}
	return finalString;
}

operator_code hashit(std::string const& inString) {
	if (inString == "+") return ePlus;
	if (inString == "-") return eMinus;
	if (inString == "*") {
		return eTimes;
	}
	else {
		return eNormal;
	}
}

int getWeight(string ch) {
	switch (hashit(ch)) {
	case eTimes: return 2;
	case ePlus:
	case eMinus: return 1;
	default: return 0;
	}
}

vector<string> Patterns::getRidOfWhiteSpaces(string line) {
	vector<string> v;
	istringstream buf(line);

	for (string word; buf >> word;) {
		v.push_back(word);
	}

	return v;
}
