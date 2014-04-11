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

#ifndef LUPUS_LIST_HPP
#define LUPUS_LIST_HPP

#include "Types.hpp"
#include "ISequence.hpp"
#include "ICopyable.hpp"

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

			class Node
			{
				T _data = T();
				Node* _next = nullptr;
			public:
				Node() = default;
				Node(const Node&) = default;
				Node(Node&&) = default;
				Node(const T&);
				PropertyAccess<T> Data = PropertyAccess<T>(_data);
				PropertyAccess<Node*> Next = PropertyAccess<Node*>(_next);
			};
			
			// first entry
			Node* _node = nullptr;
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
			PropertyWriter<Pointer<ListSortStrategy<T>>> ListSortAlgorithm = PropertyWriter<Pointer<TextSearchStrategy>>(_strategy);
			//! Set default sort algorithm
			static PropertyWriter<Pointer<ListSortStrategy<T>>> DefaultListSortAlgorithm;
			List();
			List(const List<T>&);
			List(List<T>&&);
			List(const ISequence<T>&);
			List(const std::initializer_list<T>&);
			List(int);
			virtual ~List();
			virtual void Add(const T&) override;
			virtual T& Back() override;
			virtual const T& Back() const override;
			virtual Pointer<Iterator<T>> GetIterator() const override;
			virtual void Clear() override;
			virtual bool Contains(const T&) const override;
			virtual void CopyTo(Vector<T>&, int) const override;
			virtual void CopyTo(int, Vector<T>&, int, int) const override;
			virtual int Count() const override;
			virtual T& Front() override;
			virtual const T& Front() const override;
			virtual void Insert(int, const T&) override;
			virtual bool IsEmpty() const override;
			virtual bool RemoveAt(int) override;
			virtual void Resize(int) override;
			virtual T& operator[](int) override;
			virtual const T& operator[](int) const override;
			List<T>& operator=(const List<T>&);
			List<T>& operator=(List<T>&&);
			List<T>& operator=(const ISequence<T>&);
		private:
		};

		template <typename T>
		class ListIterator : public Iterator<T>
		{
			List<T>* _list = nullptr;
			List<T>::Node* _current = nullptr;
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
