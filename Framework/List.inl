/* Copyright © 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of LupusFramwork.
 *
 * LupusFramwork is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LupusFramwork is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LupusFramwork.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MergeSort.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		Pointer<ISortStrategy<T>> List<T>::_defaultStrategy = new MergeSort<T>();
		template <typename T>
		PropertyWriter<Pointer<ISortStrategy<T>>> List<T>::DefaultListSortAlgorithm =
			PropertyWriter<Pointer<ISortStrategy<T>>>(List<T>::_defaultStrategy);

		template <typename T>
		List<T>::List()
		{
		}

		template <typename T>
		List<T>::List(const List<T>& list)
		{
			// check argument
			if (list.Count() == 0) {
				return;
			}

			// variables
			Node* node = nullptr;

			// copy values
			foreach (item, list) {
				if (!node) {
					_head = _tail = node = new Node(item->CurrentItem());
					continue;
				}

				node->Next = new Node(item->CurrentItem());
				_tail = node = node->Next;
			}

			_length = list.Count();
		}

		template <typename T>
		List<T>::List(List<T>&& list)
		{
			Lupus::Swap(_head, list._head);
			Lupus::Swap(_tail, list._tail);
			Lupus::Swap(_length, list._length);
		}

		template <typename T>
		List<T>::List(const ICollection<T>& collection)
		{
			// check argument
			if (collection.Count() == 0) {
				return;
			}

			// variables
			Node* node = nullptr;

			// copy values
			foreach (item, collection) {
				if (!node) {
					_head = _tail = node = new Node(item->CurrentItem());
					continue;
				}

				node->Next = new Node(item->CurrentItem());
				_tail = node = node->Next;
			}

			_length = collection.Count();
		}

		template <typename T>
		List<T>::List(const std::initializer_list<T>& list)
		{
			// check argument
			if (list.size() == 0) {
				return;
			}

			// variables
			Node* node = nullptr;

			// copy values
			for (const T& item : list) {
				if (!node) {
					_head = _tail = node = new Node(item);
					continue;
				}

				node->Next = new Node(item);
				_tail = node = node->Next;
			}

			_length = static_cast<int>(list.size());
		}

		template <typename T>
		List<T>::List(int count)
		{
			// check arguments
			if (count < 0) {
				throw ArgumentOutOfRangeException("count must be positive or zero");
			} else if (count == 0) {
				return;
			}

			// variables
			Node* node = nullptr;

			// allocate memory
			for (int i = 0; i < count; i++) {
				if (!node) {
					_head = _tail = node = new Node();
					continue;
				}

				node->Next = new Node();
				_tail = node = node->Next;
			}

			_length = count;
		}

		template <typename T>
		List<T>::~List()
		{
			if (_head) {
				delete _head;
			}
		}

		template <typename T>
		void List<T>::Swap(Pointer<Iterator<T>>& lhs, Pointer<Iterator<T>>& rhs)
		{
			try {
				ListIterator& first = dynamic_cast<ListIterator&>(*lhs);
				ListIterator& second = dynamic_cast<ListIterator&>(*rhs);
				int counter = 0;

				if (this != first._list || this != second._list) {
					throw InvalidIteratorException();
				} else if (lhs->IsDone() || rhs->IsDone()) {
					throw IteratorOutOfBoundException();
				}

				for (Node* node = _head, *prev = nullptr; node && counter < 2; prev = node, node = node->Next) {
					if (node == first._current) {
						if (prev) prev->Next = second._current;
						counter++;
					}

					if (node == second._current) {
						if (prev) prev->Next = first._current;
						counter++;
					}
				}

				Lupus::Swap(first._current, second._current);
				Lupus::Swap(first._current->Next, second._current->Next);
			} catch (...) {
				throw InvalidIteratorException();
			}
		}

		template <typename T>
		void List<T>::Add(const T& value)
		{
			if (!_head) {
				_head = _tail = new Node(value);
				return;
			}

			_tail->Next = new Node(value);
			_tail = _tail->Next;
			_length += 1;
		}

		template <typename T>
		T& List<T>::Back()
		{
			if (!_tail) {
				throw NullPointerException();
			}

			return _tail->Data;
		}

		template <typename T>
		const T& List<T>::Back() const
		{
			if (!_tail) {
				throw NullPointerException();
			}

			return _tail->Data;
		}

		template <typename T>
		Pointer<Iterator<T>> List<T>::GetIterator() const
		{
			return new ListIterator(this);
		}

		template <typename T>
		void List<T>::Clear()
		{
			if (_head) {
				delete _head;
				_head = _tail = nullptr;
				_length = 0;
			}
		}

		template <typename T>
		bool List<T>::Contains(const T& value) const
		{
			for (Node* node = _head; node; node = node->Next) {
				if (node->Data == value) {
					return true;
				}
			}

			return false;
		}

		template <typename T>
		void List<T>::CopyTo(Vector<T>& vector, int startIndex) const
		{
			CopyTo(0, vector, startIndex, _length);
		}

		template <typename T>
		void List<T>::CopyTo(int sourceIndex, Vector<T>& vector, int destinationIndex, int count) const
		{
			// check argument
			if ((sourceIndex + count) > _length) {
				throw ArgumentOutOfRangeException("sourceIndex plus count exceedes vector length");
			} else if (sourceIndex < 0) {
				throw ArgumentOutOfRangeException("sourceIndex must be greater than zero");
			} else if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			} else if ((destinationIndex + count) > vector.Length) {
				throw ArgumentOutOfRangeException("destinationIndex plus count exceedes vector length");
			} else if (destinationIndex < 0) {
				throw ArgumentOutOfRangeException("destinationIndex must be greater than zero");
			}

			// variables
			int limit = sourceIndex + count;
			int i = 0;
			int j = destinationIndex;

			// copy
			for (Node* node = _head; node && i < limit; node = node->Next, i++) {
				if (i < sourceIndex) {
					continue;
				}

				vector[j] = node->Data;
			}
		}

		template <typename T>
		int List<T>::Count() const
		{
			return _length;
		}

		template <typename T>
		T& List<T>::Front()
		{
			if (!_head) {
				throw NullPointerException();
			}

			return _head->Data;
		}

		template <typename T>
		const T& List<T>::Front() const
		{
			if (!_head) {
				throw NullPointerException();
			}

			return _head->Data;
		}

		template <typename T>
		void List<T>::Insert(int index, const T& item)
		{
			// check arguments
			if (index > _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			// increment length
			_length += 1;

			// check if insertion ist at the beginning or end
			if (index == 0) {
				Node* node = _head;
				_head = new Node(item);
				_head->Next = node;
				return;
			} else if (index == _length) {
				_tail->Next = new Node(item);
				_tail = _tail->Next;
				return;
			}

			// variables
			int i = 1;

			// insert
			for (Node* node = _head->Next, *prev = _head; node; prev = node, node = node->Next, i++) {
				if (i == index) {
					prev->Next = new Node(item);
					prev->Next->Next = node;
					return;
				}
			}
		}

		template <typename T>
		bool List<T>::IsEmpty() const
		{
			return (_length == 0);
		}

		template <typename T>
		void List<T>::RemoveAt(int index)
		{
			// check arguments
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than or equal to zero");
			}

			// decrement length
			_length -= 1;

			// check if insertion ist at the beginning or end
			if (index == 0) {
				Node* node = _head->Next;
				delete _head;
				_head = node;
				return;
			}

			// variables
			int i = 1;

			for (Node* node = _head->Next, *prev = _head; node; prev = node, node = node->Next, i++) {
				if (i == index) {
					prev->Next = node->Next;
					delete node;
					return;
				}
			}
		}

		template <typename T>
		void List<T>::Resize(int count)
		{
			// check argument
			if (count < 0) {
				throw ArgumentOutOfRangeException("count should be a positive number");
			}

			_length = count;

			// check cases for count
			if (count == 0) {
				delete _head;
				_head = _tail = nullptr;
			} else if (count > _length) {
				for (int i = _length; i < count; i++) {
					_tail->Next = new Node();
					_tail = _tail->Next;
				}
			} else if (count < _length) {
				int i = 1;

				for (Node* node = _head; node; node = node->Next, i++) {
					if (i == count) {
						delete node->Next;
						_tail = node;
						return;
					}
				}
			}
		}

		template <typename T>
		void List<T>::Sort()
		{
			_strategy->Sort(*this);
		}

		template <typename T>
		T& List<T>::operator[](int index)
		{
			// check arguments
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			// check if head or tail
			if (index == 0) {
				return _head->Data;
			} else if (index == _length - 1) {
				return _tail->Data;
			}

			// variables
			int i = 1;
			Node* node = nullptr;

			for (node = _head->Next; node; node = node->Next) {
				if (index == i) {
					break;
				}
			}

			return node->Data;
		}

		template <typename T>
		const T& List<T>::operator[](int index) const
		{
			// check arguments
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			// check if head or tail
			if (index == 0) {
				return _head->Data;
			} else if (index == _length - 1) {
				return _tail->Data;
			}

			// variables
			int i = 1;
			Node* node = nullptr;

			for (node = _head->Next; node; node = node->Next) {
				if (index == i) {
					break;
				}
			}

			return node->Data;
		}

		template <typename T>
		List<T>& List<T>::operator=(const List<T>& list)
		{
			// check argument
			if (list.Length == 0) {
				delete _head;
				_head = _tail = nullptr;
				_length = 0;
				return (*this);
			}

			// variables
			Node* node = nullptr;

			// copy values
			foreach (item, list) {
				if (!node) {
					_head = _tail = node = new Node(item->CurrentItem());
					continue;
				}

				node->Next = new Node(item->CurrentItem());
				_tail = node = node->Next;
			}

			_length = list._length;
			return (*this);
		}

		template <typename T>
		List<T>& List<T>::operator=(List<T>&& list)
		{
			Lupus::Swap(_head, list._head);
			Lupus::Swap(_tail, list._tail);
			Lupus::Swap(_length, list._length);
			return (*this);
		}

		template <typename T>
		List<T>& List<T>::operator=(const ICollection<T>& collection)
		{
			// check argument
			if (collection.Count() == 0) {
				delete _head;
				_head = _tail = nullptr;
				_length = 0;
				return (*this);
			}

			// variables
			Node* node = nullptr;

			// copy values
			foreach (item, collection) {
				if (!node) {
					_head = _tail = node = new Node(item->CurrentItem());
					continue;
				}

				node->Next = new Node(item->CurrentItem());
				_tail = node = node->Next;
			}

			_length = collection.Count();
			return (*this);
		}

		template <typename T>
		List<T>::Node::Node(Node&& node)
		{
			Lupus::Swap(Data, node.Data);
			Lupus::Swap(Next, node.Next);
		}

		template <typename T>
		List<T>::Node::Node(const T& data)
		{
			Data = data;
		}

		template <typename T>
		List<T>::Node::~Node()
		{
			if (Next) {
				delete Next;
			}
		}

		template <typename T>
		List<T>::ListIterator::ListIterator(const List<T>* list) :
			_list(list)
		{
			if (!list) {
				throw ArgumentNullException();
			}

			_current = _list->_head;
		}

		template <typename T>
		List<T>::ListIterator::~ListIterator()
		{
		}

		template <typename T>
		void List<T>::ListIterator::First()
		{
			_current = _list->_head;
		}

		template <typename T>
		void List<T>::ListIterator::Next()
		{
			if (_current) {
				_current = _current->Next;
			}
		}

		template <typename T>
		bool List<T>::ListIterator::IsDone() const
		{
			return (_current == nullptr);
		}

		template <typename T>
		const T& List<T>::ListIterator::CurrentItem() const
		{
			if (IsDone()) {
				throw IteratorOutOfBoundException();
			}

			return (_current->Data);
		}
	}
}
