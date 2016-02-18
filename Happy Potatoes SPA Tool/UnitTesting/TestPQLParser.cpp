#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Happy Potatoes SPA Tool/PQL/Header/ParseResult.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestPQLParser_VS2015 {
	TEST_CLASS(TestParseResult) {
	public:
		TEST_METHOD(testCheckAndParseDeclaration) {
			ParseResult parseR;
			bool correct = parseR.checkAndParseDeclaration("assign a; variable v");
			Assert::AreEqual(true, correct);

			return;
		}

		TEST_METHOD(testCheckAndParseQuery) {
			ParseResult parseR;
			parseR = parseR.checkAndParseQuery("Select s such that Parent (2, s) pattern a (\"x\", _)");
			ParameterSet selectSet = parseR.getSelectParameter();
			ClauseSet cSet = parseR.getClauses();
			PatternSet patSet = parseR.getPatterns();
			string select = selectSet.at(0);
			Clause clause = cSet.at(0);
			Pattern pattern = patSet.at(0);
			string cType = clause.getClauseOperation();
			string cP1 = clause.getFirstParameter();
			string cP2 = clause.getSecondParameter();
			string patT = pattern.getPatternOperation();
			string patP1 = pattern.getFirstParameter();
			string patP2 = pattern.getSecondParameter();
			string check = "s,stmt";
			Assert::AreEqual(select, check);
			check = "Parentss";
			Assert::AreEqual(cType,check);
			check = "2";
			Assert::AreEqual(cP1, check);
			check = "s";
			Assert::AreEqual(cP2, check);
			check = "a";
			Assert::AreEqual(patT, check);
			check = "\"x\"";
			Assert::AreEqual(patP1, check);
			check = "_";

			return;
		}
	};
}

