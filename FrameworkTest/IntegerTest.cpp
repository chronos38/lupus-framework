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
#include "..\Framework\String.hpp"
#include "..\Framework\Integer.hpp"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Lupus;
using namespace Lupus::System;

namespace FrameworkTest {
	TEST_CLASS(IntegerTest)
	{
		TEST_METHOD(IntegerToStringTest)
		{
			// variables
			byte value = 127;

			// decimal
			Assert::IsTrue(String("127").Compare(Integer::ToString(value)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("127").Compare(Integer::ToString((short)value)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("127").Compare(Integer::ToString((int)value)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("127").Compare(Integer::ToString((long)value)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("127").Compare(Integer::ToString((llong)value)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("127").Compare(Integer::ToString((ubyte)value)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("127").Compare(Integer::ToString((ushort)value)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("127").Compare(Integer::ToString((uint)value)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("127").Compare(Integer::ToString((ulong)value)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("127").Compare(Integer::ToString((ullong)value)) == 0, L"ToString", LINE_INFO());

			// octal
			Assert::IsTrue(String("0177").Compare(Integer::ToString(value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0177").Compare(Integer::ToString((short)value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0177").Compare(Integer::ToString((int)value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0177").Compare(Integer::ToString((long)value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0177").Compare(Integer::ToString((llong)value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0177").Compare(Integer::ToString((ubyte)value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0177").Compare(Integer::ToString((ushort)value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0177").Compare(Integer::ToString((uint)value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0177").Compare(Integer::ToString((ulong)value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0177").Compare(Integer::ToString((ullong)value, IntegerBase::Octal)) == 0, L"ToString", LINE_INFO());

			// hexadecimal
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString(value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString((short)value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString((int)value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString((long)value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString((llong)value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString((ubyte)value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString((ushort)value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString((uint)value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString((ulong)value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
			Assert::IsTrue(String("0x7f").Compare(Integer::ToString((ullong)value, IntegerBase::Hexadecimal)) == 0, L"ToString", LINE_INFO());
		}
	};
}