#include <iostream>
#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/Affects.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestAffects)
	{
	public:
		TEST_METHOD(TestAffectsTable) {
			
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			string result, expectedResult = "";
			bool resultBoolean;
			vector<string> affectsString;

			affectsString = Affects::getAffectsRight("1");
			expectedResult = "10,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			affectsString = Affects::getAffectsRight("2");
			expectedResult = "10,11,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsRight("3");
			expectedResult = "10,11,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsRight("10");
			expectedResult = "10,11,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsRight("13");
			expectedResult = "13,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsRight("17");
			expectedResult = "19,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsRight("22");
			expectedResult = "22,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsRight("31");
			expectedResult = "33,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsRight("36");
			expectedResult = "36,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsTransitiveRight("1");
			expectedResult = "10,11,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsTransitiveRight("36");
			expectedResult = "36,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);

			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsLeft("10");
			expectedResult = "1,2,3,10,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);
			
			result = "";
			expectedResult = "";
			affectsString = Affects::getAffectsTransitiveLeft("10");
			expectedResult = "1,2,3,10,";
			for (std::vector<string>::iterator it = affectsString.begin(); it != affectsString.end(); ++it) {
				result.append(*it);
				result.append(",");
			}
			Assert::AreEqual(expectedResult, result);
		}
	};
}