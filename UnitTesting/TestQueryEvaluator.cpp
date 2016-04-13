#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PQL/Header/QueryEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryEvaluator)
	{
	public:
		TEST_METHOD(TestReturnResultsExist) {
			QueryEvaluator QE;
			bool result;
			vector<bool> re;
			re.push_back(true);
			result = QE.ReturnResultsExist(re);
			Assert::AreEqual(result, true);

			re.clear();
			re.push_back(false);
			result = QE.ReturnResultsExist(re);
			Assert::AreEqual(result, false);
		}

		TEST_METHOD(TestIsSynonym) {
			QueryEvaluator QE;
			char c = '0';
			bool result = QE.IsSynonym(c);
			Assert::AreEqual(result, false);

			c = 'c';
			result = QE.IsSynonym(c);
			Assert::AreEqual(result, true);
		}

		TEST_METHOD(TestChangeStringToInt) {
			QueryEvaluator QE;
			string test = "1";
			int answer = 1;
			int result = QE.ChangeStringToInt(test);
			Assert::AreEqual(result, answer);

			test = "11";
			answer = 11;
			result = QE.ChangeStringToInt(test);
			Assert::AreEqual(result, answer);
		}

		TEST_METHOD(TestChangeIntToString) {
			QueryEvaluator QE;
			int test = 1;
			string answer = "1";
			string result = QE.ChangeIntToString(test);
			Assert::AreEqual(result, answer);

			test = 11;
			answer = "11";
			result = QE.ChangeIntToString(test);
			Assert::AreEqual(result, answer);
		}

		TEST_METHOD(TestHaveQuotation) {
			QueryEvaluator QE;
			string test = "This string has a \"quotation\"";
			bool result = QE.HaveQuotation(test);
			Assert::AreEqual(result, true);

			test = "This string does not have a quotation";
			result = QE.HaveQuotation(test);
			Assert::AreEqual(result, false);
		}
	};
}