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
	namespace System {
		template <typename T>
		Pointer<ListSortStrategy<T>> List<T>::_defaultStrategy = new ListQuickSort<T>();
		template <typename T>
		PropertyWriter<Pointer<ListSortStrategy<T>>> List<T>::DefaultListSortAlgorithm =
			PropertyWriter<Pointer<ListSortStrategy<T>>>(List<T>::_defaultStrategy);

		template <typename T>
		List<T>::List()
		{
		}

		template <typename T>
		List<T>::List(const List<T>& list)
		{
			throw NotImplementedException();
		}

		template <typename T>
		List<T>::List(List<T>&& list)
		{
			throw NotImplementedException();
		}

		template <typename T>
		List<T>::List(const ISequence<T>& sequence)
		{
			throw NotImplementedException();
		}

		template <typename T>
		List<T>::List(const std::initializer_list<T>& list)
		{
			throw NotImplementedException();
		}

		template <typename T>
		List<T>::List(int count)
		{
			throw NotImplementedException();
		}

		template <typename T>
		List<T>::~List()
		{
			Clear();
		}

		template <typename T>
		void List<T>::Add(const T& value)
		{
			throw NotImplementedException();
		}

		template <typename T>
		T& List<T>::Back()
		{
			throw NotImplementedException();
		}

		template <typename T>
		const T& List<T>::Back() const
		{
			throw NotImplementedException();
		}

		template <typename T>
		Pointer<Iterator<T>> List<T>::GetIterator() const
		{
			return new ListIterator<T>(this);
		}

		template <typename T>
		void List<T>::Clear()
		{
			for (Node* node = _node; node;) {
				Node* swap = node->Next;
				delete node;
				node = swap;
			}

			_length = 0;
		}

		template <typename T>
		bool List<T>::Contains(const T& value) const
		{
			throw NotImplementedException();
		}

		template <typename T>
		void List<T>::CopyTo(Vector<T>&, int) const
		{
			throw NotImplementedException();
		}

		template <typename T>
		void List<T>::CopyTo(int, Vector<T>&, int, int) const
		{
			throw NotImplementedException();
		}

		template <typename T>
		int List<T>::Count() const
		{
			return _length;
		}

		template <typename T>
		T& List<T>::Front()
		{
			throw NotImplementedException();
		}

		template <typename T>
		const T& List<T>::Front() const
		{
			throw NotImplementedException();
		}

		template <typename T>
		void List<T>::Insert(int, const T&)
		{
			throw NotImplementedException();
		}

		template <typename T>
		bool List<T>::IsEmpty() const
		{
			return (_length == 0);
		}

		template <typename T>
		bool List<T>::RemoveAt(int)
		{
			throw NotImplementedException();
		}

		template <typename T>
		void List<T>::Resize(int)
		{
			throw NotImplementedException();
		}

		template <typename T>
		T& List<T>::operator[](int)
		{
			throw NotImplementedException();
		}

		template <typename T>
		const T& List<T>::operator[](int) const
		{
			throw NotImplementedException();
		}

		template <typename T>
		List<T>& List<T>::operator=(const List<T>&)
		{
			throw NotImplementedException();
		}

		template <typename T>
		List<T>& List<T>::operator=(List<T>&&)
		{
			throw NotImplementedException();
		}

		template <typename T>
		List<T>& List<T>::operator=(const ISequence<T>&)
		{
			throw NotImplementedException();
		}

		template <typename T>
		List<T>::Node::Node(const T& data)
		{
			_data = data;
		}

		template <typename T>
		ListIterator<T>::ListIterator(ListIterator<T>&& iterator)
		{
			Swap(iterator._list, _list);
			Swap(iterator._current, _current);
		}

		template <typename T>
		ListIterator<T>::ListIterator(const List<T>& list) :
			_list(&list)
		{
		}

		template <typename T>
		ListIterator<T>::ListIterator(const List<T>* list) :
			_list(list)
		{
			if (!list) {
				throw ArgumentNullException();
			}
		}

		template <typename T>
		ListIterator<T>::~ListIterator()
		{
		}

		template <typename T>
		void ListIterator<T>::First()
		{
			_current = _list->_node;
		}

		template <typename T>
		void ListIterator<T>::Next()
		{
			_current = _current->Next;
		}

		template <typename T>
		bool ListIterator<T>::IsDone() const
		{
			return (_current != nullptr);
		}

		template <typename T>
		const T& ListIterator<T>::CurrentItem() const
		{
			if (IsDone()) {
				throw IteratorOutOfBoundException();
			}

			return (_node->Data);
		}

		template <typename T>
		ListIterator<T>& ListIterator<T>::operator=(ListIterator<T>&& iterator)
		{
			Swap(iterator._sequence, _sequence);
			Swap(iterator._current, _current);
			return (*this);
		}

		template <typename T>
		Pointer<ListSortStrategy<T>> ListQuickSort<T>::Copy() const
		{
			return new ListQuickSort();
		}

		template <typename T>
		void ListQuickSort<T>::Sort(List<T>& list)
		{
			throw NotImplementedException();
		}
	}
}
