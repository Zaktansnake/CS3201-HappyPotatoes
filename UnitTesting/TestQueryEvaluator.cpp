#include <iostream>
#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PQL/Header/QueryEvaluator.h"
#include "../source/PQL/Header/QueriesAnswerStorage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryEvaluator)
	{
	public:
		TEST_METHOD(TestQE) {

			string fileName = "..\Release\Sample-Source02.txt";

			Parser::parse(fileName);

			
		}
	};
}