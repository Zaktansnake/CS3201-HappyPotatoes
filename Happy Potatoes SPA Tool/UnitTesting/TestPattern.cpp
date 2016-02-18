#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

#include "../Happy Potatoes SPA Tool/PKB/Header/Parser.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/PKB.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/Pattern.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPATTERN)
	{
	public:
		TEST_METHOD(TestPattern) {
			Pattern p;
			string testPattern, expectedPattern, returnedPattern;

			// test for patternAssignment
			testPattern = "a+b+c+d";
			expectedPattern = "(a+b)+c+d";
			Parser::parse("C:\\Users\\David_Chong\\Desktop\\TestPattern.txt");

			returnedPattern = p.patternAssignment(testPattern);
			
			Assert::AreEqual(expectedPattern, returnedPattern);

			testPattern = "a*b+c+d";
			expectedPattern = "(a*b)+c+d";
			Parser::parse("C:\\Users\\David_Chong\\Desktop\\TestPattern.txt");

			returnedPattern = p.patternAssignment(testPattern);

			Assert::AreEqual(expectedPattern, returnedPattern);

			testPattern = "a*b+(c-d)";
			expectedPattern = "(a*b)+(c-d)";
			Parser::parse("C:\\Users\\David_Chong\\Desktop\\TestPattern.txt");

			returnedPattern = p.patternAssignment(testPattern);

			Assert::AreEqual(expectedPattern, returnedPattern);
		}
}