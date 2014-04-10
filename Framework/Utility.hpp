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

#ifndef LUPUS_UTILITY_HPP
#define LUPUS_UTITLIY_HPP

/**
 * Iterate through whole container
 * @param item iteration variable as iterator type
 * @param container sequence or dictionary type
 *
 * usage:	foreach(item, container) { 
 *			// do things with 'item'
 *		}
 */
#define foreach(item, container) for (auto item = container.GetIterator(); !(item->IsDone()); item->Next())

namespace Lupus {
	/**
	 * Swaps two values
	 *
	 * @param lhs left hand value
	 * @param rhs right hand value
	 */
	template <typename T>
	void Swap(T& lhs, T& rhs);
}

#include "Utility.inl"

#endif
