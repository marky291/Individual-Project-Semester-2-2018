#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(UnitTest1)
	{
		public:
		
			TEST_METHOD(TestMethod1)
			{
				Assert::AreEqual(true, true);
			}

	};
}