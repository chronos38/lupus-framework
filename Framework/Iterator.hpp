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

#ifndef LUPUS_ITERATOR_HPP
#define LUPUS_ITERATOR_HPP

#include "Pair.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		class ISequence;
		template <typename Key, typename Value>
		class IDictionary;
		template <typename Key, typename Value>
		class Pair;

		template <typename T>
		class Iterator
		{
		public:
			virtual ~Iterator(){}
			virtual void First() = 0;
			virtual void Next() = 0;
			virtual bool IsDone() const = 0;
			virtual const T& CurrentItem() const = 0;
		};

		template <typename T>
		class SequenceIterator : public Object, public Iterator<T>
		{
			const ISequence<T>* _sequence = nullptr;
			int _current = 0;
		public:
			SequenceIterator(const ISequence<T>&);
			SequenceIterator(const ISequence<T>*);
			virtual ~SequenceIterator();
			virtual void First() override;
			virtual void Next() override;
			virtual bool IsDone() const override;
			virtual const T& CurrentItem() const override;
			SequenceIterator<T>& operator=(const SequenceIterator<T>&) = default;
		};

		template <typename Key, typename Value>
		class DictionaryIterator : public Object, public Iterator<Pair<Key, Value>>
		{
			const IDictionary<Key, Value>* _dictionary = nullptr;
		public:
			DictionaryIterator(const IDictionary<Key, Value>&);
			DictionaryIterator(const IDictionary<Key, Value>*);
			virtual ~DictionaryIterator();
			virtual void First() override;
			virtual void Next() override;
			virtual bool IsDone() const override;
			virtual const Pair<Key, Value>& CurrentItem() const override;
			DictionaryIterator<Key, Value>& operator=(const DictionaryIterator<Key, Value>&) = default;
		};
	}
}

#include "Iterator.inl"

#endif
