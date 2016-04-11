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

		TEST_METHOD(TestGetStringType) {
			QueryEvaluator QE;
			string result;
			string answer = "CONSTANT";
			char c = 'C';
			result = QE.GetStringType(c);
			Assert::AreEqual(result, answer);

			result.clear();
			answer = "VAR";
			c = 'V';
			result = QE.GetStringType(c);
			Assert::AreEqual(result, answer);

			result.clear();
			answer = "ASSIGN";
			c = 'A';
			result = QE.GetStringType(c);
			Assert::AreEqual(result, answer);

			result.clear();
			answer = "PROC";
			c = 'P';
			result = QE.GetStringType(c);
			Assert::AreEqual(result, answer);

			result.clear();
			answer = "IF";
			c = 'I';
			result = QE.GetStringType(c);
			Assert::AreEqual(result, answer);

			result.clear();
			answer = "WHILE";
			c = 'W';
			result = QE.GetStringType(c);
			Assert::AreEqual(result, answer);

			result.clear();
			answer = "STMT";
			c = 'L';
			result = QE.GetStringType(c);
			Assert::AreEqual(result, answer);

			result.clear();
			answer = "";
			c = 'M';
			result = QE.GetStringType(c);
			Assert::AreEqual(result, answer);
		}

		TEST_METHOD(TestCheckTempResultSize) {
			QueryEvaluator QE;
			bool result;
			vector<string> v;
			result = QE.CheckTempResultSize(v);
			Assert::AreEqual(result, false);

			v.push_back("1");
			result = QE.CheckTempResultSize(v);
			Assert::AreEqual(result, true);
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

		TEST_METHOD(TestIsNumber) {
			QueryEvaluator QE;
			string test = "0";
			bool result = QE.IsNumber(test);
			Assert::AreEqual(result, true);

			test = 'c';
			result = QE.IsNumber(test);
			Assert::AreEqual(result, false);
		}

		TEST_METHOD(TestSplitString) {
			QueryEvaluator QE;
			string test = "Hi.There";
			pair<string, string> answer;
			answer.first = "Hi";
			answer.second = "There";
			pair<string, string> result = QE.SplitString(test);
			Assert::AreEqual(result.first, answer.first);
			Assert::AreEqual(result.second, answer.second);
		}
	};
}