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
			int successCode = Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Happy Potatoes SPA Tool\\UnitTesting\\Sample-Source.txt");
			Assert::AreEqual(1, successCode);
		}

		TEST_METHOD(TestCreate)
		{
			
		}

	};
}