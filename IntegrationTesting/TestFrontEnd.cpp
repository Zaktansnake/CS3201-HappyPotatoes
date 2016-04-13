#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\source\PKB\Header\Parser.h"
#include "..\source\PKB\Header\ProcTable.h"
#include "..\source\PKB\Header\stmtTable.h"
#include "..\source\PKB\Header\VarTable.h"
#include "..\source\PKB\Header\CFG.h"
#include "..\source\PQL\Header\ParseResult.h"
#include "..\source\PQL\Header\QueryEvaluator.h"


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

		TEST_METHOD(TestUses)
		{
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			string result, expectedResult = "";
			bool resultBoolean;
			vector<string> usesString;

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
		}


		TEST_METHOD(CFG)
		{
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source06.txt");

			string result;
			string expectedResult;
			vector<int> actual;
			int expectBoo;
			bool resultBoo;
			int resultB;

			expectedResult = "1318";
			actual = CFG::getNext(12);
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
			expectBoo = 1;
			resultBoo = CFG::isNext(20, 21);
			if (resultBoo) {
				resultB = 1;
			}
			else {
				resultB = 0;
			}
			Assert::AreEqual(expectBoo, resultB);

			//test get next*

			result.clear();
			expectedResult = "61213181417151678591011";
			actual = CFG::getNextStar(5);
			for (std::vector<int>::iterator it = actual.begin(); it != actual.end(); ++it) {
				result.append(std::to_string(*it));

			}

			Assert::AreEqual(expectedResult, result);


			//test get prev*

			result.clear();
			expectedResult = "2021";
			actual = CFG::getPrevStar(21);
			for (std::vector<int>::iterator it = actual.begin(); it != actual.end(); ++it) {
				result.append(std::to_string(*it));

			}

			Assert::AreEqual(expectedResult, result);

			// test isNextStar
			expectBoo = 0;
			resultBoo = CFG::isNextStar(5, 21);
			if (resultBoo) {
				resultB = 1;
			}
			else {
				resultB = 0;
			}
			Assert::AreEqual(expectBoo, resultB);

		}

	};
}