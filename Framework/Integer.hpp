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

#ifndef LUPUS_INTEGER_HPP
#define LUPUS_INTEGER_HPP

#include "Types.hpp"

namespace Lupus {
	namespace System {
		// declarations
		class String;

		//! conversion base for integer
		enum class IntegerBase {
			Octal,
			Decimal,
			Hexadecimal
		};

		//! conversion class for integer types
		class LUPUS_API Integer
		{
		public:
			//! \sa Integer::ToString(int, IntegerBase)
			static String ToString(sbyte value, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::ToString(int, IntegerBase)
			static String ToString(short value, IntegerBase base = IntegerBase::Decimal);
			/**
			 * convert an integer to its respective string
			 *
			 * @param value integer to convert
			 * @param base either octal, decimal or hexadecimal
			 * @return conversion result as a string
			 */
			static String ToString(int value, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::ToString(int, IntegerBase)
			static String ToString(long value, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::ToString(int, IntegerBase)
			static String ToString(llong value, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::ToString(int, IntegerBase)
			static String ToString(ubyte value, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::ToString(int, IntegerBase)
			static String ToString(ushort value, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::ToString(int, IntegerBase)
			static String ToString(uint value, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::ToString(int, IntegerBase)
			static String ToString(ulong value, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::ToString(int, IntegerBase)
			static String ToString(ullong value, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::TryParse(String&, int, IntegerBase)
			static bool TryParse(const String& string, sbyte& result, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::TryParse(String&, int, IntegerBase)
			static bool TryParse(const String& string, short& result, IntegerBase base = IntegerBase::Decimal);
			/**
			 * convert a string to its respective integer value
			 *
			 * @param string string to convert
			 * @param result output argument where the conversion result is written to
			 * @param base either octal, decimal or hexadecimal
			 * @return true if successful, otherwise false
			 */
			static bool TryParse(const String& string, int& result, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::TryParse(String&, int, IntegerBase)
			static bool TryParse(const String& string, long& result, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::TryParse(String&, int, IntegerBase)
			static bool TryParse(const String& string, llong& result, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::TryParse(String&, int, IntegerBase)
			static bool TryParse(const String& string, ubyte& result, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::TryParse(String&, int, IntegerBase)
			static bool TryParse(const String& string, ushort& result, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::TryParse(String&, int, IntegerBase)
			static bool TryParse(const String& string, uint& result, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::TryParse(String&, int, IntegerBase)
			static bool TryParse(const String& string, ulong& result, IntegerBase base = IntegerBase::Decimal);
			//! \sa Integer::TryParse(String&, int, IntegerBase)
			static bool TryParse(const String& string, ullong& result, IntegerBase base = IntegerBase::Decimal);
		};
	}
}

#endif
