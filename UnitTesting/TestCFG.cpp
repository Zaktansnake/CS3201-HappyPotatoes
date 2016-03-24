#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <algorithm> 
#include <vector> 
#include <string>

#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"
#include "../source/PKB/Header/CFG.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestCFG)
	{
	public:
		TEST_METHOD(TestforCFG)
		{
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			int result;
			int expectedResult;
			vector<int> actual; 

			expectedResult = 1;
			actual = CFG::getNext(1);
			if (actual.size() == 0) {
				result = 0;
			}
			else {
				result = actual.front();
			}

			Assert::AreEqual(expectedResult, result);




		}
	};
}