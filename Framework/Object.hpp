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

#ifndef LUPUS_OBJECT_HPP
#define LUPUS_OBJECT_HPP

#include "Types.hpp"

namespace Lupus {
	namespace System {
		class String;
	}

	class LUPUS_API Object
	{
	public:
		virtual ~Object();
		virtual ulong GetHashCode() const;
		virtual System::String GetName() const final;
	};
}

#endif
