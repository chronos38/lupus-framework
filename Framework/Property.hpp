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
	class PropertyReader
	{
		T& _reference;
	public:
		PropertyReader() = delete;
		PropertyReader(const PropertyReader<T>&) = default;
		PropertyReader<T>& operator=(const PropertyReader<T>&);
		PropertyReader(T& reference);
		operator T() const;
	};

	template <typename T>
	class PropertyWriter
	{
		T& _reference;
	public:
		PropertyWriter() = delete;
		PropertyWriter(const PropertyWriter<T>&) = default;
		PropertyWriter<T>& operator=(const PropertyWriter<T>&);
		PropertyWriter(T& reference);
		T operator=(const T& value);
	};

	template <typename T>
	class PropertyAccess
	{
		T& _reference;
	public:
		PropertyAccess() = delete;
		PropertyAccess(const PropertyAccess<T>&) = default;
		PropertyAccess<T>& operator=(const PropertyAccess<T>&);
		PropertyAccess(T& reference);
		T operator=(const T& value);
		operator T() const;
	};

	template <typename T, typename U>
	bool operator==(const PropertyReader<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator==(const U& lhs, const PropertyReader<T>& rhs);
	template <typename T, typename U>
	bool operator!=(const PropertyReader<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator!=(const U& lhs, const PropertyReader<T>& rhs);

	template <typename T, typename U>
	bool operator==(const PropertyWriter<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator==(const U& lhs, const PropertyWriter<T>& rhs);
	template <typename T, typename U>
	bool operator!=(const PropertyWriter<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator!=(const U& lhs, const PropertyWriter<T>& rhs);

	template <typename T, typename U>
	bool operator==(const PropertyAccess<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator==(const U& lhs, const PropertyAccess<T>& rhs);
	template <typename T, typename U>
	bool operator!=(const PropertyAccess<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator!=(const U& lhs, const PropertyAccess<T>& rhs);
}

#include "Property.inl"

#endif
