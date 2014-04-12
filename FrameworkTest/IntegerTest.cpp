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
#include "..\Framework\Integer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Lupus;
using namespace Lupus::System;

namespace FrameworkTest {
	TEST_CLASS(IntegerTest)
	{
		TEST_METHOD(IntegerToStringTest)
		{
			// variables
			sbyte value = 127;

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

		TEST_METHOD(IntegerTryParseTest)
		{
			// variables
			String dec = "127";
			String hex = "0xff";
			String oct = "0001";

			// results
			sbyte hhd;
			short hd;
			int d;
			long ld;
			llong lld;
			ubyte hhu;
			ushort hu;
			uint u;
			ulong lu;
			ullong llu;

			// decimal
			Assert::IsTrue(Integer::TryParse(dec, hhd) && hhd == 127, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(dec, hd) && hd == 127, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(dec, d) && d == 127, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(dec, ld) && ld == 127, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(dec, lld) && lld == 127, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(dec, hhu) && hhu == 127, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(dec, hu) && hu == 127, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(dec, u) && u == 127, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(dec, lu) && lu == 127, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(dec, llu) && llu == 127, L"TryParse", LINE_INFO());

			// hexadecimal
			Assert::IsTrue(Integer::TryParse(hex, hhd, IntegerBase::Hexadecimal) && hhd == -1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(hex, hd, IntegerBase::Hexadecimal) && hd == 255, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(hex, d, IntegerBase::Hexadecimal) && d == 255, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(hex, ld, IntegerBase::Hexadecimal) && ld == 255, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(hex, lld, IntegerBase::Hexadecimal) && lld == 255, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(hex, hhu, IntegerBase::Hexadecimal) && hhu == 255, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(hex, hu, IntegerBase::Hexadecimal) && hu == 255, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(hex, u, IntegerBase::Hexadecimal) && u == 255, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(hex, lu, IntegerBase::Hexadecimal) && lu == 255, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(hex, llu, IntegerBase::Hexadecimal) && llu == 255, L"TryParse", LINE_INFO());

			// octal
			Assert::IsTrue(Integer::TryParse(oct, hhd, IntegerBase::Octal) && hhd == 1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(oct, hd, IntegerBase::Octal) && hd == 1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(oct, d, IntegerBase::Octal) && d == 1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(oct, ld, IntegerBase::Octal) && ld == 1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(oct, lld, IntegerBase::Octal) && lld == 1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(oct, hhu, IntegerBase::Octal) && hhu == 1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(oct, hu, IntegerBase::Octal) && hu == 1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(oct, u, IntegerBase::Octal) && u == 1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(oct, lu, IntegerBase::Octal) && lu == 1, L"TryParse", LINE_INFO());
			Assert::IsTrue(Integer::TryParse(oct, llu, IntegerBase::Octal) && llu == 1, L"TryParse", LINE_INFO());
		}
	};
}
