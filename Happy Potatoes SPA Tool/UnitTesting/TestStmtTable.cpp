#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/stmtTable.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/Follows.h"
#include "../Happy Potatoes SPA Tool/PKB/Header/Parent.h"
#include <iostream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// initial
void setUp() {
    stmtTable::addStmtTable("i=1", 1);

}

namespace UnitTesting
{
	TEST_CLASS(stmtTable)
	{
	public:
		TEST_METHOD(testFollow) {
			cout << "Test Stmt Follow : ";
			

		}
		TEST_METHOD(testParent) {
			cout << "TestStmtTable::testStmt = ";

		}
	};
}