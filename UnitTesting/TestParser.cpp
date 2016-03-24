#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPARSER)
	{
	public:
		TEST_METHOD(TestParser)
		{
			
			//normal
			int successCode = Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source01.txt");

			Assert::AreEqual(1, successCode);

			successCode = Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source04.txt");

			Assert::AreEqual(1, successCode);

			successCode = Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			Assert::AreEqual(1, successCode);
		}
	};
}