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
#include "..\Framework\String.hpp"
#include "..\Framework\Exception.hpp"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Lupus;
using namespace Lupus::System;

namespace FrameworkTest
{
	TEST_CLASS(StringTest)
	{
	public:
		TEST_METHOD(StringConstructorTest)
		{
			// variables
			Char ch[] = { L'a', L'b', L'c', L'd', L'e', L'f', L'\0' };
			String string;

			// default constructor
			Assert::AreEqual(0, string.Length(), L"default constructor", LINE_INFO());

			// (const char*) constructor
			string = String("abc");
			Assert::AreEqual(3, string.Length(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual(L'a', string[0].Value(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual(L'b', string[1].Value(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual(L'c', string[2].Value(), L"(const char*) constructor", LINE_INFO());

			// (const wchar_t*) constructor
			string = String(L"abc");
			Assert::AreEqual(3, string.Length(), L"(const wchar_t*) constructor", LINE_INFO());
			Assert::AreEqual(L'a', string[0].Value(), L"(const wchar_t*) constructor", LINE_INFO());
			Assert::AreEqual(L'b', string[1].Value(), L"(const wchar_t*) constructor", LINE_INFO());
			Assert::AreEqual(L'c', string[2].Value(), L"(const wchar_t*) constructor", LINE_INFO());

			// (const Char*) constructor
			string = String(ch);
			Assert::AreEqual(6, string.Length(), L"(const wchar_t*) constructor", LINE_INFO());
			Assert::AreEqual(L'a', string[0].Value(), L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual(L'b', string[1].Value(), L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual(L'c', string[2].Value(), L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual(L'd', string[3].Value(), L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual(L'e', string[4].Value(), L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual(L'f', string[5].Value(), L"(const Char*) constructor", LINE_INFO());

			// (char*,int,int) constructor
			string = String("abcdef", 2, 2);
			Assert::AreEqual(2, string.Length(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual(L'c', string[0].Value(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual(L'd', string[1].Value(), L"(const char*) constructor", LINE_INFO());

			// (wchar_t*,int,int) constructor
			string = String(L"abcdef", 2, 2);
			Assert::AreEqual(2, string.Length(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual(L'c', string[0].Value(), L"(const wchar_t*) constructor", LINE_INFO());
			Assert::AreEqual(L'd', string[1].Value(), L"(const wchar_t*) constructor", LINE_INFO());

			// (Char*,int,int) constructor
			string = String(ch, 2, 2);
			Assert::AreEqual(2, string.Length(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual(L'c', string[0].Value(), L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual(L'd', string[1].Value(), L"(const Char*) constructor", LINE_INFO());
		}
	};
}