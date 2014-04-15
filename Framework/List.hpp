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

#ifndef LUPUS_LIST_HPP
#define LUPUS_LIST_HPP

#include "Types.hpp"
#include "ISequence.hpp"
#include "ICopyable.hpp"
#include "Vector.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		class List;
		template <typename T>
		class ListIterator;

		template <typename T>
		class ListSortStrategy : public ICopyable<ListSortStrategy<T>>
		{
		public:
			virtual void Sort(List<T>& list) = 0;
		};

		template <typename T>
		class List : public Object, public ISequence<T>
		{
			friend class ListIterator<T>;
			friend class ListSortStrategy<T>;

			struct Node {
				Node() = default;
				Node(const Node&) = default;
				Node(Node&&);
				Node(const T&);
				~Node();
				T Data = T();
				Node* Next = nullptr;
			};
			
			//! first entry
			Node* _head = nullptr;
			//! last entry
			Node* _tail = nullptr;
			//! length of list
			int _length = 0;
			//! default sort algorithm
			static Pointer<ListSortStrategy<T>> _defaultStrategy;
			//! list sort algorithm
			Pointer<ListSortStrategy<T>> _strategy = _defaultStrategy->Copy();
		public:
			//! Return list length length
			PropertyReader<int> Length = PropertyReader<int>(_length);
			//! Set list sort algorithm
			PropertyWriter<Pointer<ListSortStrategy<T>>> ListSortAlgorithm = PropertyWriter<Pointer<ListSortStrategy<T>>>(_strategy);
			//! Set default sort algorithm
			static PropertyWriter<Pointer<ListSortStrategy<T>>> DefaultListSortAlgorithm;
			//! create empty list
			List();
			//! copy from existing list
			List(const List<T>&);
			//! swap content between lists
			List(List<T>&&);
			//! copy content from collection
			List(const ICollection<T>&);
			//! read from given initializer list
			List(const std::initializer_list<T>&);
			//! pre allocate memory
			List(int);
			//! free all allocated memory
			virtual ~List();
			//! \sa ISequence::Add
			virtual void Add(const T&) override;
			//! \sa ISequence::Back
			virtual T& Back() override;
			//! \sa ISequence::Back
			virtual const T& Back() const override;
			//! \sa Iterable::GetIterator
			virtual Pointer<Iterator<T>> GetIterator() const override;
			//! \sa ISequence::Clear
			virtual void Clear() override;
			//! \sa ISequence::Contains
			virtual bool Contains(const T&) const override;
			//! \sa ICollection::CopyTo(Vector<T>&, int)
			virtual void CopyTo(Vector<T>&, int) const override;
			//! \sa ICollection::CopyTo(int, Vector<T>&, int, int)
			virtual void CopyTo(int, Vector<T>&, int, int) const override;
			//! \sa ICollection::Count
			virtual int Count() const override;
			//! \sa ISequence::Front
			virtual T& Front() override;
			//! \sa ISequence::Front
			virtual const T& Front() const override;
			//! \sa ISequence::Insert
			virtual void Insert(int, const T&) override;
			//! \sa ISequence::IsEmtpy
			virtual bool IsEmpty() const override;
			//! \sa ISequence::RemoveAt
			virtual void RemoveAt(int) override;
			//! \sa ISequence::Resize
			virtual void Resize(int) override;
			//! sorts list entries
			void Sort();
			/**
			 * gets item at given index.
			 *
			 * \b Complexity: \a O(n)
			 *
			 * \b Exceptions:
			 * - ArgumentOutOfRangeException
			 *
			 * @param index search for entry at given index
			 * @return entry at given index
			 */
			T& operator[](int index);
			/**
			 * gets item at given index.
			 *
			 * \b Complexity: \a O(n)
			 *
			 * \b Exceptions:
			 * - ArgumentOutOfRangeException
			 *
			 * @param index search for entry at given index
			 * @return entry at given index
			 */
			const T& operator[](int index) const;
			//! assign given list
			List<T>& operator=(const List<T>&);
			//! swap lists
			List<T>& operator=(List<T>&&);
			//! assign given collection
			List<T>& operator=(const ICollection<T>&);
		private:
		};

		template <typename T>
		class ListIterator : public Iterator<T>
		{
			const List<T>* _list = nullptr;
			typename List<T>::Node* _current = nullptr;
		public:
			ListIterator() = delete;
			ListIterator(const ListIterator<T>&) = delete;
			ListIterator(ListIterator<T>&&);
			ListIterator(const List<T>&);
			ListIterator(const List<T>*);
			virtual ~ListIterator();
			virtual void First() override;
			virtual void Next() override;
			virtual bool IsDone() const override;
			virtual const T& CurrentItem() const override;
			ListIterator<T>& operator=(const ListIterator<T>&) = delete;
			ListIterator<T>& operator=(ListIterator<T>&&);
		};

		template <typename T>
		class ListQuickSort : public ListSortStrategy<T>
		{
		public:
			virtual Pointer<ListSortStrategy<T>> Copy() const override;
			virtual void Sort(List<T>& list) override;
		};
	}
}

#include "List.inl"

#endif
