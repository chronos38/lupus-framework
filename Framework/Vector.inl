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

namespace Lupus {
	namespace System {
		template <typename T>
		Vector<T>::Vector() :
			_data(new T[DEFAULT_ARRAY_SIZE]),
			_length(0),
			_capacity(DEFAULT_ARRAY_SIZE)
		{
		}
		
		template <typename T>
		Vector<T>::Vector(const Vector<T>& vector)
		{
			if (vector._length == 0) {
				Vector<T>::Vector();
				return;
			}

			_data = new T[vector._length];
			_length = _capacity = vector._length;

			for (int i = _length - 1; i >= 0; i--) {
				_data[i] = vector[i];
			}
		}

		template <typename T>
		Vector<T>::Vector(Vector<T>&& vector) :
			Vector()
		{
			Swap(_data, vector._data);
			Swap(_length, vector._length);
			Swap(_capacity, vector._capacity);
		}
		
		template <typename T>
		Vector<T>::Vector(const ICollection<T>& collection)
		{
			if (collection.Count() == 0) {
				Vector<T>::Vector();
				return;
			}

			int i = 0;
			_data = new T[collection.Count()];
			_capacity = _length = collection.Count();

			foreach (item, collection) {
				_data[i++] = item->CurrentItem();
			}
		}

		template <typename T>
		Vector<T>::Vector(const std::initializer_list<T>& list) :
			_data(new T[list.size()]),
			_length((int)list.size()),
			_capacity((int)list.size())
		{
			auto it = list.begin();
			int i = 0;

			for (const T& item : list) {
				_data[i++] = item;
			}
		}

		template <typename T>
		Vector<T>::Vector(int count)
		{
			if (count <= 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			}

			_data = new T[count];
			_length = _capacity = count;
		}

		template <typename T>
		Vector<T>::~Vector()
		{
			delete[] _data;
		}

		template <typename T>
		void Vector<T>::Add(const T& item)
		{
			if (_length < _capacity) {
				_data[_length++] = item;
			} else {
				T* buffer = new T[_capacity + 1];

				for (int i = 0; i < _length; i++) {
					buffer[i] = _data[i];
				}

				buffer[_length++] = item;
			}
		}

		template <typename T>
		T& Vector<T>::Back()
		{
			// validate
			if (_length <= 0) {
				throw InvalidOperationException();
			}

			return _data[_length - 1];
		}

		template <typename T>
		const T& Vector<T>::Back() const
		{
			// validate
			if (_length <= 0) {
				throw InvalidOperationException();
			}

			return _data[_length - 1];
		}

		template <typename T>
		Pointer<Iterator<T>> Vector<T>::GetIterator() const
		{
			return new VectorIterator(this);
		}

		template <typename T>
		void Vector<T>::Clear()
		{
			_length = 0;
		}

		template <typename T>
		bool Vector<T>::Contains(const T& item) const
		{
			for (int i = _length - 1; i >= 0; i--) {
				if (_data[i] == item) {
					return true;
				}
			}

			return false;
		}

		template <typename T>
		void Vector<T>::CopyTo(Vector<T>& vector, int startIndex) const
		{
			CopyTo(0, vector, startIndex, _length);
		}

		template <typename T>
		void Vector<T>::CopyTo(int sourceIndex, Vector<T>& vector, int destinationIndex, int count) const
		{
			// check argument
			if ((sourceIndex + count) > _length) {
				throw ArgumentOutOfRangeException("sourceIndex plus count exceedes vector length");
			} else if (sourceIndex < 0) {
				throw ArgumentOutOfRangeException("sourceIndex must be greater than zero");
			} else if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			} else if ((destinationIndex + count) > vector._length) {
				throw ArgumentOutOfRangeException("destinationIndex plus count exceedes vector length");
			} else if (destinationIndex < 0) {
				throw ArgumentOutOfRangeException("destinationIndex must be greater than zero");
			}

			// variables
			int limit = sourceIndex + count;

			// copy items
			for (int i = sourceIndex, j = destinationIndex; i < limit; i++, j++) {
				vector[j] = _data[i];
			}
		}

		template <typename T>
		int Vector<T>::Count() const
		{
			return _length;
		}

