#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB\Header\Follows.h"
#include "PKB\Header\Calls.h"
#include "PKB\Header\Parent.h"
#include "PKB\Header\Parser.h"
#include "PKB\Header\ProcTable.h"
#include "PKB\Header\stmtTable.h"
#include "PKB/Header/PKB.h"
#include "PKB/Header/Modifies.h"
#include "PKB/Header/VarTable.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestFollow)
		{

			int result;
			bool expectedIsFollow;
			bool resultIsFollow;
			int expectFollowFan;
			int resultFollowFan;
			std::vector<int>followFan;
			Parser::parse("C:\\Users\\feifei\\Source\\Repos\\CS3201-HappyPotatoes\\UnitTesting\\TestParser\\Sample-Source05.txt");

			// test for getFollow
			int expected_result01 = 0;
			vector<int> getFollow = stmtTable::getFollow(28);
			if (getFollow.size() == 0) {
				result = 0;
			}
			else {
				result = getFollow.front();
			}


			Assert::AreEqual(expected_result01, result);
		}

		TEST_METHOD(TestParent) {


			// test for getParent
			int result;
			bool isparent;
			bool expectBool;
			string expectedChildren;
			string resultChildren;
			std::vector<int> resultChild;
			int expected_result01 = 0;
			Parser::parse("C:\\Users\\feifei\\Source\\Repos\\CS3201-HappyPotatoes\\UnitTesting\\TestParser\\Sample-Source05.txt");
			vector<int> getParent = stmtTable::getParent(1);
			if (getParent.size() == 0) {
				result = 0;
			}
			else {
				result = getParent.front();
			}

			//			Parent pa;
			//			pa.PrintProcTable();

			Assert::AreEqual(expected_result01, result);
		}

		TEST_METHOD(TestModifies)
		{
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			string result, expectedResult = "";
			bool resultBoolean;
			vector<string> modifiesString;
			vector<int> modifiesInt;

			// Select v such that Modifies(13, v) => x
			modifiesString = VarTable::getModifiesVariable("13");
			expectedResult = "x";
			for (std::vector<string>::iterator it = modifiesString.begin(); it != modifiesString.end(); ++it) {
				result.append(*it);
			}
			Assert::AreEqual(expectedResult, result);
		}

	};
}