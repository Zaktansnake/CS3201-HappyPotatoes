#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <algorithm> 
#include <vector> 
#include <string>

#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/ProcTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(TestCALLS)
	{
	public:
		TEST_METHOD(TestCalls)
		{
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			string result, expectedResult = "";
			bool resultBoolean;
			vector<string> callsString;
			vector<int> callsInt;

			// Select p such that Calls("ABC", p) => Init,Second
			callsString = ProcTable::getNextProcedure("ABC");
			expectedResult = "Init,Second,";
			for (std::vector<string>::iterator it = callsString.begin(); it != callsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select p such that Calls*("x1Y1", p) => none
			callsString = ProcTable::getNextProcedure("x1Y1");
			expectedResult = "";
			if (callsString.empty()) {
				result = "";
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select p such that Calls*("ABC", p) => Init,Second
			callsString = ProcTable::getNextProcedureTransitive("ABC");
			expectedResult = "Init,Second,";
			for (std::vector<string>::iterator it = callsString.begin(); it != callsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select p such that Calls(p, "Second")=> ABC
			callsString = ProcTable::getParentProcedure("Second");
			expectedResult = "ABC,";
			for (std::vector<string>::iterator it = callsString.begin(); it != callsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			// Select p such that Calls*(p, "Second") => ABC
			callsString = ProcTable::getParentProcedureTransitive("Second");
			expectedResult = "ABC,";
			for (std::vector<string>::iterator it = callsString.begin(); it != callsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			// Select BOOLEAN such that Calls("ABC","Second") => true
			resultBoolean = ProcTable::isProcToProc("ABC", "Second");
			Assert::IsTrue(resultBoolean);

			// Select BOOLEAN such that Calls("ABC","xxx") => false
			resultBoolean = ProcTable::isProcToProc("ABC", "xxx");
			Assert::IsFalse(resultBoolean);

			// Select BOOLEAN such that Calls("ABC","Second") => true
			resultBoolean = ProcTable::isProcToProcTransitive("ABC", "Second");
			Assert::IsTrue(resultBoolean);

			// Select BOOLEAN such that Calls*("ABC","First") => false
			resultBoolean = ProcTable::isProcToProcTransitive("ABC", "First");
			Assert::IsFalse(resultBoolean);
		}
	};
}