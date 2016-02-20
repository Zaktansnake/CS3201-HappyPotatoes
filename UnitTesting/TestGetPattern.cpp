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
		}
	};
}