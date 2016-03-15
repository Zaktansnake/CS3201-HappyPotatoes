#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTesting)
	{
	public:
		TEST_METHOD(TestParse)
		{
			
			//normal
			int successCode = Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source02.txt");

			Assert::AreEqual(1, successCode);

			successCode = Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source02.txt");

			Assert::AreEqual(1, successCode);
		}
	};
}