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

#ifndef LUPUS_IDICTIONARY_HPP
#define LUPUS_IDICTIONARY_HPP

#include "Pair.hpp"
#include "ICollection.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		class Vector;

		//! interface for dictionary types
		template <typename Key, typename Value>
		class IDictionary : public ICollection<Pair<Key, Value>>
		{
		public:
			virtual ~IDictionary() { }
			//! add a new key value pair
			virtual void Add(const Key&, const Value&) = 0;
			//! clear entire content
			virtual void Clear() = 0;
			//! check if dictionary contains given value
			virtual bool Contains(const Value&) const = 0;
			//! check if dictionary contains given key
			virtual bool ContainsKey(const Key&) const = 0;
			//! remove all entries equal to given value
			virtual bool Remove(const Value&) = 0;
			//! remove all entries equal to given key
			virtual bool RemoveKey(const Key&) = 0;
			//! check if dictionary is empty
			virtual bool IsEmpty() const = 0;
			//! get all keys from this dictionary
			Vector<Key> GetKeys() const = 0;
			//! get all values from this dictionary
			Vector<Value> GetValues() const = 0;
		};
	}
}

#endif
