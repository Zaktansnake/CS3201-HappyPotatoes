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
		TEST_METHOD(CFG)
		{
			Parser::parse("C:\\Users\\feifei\\Source\\Repos\\CS3201-HappyPotatoes\\UnitTesting\\TestParser\\Sample-Source06.txt");

			string result;
			string expectedResult;
			vector<int> actual; 
			int expectBoo;
			bool resultBoo;
			int resultB;

			expectedResult = "21";
			actual = CFG::getNext(20);
			for (std::vector<int>::iterator it = actual.begin(); it != actual.end(); ++it) {
				result.append(std::to_string(*it));
			}

			Assert::AreEqual(expectedResult, result);

			//test getPrev
			result.clear();
			expectedResult = "69";
			actual = CFG::getPrev(7);
			for (std::vector<int>::iterator it = actual.begin(); it != actual.end(); ++it) {
				result.append(std::to_string(*it));
			}

			Assert::AreEqual(expectedResult, result);
			// test isNext
			expectBoo = 0;
			resultBoo = CFG::isNext(10, 12);
			if (resultBoo) {
				resultB = 1;
			}
			else {
				resultB = 0;
			}
			Assert::AreEqual(expectBoo, resultB);

			//test get next*

			result.clear();
			expectedResult = "69";
			actual = CFG::getNextStar(1);
			for (std::vector<int>::iterator it = actual.begin(); it != actual.end(); ++it) {
				result.append(std::to_string(*it));
			}

			Assert::AreEqual(expectedResult, result);



		}
	};
}