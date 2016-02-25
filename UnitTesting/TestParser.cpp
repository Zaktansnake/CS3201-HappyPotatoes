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
			// normal
			int successCode = Parser::parse("..\\Release\\Sample-Source02.txt");

			Assert::AreEqual(1, successCode);

			//// normal - with special structure
			//successCode = Parser::parse("..\\Release\\sample-source02.txt");

			//Assert::AreEqual(1, successCode);

			//// normal - with special spacing style
			//successCode = Parser::parse("..\\Release\\Sample-Source03.txt");

			//Assert::AreEqual(1, successCode);

			//// only procedure line
			//successCode = Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Release\\Sample-Source04.txt");

			//Assert::AreEqual(-1, successCode);

			//// not starting with procedure
			//successCode = Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Release\\Sample-Source05.txt");

			//Assert::AreEqual(-1, successCode);

			//// empty file
			//successCode = Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Release\\Sample-Source07.txt");
			
			//Assert::AreEqual(-1, successCode);
		}
	};
}