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

#ifndef LUPUS_PROPERTY_HPP
#define LUPUS_PROPERTY_HPP

namespace Lupus {
	template <typename T>
	class LUPUS_API PropertyReader
	{
		T& mReference;
	public:
		PropertyReader<T>& operator=(const PropertyReader<T>&) = default;
		PropertyReader(T& reference);
		operator T();
	};

	template <typename T>
	class LUPUS_API PropertyWriter
	{
		T& mReference;
	public:
		PropertyWriter<T>& operator=(const PropertyWriter<T>&) = default;
		PropertyWriter(T& reference);
		T operator=(const T& value);
	};

	template <typename T>
	class LUPUS_API PropertyAccess
	{
		T& mReference;
	public:
		PropertyAccess<T>& operator=(const PropertyAccess<T>&) = default;
		PropertyAccess(T& reference);
		T operator=(const T& value);
		operator T();
	};
}

#include "Property.inl"

#endif
