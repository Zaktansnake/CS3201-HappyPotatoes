#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\source\PKB\Header\Parser.h"
#include "..\source\PKB\Header\ProcTable.h"
#include "..\source\PKB\Header\stmtTable.h"
#include "..\source\PKB\Header\VarTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestFollow)
		{

			string result;
			bool expectedIsFollow;
			bool resultIsFollow;
			int expectFollowFan;
			int resultFollowFan;
			std::vector<int>followFan;
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			// test for getFollow
			string expected_result01 = "0";
			vector<string> getFollow = stmtTable::getFollow(28);
			if (getFollow.size() == 0) {
				result = "0";
			}
			else {
				result = getFollow.front();
			}

			Assert::AreEqual(expected_result01, result);
		}

		TEST_METHOD(TestParent) {

			string result;
			string expected_result01 = "26";
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");
			vector<string> getParent = stmtTable::getParent(28);
			if (getParent.size() == 0) {
				result = "0";
			}
			else {
				result = getParent.front();
			}
			Assert::AreEqual(expected_result01, result);
		}

		TEST_METHOD(TestModifies)
		{
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			string result, expectedResult = "";
			bool resultBoolean;
			vector<string> modifiesString;

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