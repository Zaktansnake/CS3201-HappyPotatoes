#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/Parser.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(UnitTesting)
	{
	public:
		TEST_METHOD(TestParse)
		{
			int successCode = Parser::parse("C:\\Users\\feifei\\Downloads\\TestFollow.txt");
			Assert::AreEqual(1, successCode);
		}
	};
}