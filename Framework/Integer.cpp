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
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%hhd"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#hhx"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#hho"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(short value, IntegerBase base)
		{
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%hd"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#hx"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#ho"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(int value, IntegerBase base)
		{
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%d"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#x"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#o"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(long value, IntegerBase base)
		{
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%ld"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#lx"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#lo"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(llong value, IntegerBase base)
		{
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%lld"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#llx"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#llo"), value);
				break;
			}
			return result;
		}
		String Integer::ToString(ubyte value, IntegerBase base)
		{
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%hhu"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#hhx"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#hho"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(ushort value, IntegerBase base)
		{
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%hu"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#hx"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#ho"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(uint value, IntegerBase base)
		{
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%u"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#x"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#o"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(ulong value, IntegerBase base)
		{
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%lu"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#lx"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#lo"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(ullong value, IntegerBase base)
		{
			_lchar result[sIntegerCount];
			_lmemset(result, 0, sIntegerCount);

			switch (base) {
			case IntegerBase::Decimal:
				_lsprintf(result, sIntegerCount, _lstring("%llu"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sIntegerCount, _lstring("%#llx"), value);
				break;
			case IntegerBase::Octal:
				_lsprintf(result, sIntegerCount, _lstring("%#llo"), value);
				break;
			}
			return result;
		}

		bool Integer::TryParse(const String& string, byte& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%hhd"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%hhx"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%hho"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, short& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%hd"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%hx"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%ho"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, int& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%d"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%x"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%o"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, long& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%ld"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%lx"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%lo"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, llong& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%lld"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%llx"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%llo"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, ubyte& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%hhu"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%hhx"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%hho"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, ushort& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%hu"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%hx"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%ho"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, uint& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%u"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%x"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%o"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, ulong& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%lu"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%lx"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%lo"), &result) == 1);
			}
			return false;
		}

		bool Integer::TryParse(const String& string, ullong& result, IntegerBase base)
		{
			switch (base) {
			case IntegerBase::Decimal:
				return (_lsscanf(string.Data, _lstring("%llu"), &result) == 1);
			case IntegerBase::Hexadecimal:
				return (_lsscanf(string.Data, _lstring("%llx"), &result) == 1);
			case IntegerBase::Octal:
				return (_lsscanf(string.Data, _lstring("%llo"), &result) == 1);
			}
			return false;
		}
	}
}
