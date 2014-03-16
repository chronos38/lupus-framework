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
		mReference(reference)
	{
	}

	template <typename T>
	PropertyReader<T>::operator T()
	{
		return mReference;
	}

	template <typename T>
	PropertyWriter<T>::PropertyWriter(T& reference) :
		mReference(reference)
	{
	}

	template <typename T>
	T PropertyWriter<T>::operator=(const T& value)
	{
		return (mReference = value);
	}

	template <typename T>
	PropertyAccess<T>::PropertyAccess(T& reference) :
		mReference(reference)
	{
	}

	template <typename T>
	PropertyAccess<T>::operator T()
	{
		return mReference;
	}

	template <typename T>
	T PropertyAccess<T>::operator=(const T& value)
	{
		return (mReference = value);
	}
}
