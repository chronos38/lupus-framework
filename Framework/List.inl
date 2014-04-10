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
		List<T>::List()
		{
		}

		template <typename T>
		List<T>::List(const List<T>& list) :
			_length(list.Count())
		{
			if (!_length) {
				return;
			}

			_node = new Node(list._node->Data);

			for (Node* it = list._node->Next, node = _node; it; node = node->Next) {
				node->Next = new Node(it->Data);
			}
		}

		template <typename T>
		List<T>::List(List<T>&& list)
		{
			Swap(list._node, _node);
			Swap(list._head, _head);
			Swap(list._length, _length);
		}

		template <typename T>
		List<T>::List(const ISequence<T>& sequence) :
			_length(sequence.Count())
		{
			if (!_length) {
				return;
			}

			Node* node = _node;
			_node->Date = sequence[1];

			for (int i = 1; i < _length; i++, node = node->Next) {
				node->Next = new Node(sequence[i]);
			}
		}

		template <typename T>
		List<T>::List(const std::initializer_list<T>& list) :
			_length((int)list.size())
		{
			if (!_length) {
				return;
			}

			auto it = list.begin();
			Node* node = _node;
			_node->Date = (*it);

			for (int i = 1; i < _length; i++, node = node->Next) {
				node->Next = new Node(*(it + i));
			}
		}

		template <typename T>
		List<T>::List(int count) :
			_length(count)
		{
			if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greate or equal to zero");
			} else if (!_length) {
				return;
			}

			_node = new Node();
			Node* node = _node;

			for (int i = 1; i < count; i++, node = node->Next) {
				node->Next = new Node();
			}
		}

		template <typename T>
		List<T>::~List()
		{
			for (Node* node = _node; node; ) {
				Node* next = node->Next;
				delete node;
				node = next;
			}
		}

		template <typename T>
		void List<T>::Add(const T& value)
		{
			if (!_node) {
				_node = new Node(value);
				_length = 1;
				return;
			}

			Node* it = _head.Back();
			for (; it->Next; it = it->Next);
			it->Next = new Node(value);
			_length++;
		}

		template <typename T>
		T& List<T>::Back()
		{
			if (!_length) {
				throw InvalidOperationException();
			}

			Node* it = _head.Back();
			for (; it->Next; it = it->Next);
			return it->Data;
		}

		template <typename T>
		const T& List<T>::Back() const
		{
			if (!_length) {
				throw InvalidOperationException();
			}

			Node* it = _head.Back();
			for (; it->Next; it = it->Next);
			return it->Data;
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
			for (Node* node = _node; node; node = node->Next) {
				if (node->Data == value) {
					return true;
				}
			}

			return false;
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
			// validate
			if (!_length) {
				throw InvalidOperationException();
			}

			return _node->Data;
		}

		template <typename T>
		const T& List<T>::Front() const
		{
			// validate
			if (!_length) {
				throw InvalidOperationException();
			}

			return _node->Data;
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
	}
}
