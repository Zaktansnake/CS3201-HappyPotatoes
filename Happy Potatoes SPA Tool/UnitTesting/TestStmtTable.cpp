#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>

#include "../Happy Potatoes SPA Tool/PKB/Header/Parser.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/PKB.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/stmtTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestStmtTable)
	{
	public:
		TEST_METHOD(TEST_PARENT) {
		    
			// test for getParent
			int result;
			bool isparent;
			bool expectBool;
			string expectedChildren;
			string resultChildren;
			std::vector<int> resultChild;
			int expected_result01 = 0;
			Parser::parse("C:\\Users\\feifei\\Downloads\\TestFollow.txt");

			vector<int> getParent = stmtTable::getParent(1);
			result = getParent.front();

			Assert::AreEqual(expected_result01, result);


			expected_result01 = 2;
			getParent = stmtTable::getParent(8);
			result = getParent.front();

			Assert::AreEqual(expected_result01, result);

			//test for isParent

			expectBool = true;
			isparent = stmtTable::isParent(2, 8);

			Assert::AreEqual(expectBool, isparent);

			expectBool = false;
			isparent = stmtTable::isParent(1, 2);

			Assert::AreEqual(expectBool, isparent);

			//test for getChild

			expectedChildren = "3489";
			resultChild = stmtTable::getChild(2);

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
			string expectFollowStar;
			string resultFollowSatr;
			std::vector<int>followSatr;

			Parser::parse("C:\\Users\\feifei\\Downloads\\TestFollow.txt");

			// test for getFollow

			int expected_result01 = 2;
			vector<int> getFollow = stmtTable::getFollow(1);
			result = getFollow.front();

			Assert::AreEqual(expected_result01, result);

			result = 0;
			getFollow.clear();
			expected_result01 = 8;
			getFollow = stmtTable::getFollow(4);
			result = getFollow.front();

			Assert::AreEqual(expected_result01, result); 

			//test for isFollow

			expectedIsFollow = false;
			resultIsFollow = stmtTable::isFollow(4, 7);

			Assert::AreEqual(expectedIsFollow, resultIsFollow);


	/*		
			//test for follow start
			expectFollowStar = "489";
			followSatr = stmtTable::getFollowStar(3);

			for (std::vector<int>::iterator it = followSatr.begin(); it != followSatr.end(); ++it) {
				resultFollowSatr.append(std::to_string(*it));
				//result.append(", ");
			}
			Assert::AreEqual(expectFollowStar, resultFollowSatr);
*/
		} 
	}; 
}