#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(UnitTesting)
	{
	public:
		TEST_METHOD(TestParse)
		{
			int successCode = Parser::parse("Sample-Source.txt");
			Assert::AreEqual(1, successCode);
		}
	};
}