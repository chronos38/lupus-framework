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

#ifndef LUPUS_ISEQUENCE_HPP
#define LUPUS_ISEQUENCE_HPP

#include "Object.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		class Iterator;
		template <typename T>
		class SequenceIterator;

		template <typename T>
		class ISequence
		{
		public:
			virtual ~ISequence() { }
			virtual void Add(const T&) = 0;
			virtual T& Back() = 0;
			virtual const T& Back() const = 0;
			virtual SequenceIterator<T> Begin() const = 0;
			virtual void Clear() = 0;
			virtual bool Contains(const T&) const = 0;
			virtual void CopyTo(ISequence<T>&, int) const = 0;
			/**
			 * Copy content from this instance to a sequence container
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param sourceIndex starting index for this instance
			 * @param sequence container to copy into
			 * @param destinationIndex starting index in container
			 * @param count how many chars get copied
			 */
			virtual void CopyTo(int, ISequence<T>&, int, int) const = 0;
			virtual int Count() const = 0;
			virtual T& Front() = 0;
			virtual const T& Front() const = 0;
			virtual void Insert(int, const T&) = 0;
			virtual bool IsEmpty() const = 0;
			virtual bool RemoveAt(int) = 0;
			virtual void Resize(int) = 0;
			virtual T& operator[](int) = 0;
			virtual const T& operator[](int) const = 0;
		};
	}
}

#endif
