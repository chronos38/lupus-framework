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
		List<T>::List()
		{
		}

		template <typename T>
		List<T>::List(const List<T>& list)
		{
		}

		template <typename T>
		List<T>::List(List<T>&&)
		{
		}

		template <typename T>
		List<T>::List(const ISequence<T>&)
		{
		}

		template <typename T>
		List<T>::List(const std::initializer_list<T>&)
		{
		}

		template <typename T>
		List<T>::List(int)
		{
		}

		template <typename T>
		List<T>::~List()
		{
		}

		template <typename T>
		void List<T>::Add(const T&)
		{
		}

		template <typename T>
		T& List<T>::Back()
		{
		}

		template <typename T>
		const T& List<T>::Back() const
		{
		}

		template <typename T>
		SequenceIterator<T> List<T>::ForwardIterator() const
		{
		}

		template <typename T>
		ReverseSequenceIterator<T> List<T>::ReverseIterator() const
		{
		}

		template <typename T>
		void List<T>::Clear()
		{
		}

		template <typename T>
		bool List<T>::Contains(const T&) const
		{
		}

		template <typename T>
		void List<T>::CopyTo(ISequence<T>&, int) const
		{
		}

		template <typename T>
		void List<T>::CopyTo(int, ISequence<T>&, int, int) const
		{
		}

		template <typename T>
		int List<T>::Count() const
		{
		}

		template <typename T>
		T& List<T>::Front()
		{
		}

		template <typename T>
		const T& List<T>::Front() const
		{
		}

		template <typename T>
		void List<T>::Insert(int, const T&)
		{
		}

		template <typename T>
		bool List<T>::IsEmpty() const
		{
		}

		template <typename T>
		bool List<T>::RemoveAt(int)
		{
		}

		template <typename T>
		void List<T>::Resize(int)
		{
		}

		template <typename T>
		T& List<T>::operator[](int)
		{
		}

		template <typename T>
		const T& List<T>::operator[](int) const
		{
		}

		template <typename T>
		List<T>& List<T>::operator=(const List<T>&)
		{
		}

		template <typename T>
		List<T>& List<T>::operator=(List<T>&&)
		{
		}

		template <typename T>
		List<T>& List<T>::operator=(const ISequence<T>&)
		{
		}
	}
}
