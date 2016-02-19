#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

#include "../Happy Potatoes SPA Tool/PKB/Header/Parser.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/PKB.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/VarTable.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/PatternTable.h"

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