		template <typename T>
		T& Vector<T>::Front()
		{
			// validate
			if (_length <= 0) {
				throw InvalidOperationException();
			}

			return _data[0];
		}

		template <typename T>
		const T& Vector<T>::Front() const
		{
			// validate
			if (_length <= 0) {
				throw InvalidOperationException();
			}

			return _data[0];
		}

		template <typename T>
		void Vector<T>::Insert(int index, const T& item)
		{
			// check arguments
			if (index > _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			// variables
			Vector<T> vector(_length + 1);

			// set result
			CopyTo(0, vector, 0, index);
			vector[index] = item;
			CopyTo(index, vector, index + 1, _length - index);
			Swap(vector, *this);
		}

		template <typename T>
		bool Vector<T>::IsEmpty() const
		{
			return (_length == 0);
		}

		template <typename T>
		void Vector<T>::RemoveAt(int index)
		{
			// check arguments
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			for (int i = index; i < _length; i++) {
				_data[i] = _data[i + 1];
			}

			_length -= 1;
		}

		template <typename T>
		void Vector<T>::Resize(int count)
		{
			// check argument
			if (count <= 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			}

			// check if count is less than length
			if (count <= _length) {
				_length = count;
				return;
			}

			// variables
			T* swap = new T[count];

			for (int i = 0; i < count; i++) {
				if (i < _length) {
					swap[i] = _data[i];
				} else {
					swap[i] = T();
				}
			}

			// set new length
			_length = _capacity = count;
		}

		template <typename T>
		void Vector<T>::ShrinkToFit()
		{
			// check length
			if (_length <= 0) {
				delete _data;
				_data = new T[1];
				_length = 0;
				_capacity = 1;
				return;
			}

			T* swap = new T[_length];

			for (int i = 0; i < _length; i++) {
				swap[i] = _data[i];
			}

			_capacity = _length;
			Swap(swap, _data);
			delete swap;
		}

		template <typename T>
		T& Vector<T>::operator[](int index)
		{
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return (_data[index]);
		}

		template <typename T>
		const T& Vector<T>::operator[](int index) const
		{
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return (_data[index]);
		}

		template <typename T>
		Vector<T>& Vector<T>::operator=(const Vector<T>& vector)
		{
			if (vector._length > _capacity) {
				delete[] _data;
				_data = new T[vector._length];
				_capacity = vector._length;
			}

			for (int i = vector._length - 1; i >= 0; i--) {
				_data[i] = vector._data[i];
			}

			_length = vector._length;

			return (*this);
		}

		template <typename T>
		Vector<T>& Vector<T>::operator=(Vector<T>&& vector)
		{
			Swap(_data, vector._data);
			Swap(_length, vector._length);
			Swap(_capacity, vector._capacity);
			return (*this);
		}

		template <typename T>
		Vector<T>& Vector<T>::operator=(const ICollection<T>& collection)
		{
			// copy content
			if (_capacity < collection.Count()) {
				int i = 0;
				T* buffer = new T[collection.Count()];
				_capacity = _length = collection.Count();

				foreach (item, collection) {
					buffer[i++] = item->CurrentItem();
				}

				// swap content
				delete[] _data;
				_data = buffer;
			} else {
				int i = 0;

				foreach (item, collection) {
					_data[i++] = item->CurrentItem();
				}

				_length = collection.Count();
			}

			return (*this);
		}

		template <typename T>
		Vector<T>::VectorIterator::VectorIterator(const Vector<T>* vector) :
			_vector(vector)
		{
			if (!vector) {
				throw ArgumentNullException();
			}
		}

		template <typename T>
		Vector<T>::VectorIterator::~VectorIterator()
		{
		}

		template <typename T>
		void Vector<T>::VectorIterator::First()
		{
			_current = 0;
		}

		template <typename T>
		void Vector<T>::VectorIterator::Next()
		{
			_current++;
		}

		template <typename T>
		bool Vector<T>::VectorIterator::IsDone() const
		{
			return (_current >= _vector->Count());
		}

		template <typename T>
		const T& Vector<T>::VectorIterator::CurrentItem() const
		{
			if (IsDone()) {
				throw IteratorOutOfBoundException();
			}

			return (_vector->operator[](_current));
		}
	}
}
