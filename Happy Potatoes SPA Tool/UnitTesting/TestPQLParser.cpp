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

		}

	}
}

