#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

#include "../Happy Potatoes SPA Tool/PKB/Header/Parser.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/PKB.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/Modifies.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestModifies)
	{
	public:
		TEST_METHOD(TestModifiesTable)
		{
			string expected_result01 = "1";
			string result;
			Parser::parse("C:\\Users\\jiaminn\\Desktop\\NUS\\Y2S2\\CS3201 & CS3202\\Project\\CS3201-HappyPotatoes\\Happy Potatoes SPA Tool\\UnitTesting\\Sample-Source.txt");

			vector<int> modifiesTable = Modifies::getModifiesTable("x");

			for (std::vector<int>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); ++it) {
				result.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expected_result01, result);

			result = "";
			modifiesTable.clear();
			expected_result01 = "2367";
			modifiesTable = Modifies::getModifiesTable("y");

			for (std::vector<int>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); ++it) {
				result.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expected_result01, result);

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

		}
	};
}