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
			int result;
			bool isparent;
			bool expectBool;
			string expectedChildren;
			string resultChildren;
			std::vector<int> resultChild;
			int expected_result01 = 14;
			Parser::parse("C:\\Users\\feifei\\Source\\Repos\\CS3201-HappyPotatoes\\UnitTesting\\TestParser\\Sample-Source05.txt");
        	vector<int> getParent = stmtTable::getParent(24);
			result = getParent.front();
			Parent pa;
			pa.PrintProcTable();

			Assert::AreEqual(expected_result01, result);

			expected_result01 = 4;
			getParent = stmtTable::getParent(25);
			if (getParent.size() == 0) {
				result = 0;
			}
			else {
                result = getParent.front();
			}
			

			Assert::AreEqual(expected_result01, result);

			expected_result01 = 28;
			getParent = stmtTable::getParent(30);

			if (getParent.size() == 0) {
				result = 0;
			}
			else {
				result = getParent.front();
			}

			Assert::AreEqual(expected_result01, result);
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
			
			//test for getChild
			expectedChildren = "56";
			resultChild = stmtTable::getChild(4);
		//	resultChildren = std::to_string(resultChild.size());

			for (std::vector<int>::iterator it = resultChild.begin(); it != resultChild.end(); ++it) {
				resultChildren.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expectedChildren, resultChildren);
			
	   // test for get child for while and assign
	       
			expectedChildren = "56";
			resultChild = stmtTable::getChildForAssign(4);
			resultChildren.clear();
			for (std::vector<int>::iterator it = resultChild.begin(); it != resultChild.end(); ++it) {
				resultChildren.append(std::to_string(*it));
				//result.append(", ");
			}

			Assert::AreEqual(expectedChildren, resultChildren);
			
			expectedChildren = "0";
			resultChild = stmtTable::getChildForWhile(5);
			resultChildren.clear();
			for (std::vector<int>::iterator it = resultChild.begin(); it != resultChild.end(); ++it) {
				resultChildren.append(std::to_string(*it));
				//result.append(", ");
			}
			if (resultChildren.size() == 0) {
				resultChildren.append("0");
			}

			Assert::AreEqual(expectedChildren, resultChildren);
		*/	
		}

		TEST_METHOD(TestFollow)
		{
			
			int result;
			bool expectedIsFollow;
			bool resultIsFollow;
			int expectFollowFan;
			int resultFollowFan;
			std::vector<int>followFan;
			Parser::parse("C:\\Users\\feifei\\Source\\Repos\\CS3201-HappyPotatoes\\UnitTesting\\TestParser\\Sample-Source02.txt");

			// test for getFollow
			int expected_result01 = 0;
			vector<int> getFollow = stmtTable::getFollow(4);
			if (getFollow.size() == 0) {
				result = 0;
			}
			else {
                result = getFollow.front();
			}
			

			Assert::AreEqual(expected_result01, result);

			result = 0;
			getFollow.clear();
			expected_result01 = 0;
			getFollow = stmtTable::getFollow(5);

			if (getFollow.size() == 0) {
				result = 0;
			}
			else {
				result = getFollow.front();
			}

			Assert::AreEqual(expected_result01, result);

			//test for getFollowForWhile
			expected_result01 = 0;
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
			string expected_result02;
			string resultString;
			expected_result02 = "2";
			getFollowForWhile.clear();
			getFollowForWhile = stmtTable::getFollowFanForAssign(3);

			for (std::vector<int>::iterator it = getFollowForWhile.begin(); it != getFollowForWhile.end(); ++it) {
				resultString.append(std::to_string(*it));
				//result.append(", ");
			}
			if (resultString.size() == 0) {
				resultString.append("0");
			}

			Assert::AreEqual(expected_result02, resultString); 
			
			expected_result01 = 0;
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
			expectedIsFollow = true;
			resultIsFollow = stmtTable::isFollow(3, 4);

			Assert::AreEqual(expectedIsFollow, resultIsFollow);
			
			//test for follow start
			expectFollowFan = 0;
			followFan = stmtTable::getFollowFan(1);

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