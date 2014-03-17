/* Copyright © 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of LupusFramwork.
 *
 * LupusFramwork is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LupusFramwork is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LupusFramwork.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Framework\Char.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Lupus::System;

namespace FrameworkTest
{
	TEST_CLASS(CharTest)
	{
	public:
		TEST_METHOD(CharConstructorTest)
		{
			// default constructor
			Assert::AreEqual('\0', (char)Char().Value, L"default constructor", LINE_INFO());

			// (char) constructor
			Assert::AreEqual('a', (char)Char('a').Value, L"(int) constructor with wchar_t eqhals wchar_t", LINE_INFO());

			// (wchar_t) constructor
			Assert::AreEqual('a', (char)Char('a').Value, L"(int) constructor with wchar_t eqhals wchar_t", LINE_INFO());

			// (Char) constructor
			Assert::AreEqual('a', (char)Char(Char('a')).Value, L"(int) constructor with wchar_t", LINE_INFO());
		}

		TEST_METHOD(CharEqualityTest)
		{
			// variables
			Char ch('a');

			// operator==
			Assert::IsTrue(ch == 'a', L"operator== equals with char", LINE_INFO());
			Assert::IsTrue(ch == 'a', L"operator== equals with wchar_t", LINE_INFO());
			Assert::IsTrue(ch == (int)'a', L"operator== equals with int", LINE_INFO());
			Assert::IsTrue('a' == ch, L"operator== equals with char", LINE_INFO());
			Assert::IsTrue('a' == ch, L"operator== equals with wchar_t", LINE_INFO());
			Assert::IsTrue((int)'a' == ch, L"operator== equals with int", LINE_INFO());

			// operator!=
			Assert::IsTrue(ch != 'b', L"operator!= equals with char", LINE_INFO());
			Assert::IsTrue(ch != 'b', L"operator!= equals with wchar_t", LINE_INFO());
			Assert::IsTrue(ch != (int)'b', L"operator!= equals with int", LINE_INFO());
			Assert::IsTrue('b' != ch, L"operator!= equals with char", LINE_INFO());
			Assert::IsTrue('b' != ch, L"operator!= equals with wchar_t", LINE_INFO());
			Assert::IsTrue((int)'b' != ch, L"operator!= equals with int", LINE_INFO());
		}

		TEST_METHOD(CharArithmeticTest)
		{
			// variables
			Char ch('a');

			// operator+
			Assert::AreEqual('a' + 1, ch.Value + 1, L"operator+", LINE_INFO());
			Assert::AreEqual(1 + 'a', 1 + ch.Value, L"operator+", LINE_INFO());

			// operator-
			Assert::AreEqual('a' - 1, ch.Value - 1, L"operator-", LINE_INFO());
			Assert::AreEqual(1 - 'a', 1 - ch.Value, L"operator-", LINE_INFO());

			// operator+=
			Assert::AreEqual('b', (char)(ch += 1).Value, L"operator+=", LINE_INFO());

			// operator-=
			Assert::AreEqual('a', (char)(ch -= 1).Value, L"operator-=", LINE_INFO());
		}

		TEST_METHOD(CharPropertyTest)
		{
			// variables
			Char ch('a');

			// tests
			Assert::IsFalse(ch.IsBlank(), L"IsBlank", LINE_INFO());
			Assert::IsFalse(ch.IsDigit(), L"IsDigit", LINE_INFO());
			Assert::IsTrue(ch.IsGraph(), L"IsGraph", LINE_INFO());
			Assert::IsTrue(ch.IsLetter(), L"IsLetter", LINE_INFO());
			Assert::IsTrue(ch.IsLetterOrDigit(), L"IsLetterOrDigit", LINE_INFO());
			Assert::IsTrue(ch.IsLower(), L"IsLower", LINE_INFO());
			Assert::IsFalse(ch.IsPunct(), L"IsPunct", LINE_INFO());
			Assert::IsFalse(ch.IsUpper(), L"IsUpper", LINE_INFO());
			Assert::IsFalse(ch.IsSpace(), L"IsSpace", LINE_INFO());
			Assert::IsTrue(ch.IsPrint(), L"IsPrint", LINE_INFO());
			Assert::IsFalse(ch.IsControl(), L"IsControl", LINE_INFO());
			Assert::IsTrue(ch.IsHexadecimal(), L"IsHexadecimal", LINE_INFO());
		}

		TEST_METHOD(CharMethodTest)
		{
			// variables
			Char ch1('a');
			Char ch2('A');

			// tests
			Assert::AreEqual('A', (char)(ch1.ToUpper()).Value, L"ToUpper", LINE_INFO());
			Assert::AreEqual('a', (char)(ch2.ToLower()).Value, L"ToLower", LINE_INFO());
		}
	};
}