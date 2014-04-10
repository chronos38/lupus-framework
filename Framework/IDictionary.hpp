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

#ifndef LUPUS_IDICTIONARY_HPP
#define LUPUS_IDICTIONARY_HPP

#include "Pair.hpp"
#include "Iterator.hpp"
#include "ICollection.hpp"

namespace Lupus {
	namespace System {
		template <typename T>
		class Vector;

		template <typename Key, typename Value>
		class IDictionary : public ICollection<Pair<Key, Value>>
		{
		public:
			virtual ~IDictionary() { }
			virtual void Add(const Key&, const Value&) = 0;
			virtual void Clear() = 0;
			virtual bool Contains(const Value&) const = 0;
			virtual bool ContainsKey(const Key&) const = 0;
			virtual void CopyTo(ISequence<Value>&, int);
			virtual s32 Count() = 0;
			virtual bool Remove(const Value&) = 0;
			virtual bool RemoveKey(const Key&) = 0;
			virtual bool IsEmpty() const = 0;
			Vector<Key> GetKeys();
			Vector<Value> GetValues();
		};
	}
}

#endif
