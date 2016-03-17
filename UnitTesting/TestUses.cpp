#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <algorithm> 
#include <vector> 
#include <string>

#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"
#include "../source/PKB/Header/Uses.h"
#include "../source/PKB/Header/VarTable.h"
#include "../source/PKB/Header/ProcTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(TestUSES)
	{
	public:
		TEST_METHOD(TestUses)
		{
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source04.txt");

			string result, expectedResult = "";
			bool resultBoolean;
			vector<string> usesString;
			vector<int> usesInt;

			// Select v such that Uses(11, v) => b,beta,c,chArLie,i,tmp
			usesString = VarTable::getUsesVariable("11");
			expectedResult = "b,beta,c,chArLie,i,tmp,";
			for (std::vector<string>::iterator it = usesString.begin(); it != usesString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select v such that Uses("ABC", v) => I,Romeo,a,b,beta,c,chArLie,chArlie,delta,i,j1k,k,l,left,oSCar,right,tmp,width,x
			usesString = ProcTable::getProcUsesVar("ABC");
			expectedResult = "I,Romeo,a,b,beta,c,chArLie,chArlie,delta,i,j1k,k,l,left,oSCar,right,tmp,width,x,";
			for (std::vector<string>::iterator it = usesString.begin(); it != usesString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select v such that Uses("X1x1", v) => none
			usesString = ProcTable::getProcUsesVar("X1x1");
			expectedResult = "";
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select p such that Uses(p,"x") => ABC,Second
			usesString = ProcTable::getUsesProc("x");
			expectedResult = "ABC,Second,";
			for (std::vector<string>::iterator it = usesString.begin(); it != usesString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select a such that Uses(a, "Romeo") => 17,19,31,33
			usesInt = VarTable::getUsesAssig("Romeo");
			expectedResult = "17,19,31,33,";
			for (std::vector<int>::iterator it = usesInt.begin(); it != usesInt.end(); ++it) {
				result.append(std::to_string(*it));
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select w such that Uses(w, "a") => none
			usesInt = VarTable::getUsesWhile("a");
			if (usesInt.empty()) {
				result = "";
			}
			expectedResult = "";
			Assert::AreEqual(expectedResult, result);

			// Select BOOLEAN such that Uses(23,"x") => true
			resultBoolean = VarTable::isUsesStmt("23", "x");
			Assert::IsTrue(resultBoolean);

			// Select BOOLEAN such that Uses(23,"x") => false
			resultBoolean = VarTable::isUsesWhile("23", "x");
			Assert::IsFalse(resultBoolean);

			// Select BOOLEAN such that Uses("Init","x1") => false
			resultBoolean = ProcTable::isUsesProc("Init", "x1");
			Assert::IsFalse(resultBoolean);

			// Select BOOLEAN such that Uses("Init","a") => true
			resultBoolean = ProcTable::isUsesProc("Init", "a");
			Assert::IsTrue(resultBoolean);


		}
	};
}