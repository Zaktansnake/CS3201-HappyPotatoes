#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <algorithm> 
#include <vector> 
#include <string>

#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"
#include "../source/PKB/Header/Uses.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(TestUSES)
	{
	public:
		TEST_METHOD(TestUses)
		{
			string expected_result01 = "1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 15, ";
			string result;
			Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Happy Potatoes SPA Tool\\UnitTesting\\Sample-Source.txt");
			vector<int> modifiesTable = Uses::getUsesTable("x");
			std::sort(modifiesTable.begin(), modifiesTable.end());

			for (std::vector<int>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); ++it) {
				result.append(std::to_string(*it));
				result.append(", ");
			}

			Assert::AreEqual(expected_result01, result);
		}
	};
}