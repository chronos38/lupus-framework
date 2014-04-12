/* Copyright © 2014 David Wolf <d.wolf@live.at>
*
* This file is part of LupusFramwork.
*
* LupusFramwork is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* LupusFramwork is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with LupusFramwork.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Framework\String.hpp"
#include "..\Framework\Float.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Lupus;
using namespace Lupus::System;

namespace FrameworkTest {
	TEST_CLASS(IntegerTest)
	{
		TEST_METHOD(FloatToStringTest)
		{
			// variables
			float f = 1.234f;
			double d = 1.23456789;
			real r = 1.23456789101112;

			// to string
			Assert::IsTrue(String("1.234000").Compare(Float::ToString(f)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("1.234568").Compare(Float::ToString(d)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("1.234568").Compare(Float::ToString(r)) == 0, L"ToString", LINE_INFO());
		}

		TEST_METHOD(FloatTryParseTest)
		{
			// variables
			String string("1.23456789101112");
			float f;
			double d;
			real r;

			// test
			Assert::IsTrue(Float::TryParse(string, f), L"TryParse", LINE_INFO());
			Assert::IsTrue(Float::TryParse(string, d), L"TryParse", LINE_INFO());
			Assert::IsTrue(Float::TryParse(string, r), L"TryParse", LINE_INFO());
		}
	};
}
