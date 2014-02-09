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

namespace lupus {
	namespace system {
		class String;

		enum class Base
		{
			Octal,
			Decimal,
			Hexadecimal
		};

		class LUPUS_API Integer : public Object
		{
		public:
			static String ToString(byte, Base = Base::Decimal);
			static String ToString(short, Base = Base::Decimal);
			static String ToString(int, Base = Base::Decimal);
			static String ToString(long, Base = Base::Decimal);
			static String ToString(llong, Base = Base::Decimal);
			static String ToString(ubyte, Base = Base::Decimal);
			static String ToString(ushort, Base = Base::Decimal);
			static String ToString(uint, Base = Base::Decimal);
			static String ToString(ulong, Base = Base::Decimal);
			static String ToString(ullong, Base = Base::Decimal);
		};
	}
}

#endif
