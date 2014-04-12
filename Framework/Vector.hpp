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

#ifndef LUPUS_VECTOR_HPP
#define LUPUS_VECTOR_HPP

#include "Types.hpp"
#include "ISequence.hpp"
#include "Iterator.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		class VectorIterator;

		template <typename T>
		class Vector : public Object, public ISequence<T>
		{
			//! native array
			T* _data;
			//! array length
			int _length;
			//! array capacity
			int _capacity;
		public:
			//! Return vector length
			PropertyReader<int> Length = PropertyReader<int>(_length);
			//! Return vector capacity
			PropertyReader<int> Capacity = PropertyReader<int>(_capacity);
			//! Return vector string
			PropertyReader<T*> Data = PropertyReader<T*>(_data);
			Vector();
			Vector(const Vector<T>&);
			Vector(Vector<T>&&);
			Vector(const ISequence<T>&);
			Vector(const std::initializer_list<T>&);
			Vector(int);
			virtual ~Vector();
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
			virtual void ShrinkToFit() final;
			T& operator[](int);
			const T& operator[](int) const;
			Vector<T>& operator=(const Vector<T>&);
			Vector<T>& operator=(Vector<T>&&);
			Vector<T>& operator=(const ISequence<T>&);
		};

		template <typename T>
		class VectorIterator : public Object, public Iterator<T>
		{
			const Vector<T>* _sequence = nullptr;
			int _current = 0;
		public:
			VectorIterator() = delete;
			VectorIterator(const VectorIterator<T>&) = delete;
			VectorIterator(VectorIterator<T>&&);
			VectorIterator(const Vector<T>&);
			VectorIterator(const Vector<T>*);
			virtual ~VectorIterator();
			virtual void First() override;
			virtual void Next() override;
			virtual bool IsDone() const override;
			virtual const T& CurrentItem() const override;
			VectorIterator<T>& operator=(const VectorIterator<T>&) = delete;
			VectorIterator<T>& operator=(VectorIterator<T>&&);
		};
	}
}

#include "Vector.inl"

#endif
