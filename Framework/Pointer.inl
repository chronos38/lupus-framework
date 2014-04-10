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
	Pointer<T>::Pointer(Pointer<T>&& pointer)
	{
		Swap(_pointer, pointer._pointer);
	}

	template <typename T>
	Pointer<T>::Pointer(T* pointer)
	{
		_pointer = pointer;
	}

	template <typename T>
	Pointer<T>::~Pointer()
	{
		if (_pointer) {
			delete _pointer;
		}
	}

	template <typename T>
	T* Pointer<T>::Release()
	{
		T* result = _pointer;
		_pointer = nullptr;
		return result;
	}

	template <typename T>
	T& Pointer<T>::operator*()
	{
		if (!_pointer) {
			throw NullPointerException();
		}

		return (*_pointer);
	}

	template <typename T>
	const T& Pointer<T>::operator*() const
	{
		if (!_pointer) {
			throw NullPointerException();
		}

		return (*_pointer);
	}

	template <typename T>
	T* Pointer<T>::operator->()
	{
		return _pointer;
	}

	template <typename T>
	const T* Pointer<T>::operator->() const
	{
		return _pointer;
	}

	template <typename T>
	Pointer<T>& Pointer<T>::operator=(Pointer<T>&& pointer)
	{
		Swap(_pointer, pointer._pointer);
	}

	template <typename T>
	Pointer<T>& Pointer<T>::operator=(T* pointer)
	{
		if (_pointer) {
			delete _pointer;
		}

		_pointer = pointer;
	}
}
