#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <algorithm> 
#include <vector> 
#include <string>

#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"
#include "../source/PKB/Header/Modifies.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestMODIFIES)
	{
	public:
		TEST_METHOD(TestModifies)
		{
			string expected_result01 = "3, 4, 8, 9, 10, 11, 14, 17, "; 
			string result;
			Parser::parse("..\\Release\\Sample-Source02.txt");

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