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
		SequenceIterator<T>::SequenceIterator(const ISequence<T>& sequence) :
			_sequence(&sequence)
		{
		}
		template <typename T>
		SequenceIterator<T>::SequenceIterator(const ISequence<T>* sequence) :
			_sequence(sequence)
		{
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
			return (_current >= _sequence->Length);
		}

		template <typename T>
		Char& SequenceIterator::CurrentItem()
		{
			if (IsDone()) {
				throw IteratorOutOfBoundException();
			}

			return _sequence->operator[](_current);
		}

		template <typename T>
		const Char& SequenceIterator::CurrentItem() const
		{
			if (IsDone()) {
				throw IteratorOutOfBoundException();
			}

			return _sequence->operator[](_current);
		}
	}
}
