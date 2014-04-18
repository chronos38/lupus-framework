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
#include "ISortStrategy.hpp"

namespace Lupus {
	namespace System {
		//! simple vector class for easy and fast access
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
			//! Return vector array
			PropertyReader<T*> Data = PropertyReader<T*>(_data);
			//! create default instance
			Vector();
			//! copy from given instance
			Vector(const Vector<T>&);
			//! move from given instance
			Vector(Vector<T>&&);
			//! copy from given collection
			Vector(const ICollection<T>&);
			//! read from given initializer list
			Vector(const std::initializer_list<T>&);
			//! define allocation size for internal array
			Vector(int);
			//! free allocated resources
			virtual ~Vector();
			//! \sa ISwappable::Swap
			virtual void Swap(Pointer<Iterator<T>>& lhs, Pointer<Iterator<T>>& rhs) override;
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
			//! \sa ICollection::CopyTo
			virtual void CopyTo(Vector<T>&, int) const override;
			//! \sa ICollection::CopyTo
			virtual void CopyTo(int, Vector<T>&, int, int) const override;
			//! \sa ICollection::Count
			virtual int Count() const override;
			//! \sa ISequence::Front
			virtual T& Front() override;
			//! \sa ISequence::Front
			virtual const T& Front() const override;
			//! \sa ISequence::Insert
			virtual void Insert(int, const T&) override;
			//! \sa ISequence::IsEmpty
			virtual bool IsEmpty() const override;
			//! \sa ISequence::RemoveAt
			virtual void RemoveAt(int) override;
			//! \sa ISequence::Resize
			virtual void Resize(int) override;
			//! shrink capacity to fit length
			virtual void ShrinkToFit() final;
			//! get value at given index
			T& operator[](int);
			//! get value at given index
			const T& operator[](int) const;
			//! assign given vector
			Vector<T>& operator=(const Vector<T>&);
			//! swap vectors
			Vector<T>& operator=(Vector<T>&&);
			//! assign given collection
			Vector<T>& operator=(const ICollection<T>&);
		private:
			class VectorIterator : public Iterator<T>
			{
				friend class Vector<T>;
				const Vector<T>* _vector = nullptr;
				int _current = 0;
			public:
				VectorIterator() = delete;
				VectorIterator(const VectorIterator&) = delete;
				VectorIterator(VectorIterator&&) = delete;
				VectorIterator(const Vector<T>*);
				virtual ~VectorIterator();
				virtual void First() override;
				virtual void Next() override;
				virtual bool IsDone() const override;
				virtual const T& CurrentItem() const override;
				VectorIterator& operator=(const VectorIterator&) = delete;
				VectorIterator& operator=(VectorIterator&&) = delete;
			};
		};
	}
}

#include "Vector.inl"

#endif
