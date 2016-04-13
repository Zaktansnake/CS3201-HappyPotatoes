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
	
		TEST_METHOD(TestQE2) {
			string result;

			Parser::parse("../tests01/Sample-Source01.txt");
	
			/* Test 2 */
			string declaration = "while w1;";
			string query = "Select w1 such that Uses(w1,\"x\") and Modifies(w1,\"x\")";
			result = "57920";
			
			string expectedResult;
			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);
			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE4) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");

			/* Test 4 */
			string declaration = "assign a1;";
			string query = "Select a1 such that Modifies(a1,\"y\") and Uses(a1,\"x\") pattern a1(_,_\"z\"_)";
			expectedResult = "";

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);
			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE10) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");

			/* Test 10 */
			string declaration = "variable v1; while w1; assign a1,a2;";
			string query = "Select v1 such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_) such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_)";
			result.append("");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);
			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append("");
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE11) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");

			/* Test 11 */
			string declaration = "stmt s1,s2; assign a1,a2,a3;";
			string query = "Select s1 such that Parent*(s1,37) and Modifies(s1,\"varLastLoop\") pattern a1(\"varLastLoop\",_\"varLoop5\"_) such that Follows*(s1,55) pattern a2(_,_\"varLoop8\"_) such that Uses(s1,\"loop3\") and Uses(s1,\"loop4\") pattern a3(_,_) such that Parent(s2,37)";
			result.append("");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);
			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append("");
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE12) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");

			/* Test 12 */
			string declaration = "stmt s1,s2; assign a1,a2,a3; while w1;";
			string query = "Select w1 such that Parent*(s1,37) and Parent(s2,37) and Modifies(s1,\"varLastLoop\") and Follows*(s1,55) and Uses(s1,\"loop3\") and Uses(s1,\"loop4\") pattern a1(\"varLastLoop\",_\"varLoop5\"_) pattern a2(_,_\"varLoop8\"_) pattern a3(_,_) such that Parent*(w1,55)";
			result.append("");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);
			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append("");
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE13) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");

			/* Test 13 */
			string declaration = "assign a1;";
			string query = "Select a1 pattern a1(_,_)";
			result.append("");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);
			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append("");
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE14) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");
			

			/* Test 14 */
			string declaration = "prog_line n; stmt s;";
			string query = "Select s such that Next*(16, n) and Parent*(s, n)";
			result.append("");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);
			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append("");
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE17) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");
			
			/* Test 17 */
			string declaration = "assign a1, a2; variable v;";
			string query = "Select v pattern a1(v, _) such that Affects*(a1, a2) and Uses(a2, v)";
			result.append("");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);
			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE18) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");
	
			/* Test 18 */
			string declaration = "assign a1;";
			string query = "Select a1 pattern a1(_,_\"p\"_)";
			result.append("");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append("");
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE19) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");
			
			/* Test 19 */
			string declaration = "assign a1,a2;";
			string query = "Select a1 pattern a2(_,_\"p\"_)";
			result.append("");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append("");
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE21) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");

			/* Test 21 */
			string declaration = "stmt s1;";
			string query = "Select s1 such that Uses (s1, _)";
			result.append("457812131416391018192011617");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE22) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");

			/* Test 22 */
			string declaration = "while w1;";
			string query = "Select w1 such that Uses (w1, _)";
			result.append("20597");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE23) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");

			/* Test 23 */
			string declaration = "assign a1; variable v1;";
			string query = "Select a1 such that Uses (a1, v1)";
			result.append("3681011141617");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE24) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");

			/* Test 24 */
			string declaration = "stmt s1; variable v1;";
			string query = "Select s1 such that Uses (s1, v1)";
			result.append("345678910111213141617181920");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE25) {
			string result, expectedResult;
			
			Parser::parse("../tests01/Sample-Source01.txt");
		
			/* Test 25 */
			string declaration = "constant c1; while w1; variable v1;";
			string query = "Select c1 such that Uses (w1, v1)";
			result.append("01200");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE26) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");
			
			/* Test 26 */
			string declaration = "while w1; variable v1;";
			string query = "Select w1 such that Uses (1, v1)";
			result.append("57920");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);

			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}

		TEST_METHOD(TestQE27) {
			string result, expectedResult;

			Parser::parse("../tests01/Sample-Source01.txt");
			
			/* Test 27 */
			string declaration = "variable v1;";
			string query = "Select v1 such that Uses (1, v1)";
			result.append("IRomeoabbetacchArLiechArliedeltaij1kklleftoSCarrighttmpwidthxx1");

			ParseResult generatedParseResult = ParseResult::generateParseResult(declaration, query);
			QueryEvaluator evaluator;
			std::vector<std::string> results = evaluator.startEvaluator(generatedParseResult);
			for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it) {
				expectedResult.append(*it);
			}

			Assert::AreEqual(expectedResult, result);
			result.clear();
		}
	};
}