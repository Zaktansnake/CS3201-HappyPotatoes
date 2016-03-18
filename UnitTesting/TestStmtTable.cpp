#include <iostream>
#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/Header/Parser.h"
#include "../source/PKB/Header/PKB.h"
#include "../source/PKB/Header/stmtTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestStmtTable)
	{
	public:
		TEST_METHOD(TestParent) {
		    
			
			// test for getParent
			int result;
			bool isparent;
			bool expectBool;
			string expectedChildren;
			string resultChildren;
			std::vector<int> resultChild;
			int expected_result01 = 4;
			Parser::parse("C:\\Users\\feifei\\Source\\Repos\\CS3201-HappyPotatoes\\UnitTesting\\TestParser\\Sample-Source02");
			vector<int> getParent = stmtTable::getParent(5);
			result = getParent.front();

			Assert::AreEqual(expected_result01, result);

			expected_result01 = 6;
			getParent = stmtTable::getParent(7);
			result = getParent.front();

			Assert::AreEqual(expected_result01, result);

			expected_result01 = 0;
			getParent = stmtTable::getParent(1);

			if (getParent.size() == 0) {
				result = 0;
			}

			Assert::AreEqual(expected_result01, result);
			//test for getParent  for while  and assign

			expected_result01 = 2;
			getParent = stmtTable::getParentForWhile(8);
			result = getParent.front();

			Assert::AreEqual(expected_result01, result);

			expected_result01 = 0;
			getParent = stmtTable::getParentForAssign(4);

			if (getParent.size() == 0) {
				result = 0;
			}

			Assert::AreEqual(expected_result01, result);



			//test for isParent

			expectBool = true;
			isparent = stmtTable::isParent(2, 9);

			Assert::AreEqual(expectBool, isparent);

			expectBool = false;
			isparent = stmtTable::isParent(1, 2);

			Assert::AreEqual(expectBool, isparent);

			//test for getChild
			expectedChildren = "3489";
			resultChild = stmtTable::getChild(2);
		//	resultChildren = std::to_string(resultChild.size());

			for (std::vector<int>::iterator it = resultChild.begin(); it != resultChild.end(); ++it) {
				resultChildren.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expectedChildren, resultChildren);

	   // test for get child for while and assign
	       
			expectedChildren = "389";
			resultChild = stmtTable::getChildForAssign(2);
			resultChildren.clear();
			for (std::vector<int>::iterator it = resultChild.begin(); it != resultChild.end(); ++it) {
				resultChildren.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expectedChildren, resultChildren);

			expectedChildren = "4";
			resultChild = stmtTable::getChildForWhile(2);
			resultChildren.clear();
			for (std::vector<int>::iterator it = resultChild.begin(); it != resultChild.end(); ++it) {
				resultChildren.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expectedChildren, resultChildren);
			
		}

		TEST_METHOD(TestFollow)
		{
			
			int result;
			bool expectedIsFollow;
			bool resultIsFollow;
			int expectFollowFan;
			int resultFollowFan;
			std::vector<int>followFan;
			Parser::parse("C:\\Users\\feifei\\Source\\Repos\\CS3201-HappyPotatoes\\UnitTesting\\Sample-Source 01.txt");

			// test for getFollow
			int expected_result01 = 0;
			vector<int> getFollow = stmtTable::getFollow(10);
			if (getFollow.size() == 0) {
				result = 0;
			}
			else {
                result = getFollow.front();
			}
			

			Assert::AreEqual(expected_result01, result);

			result = 0;
			getFollow.clear();
			expected_result01 = 8;
			getFollow = stmtTable::getFollow(4);

			if (getFollow.size() == 0) {
				result = 0;
			}
			else {
				result = getFollow.front();
			}

			Assert::AreEqual(expected_result01, result);

			//test for getFollowForWhile
			expected_result01 = 4;
			std::vector<int>getFollowForWhile;
			getFollowForWhile = stmtTable::getFollowForWhile(3);

			if (getFollowForWhile.size() == 0) {
				result = 0;
			}
			else {
				result = getFollowForWhile.front();
			}

			Assert::AreEqual(expected_result01, result);

			expected_result01 = 0;
			getFollowForWhile.clear();
			getFollowForWhile = stmtTable::getFollowForWhile(4);

			if (getFollowForWhile.size() == 0) {
				result = 0;
			}
			else {
				result = getFollowForWhile.front();
			}

			Assert::AreEqual(expected_result01, result);
			

			//Test for getFollowFor assign
			expected_result01 = 0;
			getFollowForWhile.clear();
			getFollowForWhile = stmtTable::getFollowFanForAssign(8);

			if (getFollowForWhile.size() == 0) {
				result = 0;
			}
			else {
				result = getFollowForWhile.front();
			}

			Assert::AreEqual(expected_result01, result);
			
			expected_result01 = 8;
			getFollowForWhile.clear();
			getFollowForWhile = stmtTable::getFollowForAssign(4);

			if (getFollowForWhile.size() == 0) {
				result = 0;
			}
			else {
				result = getFollowForWhile.front();
			}

			Assert::AreEqual(expected_result01, result);

		
			//test for isFollow
			expectedIsFollow = false;
			resultIsFollow = stmtTable::isFollow(4, 7);

			Assert::AreEqual(expectedIsFollow, resultIsFollow);

			//test for follow start
			expectFollowFan = 0;
			followFan = stmtTable::getFollowFan(3);

			if (followFan.size() == 0) {
				resultFollowFan = 0;
			}
			else {
				resultFollowFan = followFan.front();
			}

			Assert::AreEqual(expectFollowFan, resultFollowFan);

		}  
	}; 
}