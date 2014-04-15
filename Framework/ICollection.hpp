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

#ifndef LUPUS_ICOLLECTION_HPP
#define LUPUS_ICOLLECTION_HPP

#include "Iterator.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		class Vector;

		//! interface for collection types
		template <typename T>
		class ICollection : public Iterable<T>
		{
		public:
			/**
			 * Copy content from this instance to a collection container
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param sourceIndex starting index for this instance
			 * @param vector container to copy into
			 * @param destinationIndex starting index in container
			 * @param count how many values get copied
			 */
			virtual void CopyTo(int sourceIndex, Vector<T>& vector, int destinationIndex, int count) const = 0;
			/**
			 * Copy content from this instance to a collection container
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param vector container to copy into
			 * @param startIndex starts copying within this instance at given index
			 */
			virtual void CopyTo(Vector<T>& vector, int startIndex) const = 0;
			//! get current entry count
			virtual int Count() const = 0;
		};
	}
}

#endif
