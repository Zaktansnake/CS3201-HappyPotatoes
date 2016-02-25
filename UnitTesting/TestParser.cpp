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
			/*int successCode = Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Happy Potatoes SPA Tool\\UnitTesting\\Sample-Source.txt");
			Assert::AreEqual(1, successCode);

			successCode = Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Happy Potatoes SPA Tool\\UnitTesting\\Sample-Source02.txt");
			Assert::AreEqual(1, successCode);*/

			int successCode = Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Happy Potatoes SPA Tool\\UnitTesting\\Sample-Source04.txt");
			Assert::AreEqual(-1, successCode);

			/*successCode = Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Happy Potatoes SPA Tool\\UnitTesting\\Sample-Source05.txt");
			Assert::AreEqual(-1, successCode);*/
		}
	};
}