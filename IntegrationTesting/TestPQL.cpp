#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\source\PKB\Header\Parser.h"
#include "..\source\PKB\Header\ProcTable.h"
#include "..\source\PKB\Header\stmtTable.h"
#include "..\source\PKB\Header\VarTable.h"
#include "..\source\PKB\Header\CFG.h"
#include "..\source\PQL\Header\ParseResult.h"
#include "..\source\PQL\Header\QueryEvaluator.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestQE1) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 1 */
			string declaration = "procedure p,p1,p2,p3,p4; while w1,w2,w3,w4; assign a,a1,a2,a3,a4; stmt s,s#,s1,s2,s3,s4; variable v1,v2,v3,v4; prog_line n1,n2,n3,n4; constant c1,c2,c3,c4; if i1,i2,i3,i4; stmtLst stmtLst1,stmtLst2;";
			string query = "Select s such that Follows(1, s)";
			result.push_back("2");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}


		TEST_METHOD(TestQE2) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 2 */
			string declaration = "while w1;";
			string query = "Select w1 such that Uses(w1,\"x\") and Modifies(w1,\"x\")";
			result.push_back("1");
			result.push_back("2");
			result.push_back("10");
			result.push_back("12");
			result.push_back("13");
			result.push_back("14");
			result.push_back("15");
			result.push_back("16");
			
			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}


		TEST_METHOD(TestQE3) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 3 */
			string declaration = "while w1;";
			string query = "Select w1 such that Uses(w1,\"x\") and Modifies(w1,\"x\") and Uses(w1,\"i\") and Modifies(w1,\"i\")";
			result.push_back("1");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE4) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 4 */
			string declaration = "assign a1;";
			string query = "Select a1 such that Modifies(a1,\"y\") and Uses(a1,\"x\") pattern a1(_,_\"z\"_)";
			result.push_back("18");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE5) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 5 */
			string declaration = "prog_line n1; assign a1;";
			string query = "Select n1 such that Parent(32,33) and Uses(23,\"varA\") and Modifies(28,\"varD\") pattern a1(_,_\"varA\"_)";
			for (int i = 1; i <= 57; i++) {
				string toBePushed = std::to_string(i);
				result.push_back(toBePushed);
			}
			
			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE6) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 6 */
			string declaration = "while w1;";
			string query = "Select w1 such that Parent*(w1,43) and Modifies(w1,\"varLoop10\")";
			for (int i = 32; i <= 42; i++) {
				if (i == 37) continue;
				string toBePushed = std::to_string(i);
				result.push_back(toBePushed);
			}

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE7) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 7 */
			string declaration = "while w1; assign a1,a2;";
			string query = "Select w1 such that Parent*(w1,43) and Modifies(w1,\"varLoop10\") and Follows*(w1,35) pattern a2(_,_\"varLoop1\"_) pattern a1(_,_)";
			result.push_back("none");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE8) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 8 */
			string declaration = "constant c1; while w1; assign a1,a2;";
			string query = "Select c1 such that Parent*(w1,43) pattern a1(_,_) such that Modifies(w1,\"varLoop10\") and Follows*(w1,57) pattern a2(_,_\"varLoop1\"_)";
			for (int i=0; i <= 10; i++) {
				if (i == 3) continue;
				string toBePushed = std::to_string(i);
				result.push_back(toBePushed);
			}
			result.push_back("12345");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE9) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 9 */
			string declaration = "while w1; variable v1;";
			string query = "Select v1 such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1)";
			result.push_back("varLoop5");
			result.push_back("varLoop10");
			result.push_back("varLoop9");
			result.push_back("varLoop8");
			result.push_back("varLoop7");
			result.push_back("varLoop6");
			result.push_back("varLoop4");
			result.push_back("varLoop2");
			result.push_back("varLoop1");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE10) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 10 */
			string declaration = "variable v1; while w1; assign a1,a2;";
			string query = "Select v1 such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_)";
			result.push_back("varLoop5");
			result.push_back("varLoop10");
			result.push_back("varLoop9");
			result.push_back("varLoop8");
			result.push_back("varLoop7");
			result.push_back("varLoop6");
			result.push_back("varLoop4");
			result.push_back("varLoop2");
			result.push_back("varLoop1");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE11) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 11 */
			string declaration = "stmt s1,s2; assign a1,a2,a3;";
			string query = "Select s1 such that Parent*(s1,37) and Modifies(s1,\"varLastLoop\") pattern a1(\"varLastLoop\",_\"varLoop5\"_) such that Follows*(s1,55) pattern a2(_,_\"varLoop8\"_) such that Uses(s1,\"loop3\") and Uses(s1,\"loop4\") pattern a3(_,_) such that Parent(s2,37)";
			result.push_back("34");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE12) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source02.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 12 */
			string declaration = "stmt s1,s2; assign a1,a2,a3; while w1;";
			string query = "Select w1 such that Parent*(s1,37) and Parent(s2,37) and Modifies(s1,\"varLastLoop\") and Follows*(s1,55) and Uses(s1,\"loop3\") and Uses(s1,\"loop4\") pattern a1(\"varLastLoop\",_\"varLoop5\"_) pattern a2(_,_\"varLoop8\"_) pattern a3(_,_) such that Parent*(w1,55)";
			result.push_back("32");
			result.push_back("33");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE13) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 13 */
			string declaration = "assign a1;";
			string query = "Select a1 pattern a1(_,_)";
			for (int i = 3; i <= 9; i++) {
				string toBePushed = std::to_string(i);
				result.push_back(toBePushed);
			}
			result.push_back("11");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE14) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 14 */
			string declaration = "prog_line n; stmt s;";
			string query = "Select s such that Next*(16, n) and Parent*(s, n)";
			result.push_back("13");
			result.push_back("14");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE15) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 15 */
			string declaration = "prog_line n; assign a;";
			string query = "Select a such that Affects*(a, n) and Next*(13, n)";
			result.push_back("17");
			result.push_back("18");
			result.push_back("19");
			result.push_back("20");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE16) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 16 */
			string declaration = "procedure p, q; variable v;";
			string query = "Select <p, q, v> such that Modifies(p, v) and Calls(p, q)";
			result.push_back("Example p i");
			result.push_back("Example p x");
			result.push_back("Example p y");
			result.push_back("Example p z");
			result.push_back("Example q i");
			result.push_back("Example q x");
			result.push_back("Example q y");
			result.push_back("Example q z");
			result.push_back("p q i");
			result.push_back("p q x");
			result.push_back("p q z");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE17) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 17 */
			string declaration = "assign a1, a2; variable v;";
			string query = "Select v pattern a1(v, _) such that Affects*(a1, a2) and Uses(a2, v)";
			result.push_back("i");
			result.push_back("x");
			result.push_back("z");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE18) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 18 */
			string declaration = "assign a1;";
			string query = "Select a1 pattern a1(_,_\"p\"_)";
			result.push_back("none");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE19) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 19 */
			string declaration = "assign a1,a2;";
			string query = "Select a1 pattern a2(_,_\"p\"_)";
			result.push_back("none");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE20) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 20 */
			string declaration = "assign a1,a2;";
			string query = "Select a1 pattern a2(_,_\"x\"_)";
			for (int i = 3; i <= 9; i++) {
				string toBePushed = std::to_string(i);
				result.push_back(toBePushed);
			}
			result.push_back("11");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE21) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 21 */
			string declaration = "stmt s1;";
			string query = "Select s1 such that Uses (s1, _)";
			for (int i = 1; i <= 11; i++) {
				if (i == 6 || i == 7) continue;
				string toBePushed = std::to_string(i);
				result.push_back(toBePushed);
			}

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE22) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 22 */
			string declaration = "while w1;";
			string query = "Select w1 such that Uses (w1, _)";
			result.push_back("1");
			result.push_back("2");
			result.push_back("10");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE23) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 23 */
			string declaration = "assign a1; variable v1;";
			string query = "Select a1 such that Uses (a1, v1)";
			for (int i = 3; i <= 9; i++) {
				if (i == 6 || i == 7) continue;
				string toBePushed = std::to_string(i);
				result.push_back(toBePushed);
			}
			result.push_back("11");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE24) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 24 */
			string declaration = "stmt s1; variable v1;";
			string query = "Select s1 such that Uses (s1, v1)";
			for (int i = 1; i <= 11; i++) {
				if (i == 6 || i == 7) continue;
				string toBePushed = std::to_string(i);
				result.push_back(toBePushed);
			}

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE25) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 25 */
			string declaration = "constant c1; while w1; variable v1;";
			string query = "Select c1 such that Uses (w1, v1)";
			result.push_back("0");
			result.push_back("1");
			result.push_back("2");
			result.push_back("5");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE26) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 26 */
			string declaration = "while w1; variable v1;";
			string query = "Select w1 such that Uses (1, v1)";
			result.push_back("1");
			result.push_back("2");
			result.push_back("10");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE27) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 27 */
			string declaration = "variable v1;";
			string query = "Select v1 such that Uses (1, v1)";
			result.push_back("i");
			result.push_back("j");
			result.push_back("x");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE28) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 28 */
			string declaration = "assign a1; while w1;";
			string query = "Select a1 pattern a1 (\"x\",_) such that Uses(w1, \"i\")";
			result.push_back("3");
			result.push_back("4");
			result.push_back("6");
			result.push_back("11");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE29) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 29 */
			string declaration = "assign a1;";
			string query = "Select a1 such that Modifies(a1,\"x\")";
			result.push_back("3");
			result.push_back("4");
			result.push_back("6");
			result.push_back("11");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE30) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 30 */
			string declaration = "variable v1; assign a1;";
			string query = "Select a1 such that Modifies(a1,v1) pattern a1(\"x\",_\"x\"_)";
			result.push_back("3");
			result.push_back("4");
			result.push_back("11");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE31) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 31 */
			string declaration = "stmt s1;";
			string query = "Select s1 such that Parent(10, s1)";
			result.push_back("11");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE32) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 32 */
			string declaration = "assign a1;";
			string query = "Select a1 such that Parent(_,3) pattern a1(_,_\"z\"_)";
			result.push_back("8");
			result.push_back("9");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE33) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 33 */
			string declaration = "stmt s1;";
			string query = "Select s1 such that Parent*(10, s1)";
			result.push_back("11");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE34) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 34 */
			string declaration = "assign a1;";
			string query = "Select a1 such that Parent*(_,3) pattern a1(_,_\"z\"_)";
			result.push_back("8");
			result.push_back("9");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE35) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 35 */
			string declaration = "stmt s1; assign a1;";
			string query = "Select a1 such that Follows(1, 6) pattern a1(\"y\", _)";
			result.push_back("9");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE36) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 36 */
			string declaration = "stmt s1;";
			string query = "Select s1 such that Follows(_, _)";
			for (int i = 1; i <= 11; i++) {
				string toBePushed = std::to_string(i);
				result.push_back(toBePushed);
			}


			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE37) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 37 */
			string declaration = "stmt s1; assign a1;";
			string query = "Select a1 such that Follows*(1, 10) pattern a1(\"y\", _)";
			result.push_back("9");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE38) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 38 */
			string declaration = "while w; variable v;";
			string query = "Select w such that Modifies(w, v) with v.varName = \"x\"";
			result.push_back("4");
			result.push_back("14");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE39) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 39 */
			string declaration = "procedure p, q;";
			string query = "Select BOOLEAN such that Calls(p, q) with q.procName = \"p\" and p.procName = \"Example\"";
			result.push_back("true");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}

		TEST_METHOD(TestQE40) {
			std::vector<string> result;

			try {
				Parser::parse("../tests01/Sample-Source03.txt");
			}
			catch (exception& e) {
				cout << "PKBParser: " << e.what() << endl;
			}

			/* Test 40 */
			string declaration = "if ifs; assign a1, a2; variable v1, v2;";
			string query = "Select ifs such that Follows*(a1, ifs) and Follows*(ifs, a2) and Modifies(ifs, v1) and Uses(ifs, v2) with v1.varName = v2.varName";
			result.push_back("6");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			Assert::AreEqual(results, result);
			result.clear();
		}
	};
}