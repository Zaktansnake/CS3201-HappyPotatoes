#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <algorithm> 
#include <vector> 
#include <string>

#include "./PKB/Header/Parser.h"
#include "./PKB/Header/PKB.h"
#include "./PKB/Header/Modifies.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestModifies)
	{
	public:
		TEST_METHOD(TestModifiesTable)
		{
			string expected_result01 = "2, 3, 6, 9, 10, 11, "; 
			string result;
			Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Happy Potatoes SPA Tool\\UnitTesting\\Sample-Source.txt");

			vector<int> modifiesTable = Modifies::getModifiesTable("x");
			std::sort(modifiesTable.begin(), modifiesTable.end());
			for (std::vector<int>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); ++it) {
				result.append(std::to_string(*it));
				result.append(", ");
			}

			Assert::AreEqual(expected_result01, result);
		}
	};
}