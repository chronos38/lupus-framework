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

#ifndef LUPUS_ISEQUENCE_HPP
#define LUPUS_ISEQUENCE_HPP

#include "Types.hpp"
#include "ICollection.hpp"

namespace Lupus {
	namespace System {
		//! interface for sequence types
		template <typename T>
		class ISequence : public ICollection<T>
		{
		public:
			virtual ~ISequence() { }
			//! add a new entry
			virtual void Add(const T&) = 0;
			//! get last entry
			virtual T& Back() = 0;
			//! get last entry
			virtual const T& Back() const = 0;
			//! clear entire content
			virtual void Clear() = 0;
			//! check if sequence contains given value
			virtual bool Contains(const T&) const = 0;
			//! get first entry
			virtual T& Front() = 0;
			//! get first entry
			virtual const T& Front() const = 0;
			/**
			 * insert at given index new entry with provided value
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param index position within this instance for insertion
			 * @param value value for new entry
			 */
			virtual void Insert(int index, const T& value) = 0;
			//! check if container ist empty
			virtual bool IsEmpty() const = 0;
			//! try to remove entry at given index
			virtual bool RemoveAt(int) = 0;
			/**
			 * resize container to given value.
			 * if count is smaller than current length, than all content between count and length is deleted
			 * if count is greater than current capacity, than new space will be allocated
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param count new size for this container
			 */
			virtual void Resize(int count) = 0;
		};
	}
}

#endif
