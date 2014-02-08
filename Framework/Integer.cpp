/* This file is part of LupusFramwork.
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

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Integer.hpp"
#include "Char.hpp"
#include "String.hpp"
#include <cstdio>
#include <cstring>

namespace lupus {
	namespace system {
		String Integer::ToString(byte value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%o", (int)value);
				break;
			case Base::Decimal:
				sprintf(result, "%d", (int)value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%x", (int)value);
				break;
			}
			return result;
		}

		String Integer::ToString(short value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%o", (int)value);
				break;
			case Base::Decimal:
				sprintf(result, "%d", (int)value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%x", (int)value);
				break;
			}
			return result;
		}

		String Integer::ToString(int value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%o", value);
				break;
			case Base::Decimal:
				sprintf(result, "%d", value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%x", value);
				break;
			}
			return result;
		}

		String Integer::ToString(long value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%lo", value);
				break;
			case Base::Decimal:
				sprintf(result, "%ld", value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%lx", value);
				break;
			}
			return result;
		}

		String Integer::ToString(llong value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%llo", value);
				break;
			case Base::Decimal:
				sprintf(result, "%lld", value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%llx", value);
				break;
			}
			return result;
		}
		String Integer::ToString(ubyte value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%o", (uint)value);
				break;
			case Base::Decimal:
				sprintf(result, "%u", (uint)value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%x", (uint)value);
				break;
			}
			return result;
		}

		String Integer::ToString(ushort value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%o", (uint)value);
				break;
			case Base::Decimal:
				sprintf(result, "%u", (uint)value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%x", (uint)value);
				break;
			}
			return result;
		}

		String Integer::ToString(uint value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%o", value);
				break;
			case Base::Decimal:
				sprintf(result, "%u", value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%x", value);
				break;
			}
			return result;
		}

		String Integer::ToString(ulong value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%lo", value);
				break;
			case Base::Decimal:
				sprintf(result, "%lu", value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%lx", value);
				break;
			}
			return result;
		}

		String Integer::ToString(ullong value, Base base)
		{
			char result[32] = { 0 };
			memset(result, 0, 32);

			switch (base) {
			case Base::Octal:
				sprintf(result, "%llo", value);
				break;
			case Base::Decimal:
				sprintf(result, "%llu", value);
				break;
			case Base::Hexadecimal:
				sprintf(result, "%llx", value);
				break;
			}
			return result;
		}
	}
}
