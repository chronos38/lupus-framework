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

#ifndef LUPUS_ITERATOR_HPP
#define LUPUS_ITERATOR_HPP

namespace Lupus {
	template <typename T>
	class Pointer;

	namespace System {
		template <typename T>
		class Iterator
		{
		public:
			virtual ~Iterator(){}
			virtual void First() = 0;
			virtual void Next() = 0;
			virtual bool IsDone() const = 0;
			virtual const T& CurrentItem() const = 0;
		};

		template <typename T>
		class Iterable
		{
		public:
			virtual Pointer<Iterator<T>> GetIterator() const = 0;
		};
	}
}

#endif
