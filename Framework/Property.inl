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

namespace Lupus {
	template <typename T>
	PropertyReader<T>::PropertyReader(T& reference) :
		_reference(reference)
	{
	}

	template <typename T>
	PropertyReader<T>& PropertyReader<T>::operator=(const PropertyReader<T>& propertyReader)
	{
		_reference = propertyReader._reference;
	}

	template <typename T>
	PropertyReader<T>::operator T() const
	{
		return _reference;
	}

	template <typename T>
	PropertyWriter<T>::PropertyWriter(T& reference) :
		_reference(reference)
	{
	}

	template <typename T>
	PropertyWriter<T>& PropertyWriter<T>::operator=(const PropertyWriter<T>& propertyWriter)
	{
		_reference = propertyWriter._reference;
	}

	template <typename T>
	T PropertyWriter<T>::operator=(const T& value)
	{
		return (_reference = value);
	}

	template <typename T>
	PropertyAccess<T>::PropertyAccess(T& reference) :
		_reference(reference)
	{
	}

	template <typename T>
	PropertyAccess<T>& PropertyAccess<T>::operator=(const PropertyAccess<T>& propertyAccess)
	{
		_reference = propertyAccess._reference;
	}

	template <typename T>
	PropertyAccess<T>::operator T() const
	{
		return _reference;
	}

	template <typename T>
	T PropertyAccess<T>::operator=(const T& value)
	{
		return (_reference = value);
	}

	template <typename T, typename U>
	bool operator==(const PropertyReader<T>& lhs, const U& rhs)
	{
		return (static_cast<U>(lhs) == rhs);
	}

	template <typename T, typename U>
	bool operator==(const U& lhs, const PropertyReader<T>& rhs)
	{
		return (lhs == static_cast<U>(rhs));
	}

	template <typename T, typename U>
	bool operator!=(const PropertyReader<T>& lhs, const U& rhs)
	{
		return (static_cast<U>(lhs) != rhs);
	}

	template <typename T, typename U>
	bool operator!=(const U& lhs, const PropertyReader<T>& rhs)
	{
		return (lhs != static_cast<U>(rhs));
	}

	template <typename T, typename U>
	bool operator==(const PropertyWriter<T>& lhs, const U& rhs)
	{
		return (static_cast<U>(lhs) == rhs);
	}

	template <typename T, typename U>
	bool operator==(const U& lhs, const PropertyWriter<T>& rhs)
	{
		return (lhs == static_cast<U>(rhs));
	}

	template <typename T, typename U>
	bool operator!=(const PropertyWriter<T>& lhs, const U& rhs)
	{
		return (static_cast<U>(lhs) != rhs);
	}

	template <typename T, typename U>
	bool operator!=(const U& lhs, const PropertyWriter<T>& rhs)
	{
		return (lhs != static_cast<U>(rhs));
	}

	template <typename T, typename U>
	bool operator==(const PropertyAccess<T>& lhs, const U& rhs)
	{
		return (static_cast<U>(lhs) == rhs);
	}

	template <typename T, typename U>
	bool operator==(const U& lhs, const PropertyAccess<T>& rhs)
	{
		return (lhs == static_cast<U>(rhs));
	}

	template <typename T, typename U>
	bool operator!=(const PropertyAccess<T>& lhs, const U& rhs)
	{
		return (static_cast<U>(lhs) != rhs);
	}

	template <typename T, typename U>
	bool operator!=(const U& lhs, const PropertyAccess<T>& rhs)
	{
		return (lhs != static_cast<U>(rhs));
	}
}
