#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

#include "./PKB/Header/Parser.h"
#include "./PKB/Header/PKB.h"
#include "./PKB/Header/VarTable.h"
#include "./PKB/Header/PatternTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestGetPattern)
	{
	public:
		TEST_METHOD(TestisPattern) {

			// test for isPattern
			
			bool expected_result01 = true;
			Parser::parse("C:\\Users\\feifei\\Downloads\\TestFollow.txt");

			bool ispattern = PatternTable::isPattern("z","z+x+i");
			

			Assert::AreEqual(expected_result01, ispattern);


			//test for getAssign

			string expected_result = "3578";
			string result;
			vector<int>getPattern = PatternTable::getAssign("x");
			for (std::vector<int>::iterator it = getPattern.begin(); it != getPattern.end(); ++it) {
				result.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expected_result, result);


			// test for getAssignWithVar
			string expected_result_vat = "58";
			string resultVar;
			getPattern = PatternTable::getAssignWithVar("z","x");
			for (std::vector<int>::iterator it = getPattern.begin(); it != getPattern.end(); ++it) {
				resultVar.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expected_result_vat, resultVar);
			
		}
	};
}