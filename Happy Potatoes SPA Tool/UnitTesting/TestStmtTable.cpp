#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

#include "../Happy Potatoes SPA Tool/PKB/Header/Parser.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/PKB.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/stmtTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestStmtTable)
	{
	public:
		TEST_METHOD(TestFollow)
		{
			int expected_result01 = 2;
			int result;
			Parser::parse("C:\\Users\\feifei\\Downloads\\TestFollow.txt");

			vector<int> getFollow = stmtTable::getFollow(1);
			result = getFollow.front();

			Assert::AreEqual(expected_result01, result);

			result = 0;
			getFollow.clear();
			expected_result01 = 1;
			getFollow = stmtTable::getFollow(12);
			result = getFollow.front();

			Assert::AreEqual(expected_result01, result);
/*
			result = "";
			modifiesTable.clear();
			expected_result01 = "368";
			modifiesTable = Modifies::getModifiesTable("i");

			for (std::vector<int>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); ++it) {
				result.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expected_result01, result);

			result = "";
			modifiesTable.clear();
			expected_result01 = "34";
			modifiesTable = Modifies::getModifiesTable("z");

			for (std::vector<int>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); ++it) {
				result.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expected_result01, result);

			result = "";
			modifiesTable.clear();
			expected_result01 = "359";
			modifiesTable = Modifies::getModifiesTable("t");

			for (std::vector<int>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); ++it) {
				result.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expected_result01, result);
*/
		}
	};
}