/* Copyright � 2014 David Wolf <d.wolf@live.at>
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

#ifndef LUPUS_VECTOR_HPP
#define LUPUS_VECTOR_HPP

#include "Object.hpp"
#include "Vector.hpp"
#include "ISequence.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		class List;

		template <typename T>
		class ListIterator : public Iterator<T>
		{
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
		class List : public Object, public ISequence<T>
		{
			friend class ListIterator<T>;

			class Node
			{
				T _data = T();
				Node* _next = nullptr;
				Node* _prev = nullptr;
			public:
				PropertyAccess<T> Data = PropertyAccess<T>(_data);
				PropertyAccess<Node*> Next = PropertyAccess<Node*>(_next);
				PropertyAccess<Node*> Previous = PropertyAccess<Node*>(_prev);
			};
			
			Node* _head[32];

			Node _first;
			Node _last;
			int _length;
		public:
			//! Return list length length
			PropertyReader<int> Length = PropertyReader<int>(_length);
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
			virtual Iterator<T> GetIterator() const override;
			virtual void Clear() override;
			virtual bool Contains(const T&) const override;
			virtual void CopyTo(ISequence<T>&, int) const override;
			virtual void CopyTo(int, ISequence<T>&, int, int) const override;
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
		};
	}
}

#include "List.inl"

#endif