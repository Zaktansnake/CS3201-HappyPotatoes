#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PQL/Header/ParseResult.h"
#include "../source/PQL/Header/QueryEvaluator.h"
#include "../source/PQL/Header/QueriesAnswerStorage.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryEvaluator)
	{
	public:
		TEST_METHOD(TestQE) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 1 */
			string declaration = "procedure p,p1,p2,p3,p4; while w1,w2,w3,w4; assign a,a1,a2,a3,a4; stmt s,s#,s1,s2,s3,s4; variable v1,v2,v3,v4; prog_line n1,n2,n3,n4; constant c1,c2,c3,c4; call ca1,ca2,ca3,ca4; if i1,i2,i3,i4; stmtLst stmtLst1,stmtLst2; plus add; times times; minus minus;";
			string query = "Select s such that Follows(1, s)";
			result.push_back("2");

			ParseResult parser = ParseResult();
			ParseResult generatedParseResult = parser.generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			//Assert::AreEqual(results, result);
			result.clear();
		}
	};
}