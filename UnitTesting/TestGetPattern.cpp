#include <iostream>
#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PatternTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPattern)
	{
	public:
		TEST_METHOD(TestPatternTable) {
			
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			string result, expectedResult = "";
			bool resultBoolean;
			vector<string> patternString;

			// test for isPattern
			bool expected_result = true;
			bool ispattern = PatternTable::isPattern("c", " c - 1 ");
			Assert::AreEqual(expected_result, ispattern);

			// Select a pattern a("x",_)
			patternString = PatternTable::getPatternAssignNum("x", "_");
			expectedResult = "13,23,37,";
			for (std::vector<string>::iterator it = patternString.begin(); it != patternString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			// Select a pattern a(_,"c - 1")
			patternString = PatternTable::getPatternAssignNum("_", "c - 1");
			expectedResult = "22,36,";
			for (std::vector<string>::iterator it = patternString.begin(); it != patternString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			// Select a pattern a("c",_"c"_)
			patternString = PatternTable::getPatternAssignNum("c", "_\"c\"_");
			expectedResult = "22,36,";
			for (std::vector<string>::iterator it = patternString.begin(); it != patternString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			// Select a pattern a("_","_")
			patternString = PatternTable::getPatternAssignNum("_", "_");
			expectedResult = "1,2,3,6,8,10,11,13,17,18,19,22,23,27,31,32,33,36,37,40,";
			for (std::vector<string>::iterator it = patternString.begin(); it != patternString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			// Select a pattern a("c",_"c -1"_)
			patternString = PatternTable::getPatternAssignNum("c", "_\"c - 1\"_");
			expectedResult = "22,36,";
			for (std::vector<string>::iterator it = patternString.begin(); it != patternString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);


		}
	};
}