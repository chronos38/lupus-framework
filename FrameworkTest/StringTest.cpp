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
			String string;

			// default constructor
			Assert::AreEqual(0, string.Length(), L"default constructor", LINE_INFO());
			Assert::AreEqual(0, string[0].Value(), L"default constructor", LINE_INFO());

			// (const char*)
			try {
				string = String((char*)0);
				string = String((wchar_t*)0);
				string = String((Char*)0);
			} catch (ArgumentNullException& e) {
				// do nothing
			}
			string = String("abc");
			Assert::AreEqual(3, string.Length(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual((int)'a', string[0].Value(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual((int)'b', string[1].Value(), L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual((int)'c', string[2].Value(), L"(const char*) constructor", LINE_INFO());
		}
	};
}