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

#ifndef LUPUS_POINTER_HPP
#define LUPUS_POINTER_HPP

namespace Lupus {
	namespace System {
		template <typename T>
		class Pointer
		{
			T* _pointer = nullptr;
		public:
			Pointer() = delete;
			Pointer(const Pointer<T>&) = delete;
			Pointer(Pointer<T>&&);
			Pointer(T* pointer);
			~Pointer();
			T& operator*();
			const T& operator*() const;
			T* operator->();
			const T* operator->() const;
			Pointer<T>& operator=(const Pointer<T>&) = delete;
			Pointer<T>& operator=(Pointer<T>&&);
			Pointer<T>& operator=(T*);
		};
	}
}

#include "Pointer.inl"

#endif
