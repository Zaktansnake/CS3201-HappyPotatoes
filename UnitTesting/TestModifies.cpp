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
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			string result, expectedResult = "";
			bool resultBoolean;
			vector<string> modifiesString;

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
			if (modifiesString.empty()) {
				result = "";
			}
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
			modifiesString = VarTable::getModifiesWhile("Romeo");
			expectedResult = "12,";
			for (std::vector<string>::iterator it = modifiesString.begin(); it != modifiesString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select a such that Modifies(a, "Romeo") => 17,31
			modifiesString = VarTable::getModifiesAssign("Romeo");
			expectedResult = "17,31,";
			for (std::vector<string>::iterator it = modifiesString.begin(); it != modifiesString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			// Select BOOLEAN such that Modifies(23,"x") => true
			resultBoolean = VarTable::isModifiesStmt("23", "x");
			Assert::IsTrue(resultBoolean);

			// Select BOOLEAN such that Modifies(23,"x") => false
			resultBoolean = VarTable::isModifiesWhile("23", "x");
			Assert::IsFalse(resultBoolean);

			// Select BOOLEAN such that Modifies("Init","x1") => true
			resultBoolean =	ProcTable::isModifiesProc("Init", "x1");
			Assert::IsTrue(resultBoolean);

			// Select BOOLEAN such that Modifies("Init","x1") => false
			resultBoolean = ProcTable::isModifiesProc("Init", "a");
			Assert::IsFalse(resultBoolean);

			result = "";
			// Select s such that Modifies(s, "Romeo") => 12,14,15,16,17,26,28,30,31,4
			modifiesString = VarTable::getModifiesStmt("Romeo");
			expectedResult = "4,12,14,15,16,17,26,28,30,31,";
			for (std::vector<string>::iterator it = modifiesString.begin(); it != modifiesString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);
		}
	};
}