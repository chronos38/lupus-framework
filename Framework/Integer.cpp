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

#include "Integer.hpp"
#include "Char.hpp"
#include "String.hpp"

static const size_t sIntegerCount = 32;

namespace Lupus {
	namespace System {
		String Integer::ToString(byte value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%hhd"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#hhx"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#hho"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(short value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%hd"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#hx"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#ho"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(int value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%d"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#x"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#o"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(long value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%ld"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#lx"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#lo"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(llong value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%lld"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#llx"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#llo"), value);
				break;
			}
			return result;
		}
		String Integer::ToString(ubyte value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%hhu"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#hhx"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#hho"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(ushort value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%hu"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#hx"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#ho"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(uint value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%u"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#x"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#o"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(ulong value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%lu"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#lx"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#lo"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(ullong value, IntegerBase base)
		{
			char result[sIntegerCount];
			memset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				snprintf(result, sIntegerCount, ("%llu"), value);
				break;
			case IntegerBase::Hexadecimal:
				snprintf(result, sIntegerCount, ("%#llx"), value);
				break;
			case IntegerBase::Octal:
				snprintf(result, sIntegerCount, ("%#llo"), value);
				break;
			}
			return result;
		}

		bool Integer::TryParse(const String& string, byte& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%hhd"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%hhx"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%hho"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, short& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%hd"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%hx"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%ho"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, int& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%d"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%x"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%o"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, long& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%ld"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%lx"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%lo"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, llong& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%lld"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%llx"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%llo"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, ubyte& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%hhu"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%hhx"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%hho"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, ushort& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%hu"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%hx"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%ho"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, uint& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%u"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%x"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%o"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, ulong& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%lu"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%lx"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%lo"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, ullong& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (sscanf(string.Data, ("%llu"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (sscanf(string.Data, ("%llx"), &result) == 1);
			case IntegerBase::Octal:
				return (sscanf(string.Data, ("%llo"), &result) == 1);
			}
			return false;
		}
	}
}
