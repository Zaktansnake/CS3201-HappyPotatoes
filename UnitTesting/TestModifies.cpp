#include <iostream>
#include <algorithm> 
#include <vector> 
#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"
#include "../source/PKB/Header/Modifies.h"
#include "../source/PKB/Header/VarTable.h"
#include "../source/PKB/Header/ProcTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestMODIFIES)
	{
	public:
		TEST_METHOD(TestModifies)
		{

			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source04.txt");

			string result, expectedResult = "";
			vector<string> modifiesString;
			vector<int> modifiesInt;

			// Select v such that Modifies(13, v) => x
			modifiesString = VarTable::getModifiesVariable("13");
			expectedResult = "x";
			for (std::vector<string>::iterator it = modifiesString.begin(); it != modifiesString.end(); ++it) {
				result.append(*it);
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select v such that Modifies("ABC", v) => Romeo,Y1,b,c,i,oSCar,x,x1
			modifiesString = ProcTable::getProcModifiesVar("ABC");
			expectedResult = "Romeo,Y1,b,c,i,oSCar,x,x1,";
			for (std::vector<string>::iterator it = modifiesString.begin(); it != modifiesString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}

			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select v such that Modifies("X1x1", v) => none
			modifiesString = ProcTable::getProcModifiesVar("X1x1");
			expectedResult = "";
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select p such that Modifies(p,"x") => ABC,Second
			modifiesString = ProcTable::getModifiesProc("x");
			expectedResult = "ABC,Second,";
			for (std::vector<string>::iterator it = modifiesString.begin(); it != modifiesString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}

			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select w such that Modifies(w, "Romeo") => 12
			modifiesInt = VarTable::getModifiesWhile("Romeo");
			expectedResult = "12,";
			for (std::vector<int>::iterator it = modifiesInt.begin(); it != modifiesInt.end(); ++it) {
				result.append(std::to_string(*it));
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select a such that Modifies(a, "Romeo") => 17,31
			modifiesInt = VarTable::getModifiesAssign("Romeo");
			expectedResult = "17,31,";
			for (std::vector<int>::iterator it = modifiesInt.begin(); it != modifiesInt.end(); ++it) {
				result.append(std::to_string(*it));
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select s such that Modifies(s, "Romeo") => 12,14,15,16,17,26,28,30,31,4
			modifiesInt = VarTable::getModifiesStmt("Romeo");
			expectedResult = "4,12,14,15,16,17,26,28,30,31,";
			for (std::vector<int>::iterator it = modifiesInt.begin(); it != modifiesInt.end(); ++it) {
				result.append(std::to_string(*it));
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);
		}
	};
}