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

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Integer.hpp"
#include "Char.hpp"
#include "String.hpp"
#include <cstdio>
#include <cstring>

namespace Lupus {
	namespace System {
		String Integer::ToString(byte value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%o", (int)value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%d", (int)value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%x", (int)value);
				break;
			}
			return result;
		}

		String Integer::ToString(short value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%o", (int)value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%d", (int)value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%x", (int)value);
				break;
			}
			return result;
		}

		String Integer::ToString(int value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%o", value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%d", value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%x", value);
				break;
			}
			return result;
		}

		String Integer::ToString(long value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%lo", value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%ld", value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%lx", value);
				break;
			}
			return result;
		}

		String Integer::ToString(llong value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%llo", value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%lld", value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%llx", value);
				break;
			}
			return result;
		}
		String Integer::ToString(ubyte value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%o", (uint)value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%u", (uint)value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%x", (uint)value);
				break;
			}
			return result;
		}

		String Integer::ToString(ushort value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%o", (uint)value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%u", (uint)value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%x", (uint)value);
				break;
			}
			return result;
		}

		String Integer::ToString(uint value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%o", value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%u", value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%x", value);
				break;
			}
			return result;
		}

		String Integer::ToString(ulong value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%lo", value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%lu", value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%lx", value);
				break;
			}
			return result;
		}

		String Integer::ToString(ullong value, IntegerBase base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case IntegerBase::Octal:
				sprintf(result, "%llo", value);
				break;
			case IntegerBase::Decimal:
				sprintf(result, "%llu", value);
				break;
			case IntegerBase::Hexadecimal:
				sprintf(result, "%llx", value);
				break;
			}
			return result;
		}
	}
}
