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
#include "ISequence.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		SequenceIterator<T>::SequenceIterator(SequenceIterator<T>&& iterator)
		{
			Swap(iterator._sequence, nullptr);
			Swap(iterator._current, 0);
		}

		template <typename T>
		SequenceIterator<T>::SequenceIterator(const ISequence<T>& sequence) :
			_sequence(&sequence)
		{
		}

		template <typename T>
		SequenceIterator<T>::SequenceIterator(const ISequence<T>* sequence) :
			_sequence(sequence)
		{
			if (!sequence) {
				throw ArgumentNullException();
			}
		}

		template <typename T>
		SequenceIterator<T>::~SequenceIterator()
		{
		}

		template <typename T>
		void SequenceIterator<T>::First()
		{
			_current = 0;
		}

		template <typename T>
		void SequenceIterator<T>::Next()
		{
			_current++;
		}

		template <typename T>
		bool SequenceIterator<T>::IsDone() const
		{
			return (_current >= _sequence->Count());
		}

		template <typename T>
		const T& SequenceIterator<T>::CurrentItem() const
		{
			if (IsDone()) {
				throw IteratorOutOfBoundException();
			}

			return (_sequence->operator[](_current));
		}

		template <typename T>
		SequenceIterator<T>& SequenceIterator<T>::operator=(SequenceIterator<T>&& iterator)
		{
			Swap(iterator._sequence, _sequence);
			Swap(iterator._current, _current);
		}

		template <typename Key, typename Value>
		DictionaryIterator<Key, Value>::DictionaryIterator(const IDictionary<Key, Value>& dictionary) :
			_dictionary(&dictionary)
		{
		}

		template <typename Key, typename Value>
		DictionaryIterator<Key, Value>::DictionaryIterator(const IDictionary<Key, Value>* dictionary) :
			_dictionary(dictionary)
		{
			if (!sequence) {
				throw ArgumentNullException();
			}
		}

		template <typename Key, typename Value>
		DictionaryIterator<Key, Value>::~DictionaryIterator()
		{
			throw NotImplementedException();
		}

		template <typename Key, typename Value>
		void DictionaryIterator<Key, Value>::First()
		{
			throw NotImplementedException();
		}

		template <typename Key, typename Value>
		void DictionaryIterator<Key, Value>::Next()
		{
			throw NotImplementedException();
		}

		template <typename Key, typename Value>
		bool DictionaryIterator<Key, Value>::IsDone() const
		{
			throw NotImplementedException();
		}

		template <typename Key, typename Value>
		const Pair<Key, Value>& DictionaryIterator<Key, Value>::CurrentItem() const
		{
			throw NotImplementedException();
		}
	}
}
