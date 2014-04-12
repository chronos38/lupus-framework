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

#ifndef LUPUS_ICOMPARABLE_HPP
#define LUPUS_ICOMPARABLE_HPP

namespace Lupus {
	namespace System {
		//! interface for comparable types
		template <typename T>
		class IComparable
		{
		public:
			/**
			 * Compare given object to this instance
			 *
			 * @param object given object to compare to
			 * @return <0 this instance preceeds object; =0 this instance is equal to object; >0 this instance follows object
			 */
			virtual int Compare(const T& object) const = 0;
		};
	}
}

#endif
