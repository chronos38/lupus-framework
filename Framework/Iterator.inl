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

#include "Exception.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		const T& Iterator<T>::CurrentItem() const
		{
			throw NotSupportedException("iterator does not support this method");
		}

		template <typename T>
		bool Iterator<T>::IsDone() const
		{
			throw NotSupportedException("iterator does not support this method");
		}

		template <typename T>
		void Iterator<T>::First()
		{
			throw NotSupportedException("iterator does not support this method");
		}

		template <typename T>
		void Iterator<T>::Next()
		{
			throw NotSupportedException("iterator does not support this method");
		}
	}
}
