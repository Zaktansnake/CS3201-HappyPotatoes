#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

#include "./PKB/Header/Parser.h"
#include "./PKB/Header/PKB.h"
#include "./PKB/Header/stmtTable.h"

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
			Parser::parse("..\\Release\Sample-Source.txt");

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


			//test for isParent

			expectBool = true;
			isparent = stmtTable::isParent(2, 9);

			Assert::AreEqual(expectBool, isparent);

			expectBool = false;
			isparent = stmtTable::isParent(1, 2);

			Assert::AreEqual(expectBool, isparent);

			//test for getChild

			expectedChildren = "34689";
			resultChild = stmtTable::getChild(2);
		//	resultChildren = std::to_string(resultChild.size());
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

			Parser::parse("C:\\Users\\feifei\\Downloads\\TestFollow.txt");

			// test for getFollow

			int expected_result01 = 2;
			vector<int> getFollow = stmtTable::getFollow(1);
			result = getFollow.front();

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