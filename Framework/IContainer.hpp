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

#ifndef LUPUS_ICONTAINER_HPP
#define LUPUS_ICONTAINER_HPP

#include "IIterator.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		class IContainer
		{
		public:
			virtual ~IContainer() { }
			virtual void Add(const T&) = 0;
			virtual IIterator<T> Begin() = 0;
			virtual T& Back() = 0;
			virtual const T& Back() const = 0;
			virtual void Clear() = 0;
			virtual int Count() const = 0;
			virtual T& Front() = 0;
			virtual const T& Front() const = 0;
			virtual bool IsEmpty() const = 0;
			virtual void Remove(const IIterator<T>&) = 0;
			virtual void Remove(int) = 0;
			virtual void Resize(int) = 0;
		};
	}
}

#endif
