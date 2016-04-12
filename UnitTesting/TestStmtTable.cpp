#include <iostream>
#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"
#include "../source/PKB/Header/stmtTable.h"
#include "../source/PKB/Header/Parent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestStmtTable)
	{
	public:
		TEST_METHOD(TestParent) {


			// test for getParent
			string result;
			bool isparent;
			bool expectBool;
			string expectedChildren;
			string resultChildren;
			std::vector<string> resultChild;
			string expected_result01 = "14";
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");
			vector<string> getParent = stmtTable::getParent(24);
			if (getParent.size() == 0) {
				result = "0";
			}
			else {
				result = getParent.front();
			}

			//			Parent pa;
			//			pa.PrintProcTable();

			Assert::AreEqual(expected_result01, result);

			expected_result01 = "0";
			getParent = stmtTable::getParent(26);
			if (getParent.size() == 0) {
				result = "0";
			}
			else {
				result = getParent.front();
			}


			Assert::AreEqual(expected_result01, result);

			expected_result01 = "28";
			getParent = stmtTable::getParent(30);

			if (getParent.size() == 0) {
				result = "0";
			}
			else {
				result = getParent.front();
			}

			Assert::AreEqual(expected_result01, result);


			string expected_star = "9754";
			getParent = stmtTable::getParentStar(11);
			string actualResult;

			for (std::vector<string>::iterator it = getParent.begin(); it != getParent.end(); ++it) {
				actualResult.append(*it);
			}

			Assert::AreEqual(expected_star, actualResult);


			// test get Child star
			expected_star = "5678910111213141516171819202122232425";
			getParent = stmtTable::getChildStar(4);
			actualResult.clear();

			for (std::vector<string>::iterator it = getParent.begin(); it != getParent.end(); ++it) {
				actualResult.append(*it);
			}

			Assert::AreEqual(expected_star, actualResult);

/*			
			//test for getParent  for while  and assign

			expected_result01 = 0;
			getParent = stmtTable::getParentForWhile(5);
			if (getParent.size() == 0) {
				result = 0;
			}
			else {
                result = getParent.front();
			}
			

			Assert::AreEqual(expected_result01, result);

			expected_result01 = 0;
			getParent = stmtTable::getParentForAssign(5);

			if (getParent.size() == 0) {
				result = 0;
			}
			else {
				result = getParent.front();
			}

			Assert::AreEqual(expected_result01, result);



			//test for isParent

			expectBool = true;
			isparent = stmtTable::isParent(4, 5);

			Assert::AreEqual(expectBool, isparent);

			expectBool = false;
			isparent = stmtTable::isParent(3, 4);

			Assert::AreEqual(expectBool, isparent);
	*/		
			//test for getChild
			expectedChildren = "51225";
			resultChild = stmtTable::getChild(4);
			resultChildren.clear();
		//	resultChildren = std::to_string(resultChild.size());

			for (std::vector<string>::iterator it = resultChild.begin(); it != resultChild.end(); ++it) {
				resultChildren.append(*it);
				//result.append(", ");
			}

			Assert::AreEqual(expectedChildren, resultChildren);
			
	   // test for get child for while and assign
	       
			expectedChildren = "681011";
			resultChild = stmtTable::getChildStarForAssign(5);
			resultChildren.clear();
			for (std::vector<string>::iterator it = resultChild.begin(); it != resultChild.end(); ++it) {
				resultChildren.append(*it);
				//result.append(", ");
			}

			Assert::AreEqual(expectedChildren, resultChildren);
			
			expectedChildren = "7";
			resultChild = stmtTable::getChildForWhile(5);
			resultChildren.clear();
			for (std::vector<string>::iterator it = resultChild.begin(); it != resultChild.end(); ++it) {
				resultChildren.append(*it);
				//result.append(", ");
			}
			if (resultChildren.size() == 0) {
				resultChildren.append("0");
			}

			Assert::AreEqual(expectedChildren, resultChildren);
			
			//test isParentStar
			isparent = true;
			expectBool = stmtTable::isParentStar(4,10);
			Assert::AreEqual(expectBool, isparent);
		
		}

		TEST_METHOD(TestFollow)
		{
			
			string result;
			bool expectedIsFollow;
			bool resultIsFollow;
			int expectFollowFan;
			int resultFollowFan;
			std::vector<int>followFan;
			Parser::parse("..\\UnitTesting\\TestParser\\Sample-Source05.txt");

			// test for getFollow
			string expected_result01 = "16";
			vector<string> getFollow = stmtTable::getFollow(15);
			if (getFollow.size() == 0) {
				result = "0";
			}
			else {
                result = getFollow.front();
			}
			

			Assert::AreEqual(expected_result01, result);

			result = "0";
			getFollow.clear();
			expected_result01 = "0";
			getFollow = stmtTable::getFollow(4);

			if (getFollow.size() == 0) {
				result = "0";
			}
			else {
				result = getFollow.front();
			}

			Assert::AreEqual(expected_result01, result);
			// test follow fan
			result = "0";
			getFollow.clear();
			expected_result01 = "0";
			getFollow = stmtTable::getFollowFan(29);

			if (getFollow.size() == 0) {
				result = "0";
			}
			else {
				result = getFollow.front();
			}

			Assert::AreEqual(expected_result01, result);


			//test FollowFanStar
			result.clear();
			getFollow.clear();
			expected_result01 = "1718";
			getFollow = stmtTable::getFollowFanStar(19);

			if (getFollow.size() == 0) {
				result = "0";
			}
			else {
				for (int i = 0; i < getFollow.size(); i++) {
					result.append(getFollow.at(i));
				}
			}
			Assert::AreEqual(expected_result01, result);
			//test getFollowStar
			result.clear();
			getFollow.clear();
			expected_result01 = "3233";
			getFollow = stmtTable::getFollowStar(31);

			if (getFollow.size() == 0) {
				result = "0";
			}
			else {
				for (int i = 0; i < getFollow.size(); i++) {
					result.append(getFollow.at(i));
				}
			}
			Assert::AreEqual(expected_result01, result);

			// test follow fan
			result.clear();
			getFollow.clear();
			expected_result01 = "18";
			getFollow = stmtTable::getFollowFan(19);

			if (getFollow.size() == 0) {
				result = "0";
			}
			else {
				for (int i = 0; i < getFollow.size(); i++) {
					result.append(getFollow.at(i));
				}
			}

			Assert::AreEqual(expected_result01, result);

			//test for getFollowForWhile
			expected_result01 = "12";
			std::vector<string>getFollowForWhile;
			getFollowForWhile = stmtTable::getFollowForWhile(5);

			if (getFollowForWhile.size() == 0) {
				result = "0";
			}
			else {
				result = getFollowForWhile.front();
			}

			Assert::AreEqual(expected_result01, result);
			// test getFollowStar for while
			expected_result01 = "12";
			getFollowForWhile.clear();
			result.clear();
			getFollowForWhile = stmtTable::getFollowStarForWhile(5);

			if (getFollowForWhile.size() == 0) {
				result = "0";
			}
			else {
				for (std::vector<string>::iterator it = getFollowForWhile.begin(); it != getFollowForWhile.end(); ++it) {
					result.append(*it);
					//result.append(", ");
				}
			}

			Assert::AreEqual(expected_result01, result);
			
			
			//Test for getFollowFor assign
		string expected_result02;
			string resultString;
			expected_result02 = "18";
			getFollowForWhile.clear();
			getFollowForWhile = stmtTable::getFollowFanForAssign(19);

			for (std::vector<string>::iterator it = getFollowForWhile.begin(); it != getFollowForWhile.end(); ++it) {
				resultString.append(*it);
				//result.append(", ");
			}
			if (resultString.size() == 0) {
				resultString.append("0");
			}

			Assert::AreEqual(expected_result02, resultString); 
			
			expected_result01 = "14";
			getFollowForWhile.clear();
			result.clear();
			getFollowForWhile = stmtTable::getFollowStarForIf(13);

			if (getFollowForWhile.size() == 0) {
				result = "0";
			}
			else {
				for (int i = 0; i < getFollowForWhile.size(); i++) {
					result.append(getFollowForWhile.at(i));
				}
			}

			Assert::AreEqual(expected_result01, result);
			
		
			//test for isFollow
			expectedIsFollow = true;
			resultIsFollow = stmtTable::isFollow(3, 4);

			Assert::AreEqual(expectedIsFollow, resultIsFollow);


			expectedIsFollow = true;
			resultIsFollow = stmtTable::isFollowStar(17, 19);

			Assert::AreEqual(expectedIsFollow, resultIsFollow);
			
		}  
	}; 
}