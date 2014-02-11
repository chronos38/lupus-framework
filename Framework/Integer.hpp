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

#ifndef LUPUS_INTEGER_HPP
#define LUPUS_INTEGER_HPP

#include "Object.hpp"

namespace Lupus {
	namespace System {
		class String;

		class LUPUS_API Integer : public Object
		{
		public:
			static String ToString(byte, IntegerBase = IntegerBase::Decimal);
			static String ToString(short, IntegerBase = IntegerBase::Decimal);
			static String ToString(int, IntegerBase = IntegerBase::Decimal);
			static String ToString(long, IntegerBase = IntegerBase::Decimal);
			static String ToString(llong, IntegerBase = IntegerBase::Decimal);
			static String ToString(ubyte, IntegerBase = IntegerBase::Decimal);
			static String ToString(ushort, IntegerBase = IntegerBase::Decimal);
			static String ToString(uint, IntegerBase = IntegerBase::Decimal);
			static String ToString(ulong, IntegerBase = IntegerBase::Decimal);
			static String ToString(ullong, IntegerBase = IntegerBase::Decimal);
		};
	}
}

#endif
