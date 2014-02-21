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
#include <cstdio>
#include <cstring>

static const size_t sCount = 32;

namespace Lupus {
	namespace System {
		String Integer::ToString(byte value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%o"), (int)value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%d"), (int)value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%x"), (int)value);
				break;
			}
			return result;
		}

		String Integer::ToString(short value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%o"), (int)value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%d"), (int)value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%x"), (int)value);
				break;
			}
			return result;
		}

		String Integer::ToString(int value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%o"), value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%d"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%x"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(long value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%lo"), value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%ld"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%lx"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(llong value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%llo"), value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%lld"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%llx"), value);
				break;
			}
			return result;
		}
		String Integer::ToString(ubyte value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%o"), (uint)value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%u"), (uint)value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%x"), (uint)value);
				break;
			}
			return result;
		}

		String Integer::ToString(ushort value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%o"), (uint)value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%u"), (uint)value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%x"), (uint)value);
				break;
			}
			return result;
		}

		String Integer::ToString(uint value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%o"), value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%u"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%x"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(ulong value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%lo"), value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%lu"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%lx"), value);
				break;
			}
			return result;
		}

		String Integer::ToString(ullong value, IntegerBase base)
		{
			_lchar result[sCount];
			_lmemset(result, 0, sCount);

			switch (base) {
			case IntegerBase::Octal:
				_lsprintf(result, sCount, _lstring("0%llo"), value);
				break;
			case IntegerBase::Decimal:
				_lsprintf(result, sCount, _lstring("%llu"), value);
				break;
			case IntegerBase::Hexadecimal:
				_lsprintf(result, sCount, _lstring("0x%llx"), value);
				break;
			}
			return result;
		}
	}
}
