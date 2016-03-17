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
			vector<string> modifiesInt;

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
			modifiesString = ProcTable::getProcModifiesVar("ABC");
			expectedResult = "ABC,Second,";
			for (std::vector<string>::iterator it = modifiesString.begin(); it != modifiesString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}

			Assert::AreEqual(expectedResult, result);
		}
	};
}