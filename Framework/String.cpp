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

#include "String.hpp"
#include "ISequence.hpp"
#include "Iterator.hpp"
#include "Exception.hpp"
#include <cstring>

namespace Lupus {
	namespace System {
		String::String() :
			Object(),
			_data(new _lchar[1]),
			_length(0),
			_capacity(0)
		{
			_data[0] = 0;
		}

		String::String(const Char* source) :
			Object()
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables
			int length = GetLength(source);

			// in case the string is empty, apply it now
			if (!length) {
				*this = String();
				return;
			}

			// set values
			_data = new _lchar[length + 1];

			// set internal buffer
			for (int i = 0; i < length; i++) {
				_data[i] = source[i].Value();
			}

			_data[length] = 0;
			_length = _capacity = length;
		}

		String::String(const Char* source, int startIndex, int count) :
			Object()
		{
			// check arguments
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			} else if (count <= 0) {
				throw ArgumentOutOfRangeException("length must be greater than zero");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex is less than zero");
			}

			// variables
			int sourceLength = GetLength(source);

			// in case the string is empty, apply it now
			if (!sourceLength) {
				*this = String();
				return;
			}

			// check for errors
			if ((startIndex + count) > sourceLength) {
				throw ArgumentOutOfRangeException("length exceeds actual string length");
			}

			// create buffer
			_data = new _lchar[count + 1];

			// set internal buffer
			for (int i = 0; i < count; i++) {
				_data[i] = source[i + startIndex].Value();
			}

			// terminate with zero and free not needed memory
			_data[count] = 0;
			_length = _capacity = count;
		}

		String::String(const String& string) :
			Object(),
			_data(new wchar_t[string.Length + 1]),
			_length(string.Length),
			_capacity(string.Length)
		{
			_lmemcpy(_data, string.Data, _length);
			_data[_length] = 0;
		}

		String::String(String&& string) :
			String()
		{
			// variables
			_lchar* swapData = _data;
			int swapLength = _length;
			int swapCapacity = _capacity;

			// swap memory
			_data = string._data;
			_length = string._length;
			_capacity = string._capacity;

			string._data = swapData;
			string._length = swapLength;
			string._capacity = swapCapacity;
		}

		String::~String()
		{
			if (_data) {
				delete[] _data;
			}
		}

		String& String::Append(const String& string)
		{
			return operator+=(string);
		}

		String& String::Append(const Char& ch)
		{
			return operator+=(ch);
		}

		int String::Compare(const String& string, CaseSensitivity sensitivity) const
		{
			// check length
			if (_length != string.Length) {
				return (_length - string.Length);
			}

			// variables
			const _lchar* data = string.Data;

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = 0; i < _length; i++) {
					if (_data[i] != data[i]) {
						return (_data[i] - data[i]);
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = 0; i < _length; i++) {
					if (_ltolower(_data[i]) != _ltolower(data[i])) {
						return (_data[i] - data[i]);
					}
				}
				break;
			}

			return 0;
		}

		bool String::Contains(const String& string, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (string == "") {
				return true;
			} else if (_length < string.Length) {
				return false;
			} else if (_length == string.Length) {
				return (Compare(string, sensitivity) == 0);
			}

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return (KnuthMorrisPratt(_data, _length, string.Data, string.Length) != -1);
			case CaseSensitivity::CaseInsensitive:
				return (KnuthMorrisPrattInsensitive(_data, _length, string.Data, string.Length) != -1);
			}

			return false;
		}

		void String::CopyTo(int sourceIndex, ISequence<Char>& sequence, int destinationIndex, int count) const
		{
			// check argument
			if ((sourceIndex + count) > _length) {
				throw ArgumentOutOfRangeException("sourceIndex plus count exceedes string length");
			} else if (sourceIndex < 0) {
				throw ArgumentOutOfRangeException("sourceIndex must be greater than zero");
			} else if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			}

			// variables
			int limit = sourceIndex + count;

			// copy values
			for (int i = sourceIndex, j = destinationIndex; i < limit; i++, j++) {
				sequence[j] = _data[i];
			}
		}

		int String::IndexOf(const Char& ch, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= _length) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// variables
			Char lower = ch.ToLower();

			// comput result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = startIndex; i < _length; i++) {
					if (_data[i] == ch) {
						return i;
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = startIndex; i < _length; i++) {
					if (_ltolower(_data[i]) == lower) {
						return i;
					}
				}
				break;
			}

			return -1;
		}

		int String::IndexOf(const String& string, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= _length) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return KnuthMorrisPratt(_data + startIndex, _length - startIndex, string.Data, string.Length);
			case CaseSensitivity::CaseInsensitive:
				return KnuthMorrisPrattInsensitive(_data + startIndex, _length - startIndex, string.Data, string.Length);
			}

			return -1;
		}

		int String::IndexOfAny(const ISequence<Char>& sequence, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= _length) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			} else if (sequence.IsEmpty()) {
				return -1;
			}

			// variables
			auto iterator = sequence.Begin();

			// comput result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = startIndex; i < _length; i++) {
					_lchar& ch = _data[i];

					while (!iterator.IsDone()) {
						if (ch == iterator.CurrentItem()) {
							return i;
						}
					}

					iterator.First();
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = startIndex; i < _length; i++) {
					_lchar ch = _ltolower(_data[i]);

					while (!iterator.IsDone()) {
						if (ch == iterator.CurrentItem()) {
							return i;
						}
					}

					iterator.First();
				}
				break;
			}

			return -1;
		}

		int String::LastIndexOf(const Char& ch, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if ((_length - startIndex) < 0) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// variables
			Char lower = ch.ToLower();

			// comput result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = (_length - startIndex); i >= 0; i--) {
					if (_data[i] == ch) {
						return i;
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = (_length - startIndex); i >= 0; i--) {
					if (_ltolower(_data[i]) == lower) {
						return i;
					}
				}
				break;
			}

			return -1;
		}

		int String::LastIndexOf(const String& string, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= _length) {
				throw ArgumentNullException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return KnuthMorrisPrattLast(_data + startIndex, _length - startIndex, string.Data, string.Length);
			case CaseSensitivity::CaseInsensitive:
				return KnuthMorrisPrattInsensitiveLast(_data + startIndex, _length - startIndex, string.Data, string.Length);
			}

			return -1;
		}

		int String::LastIndexOfAny(const ISequence<Char>& sequence, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= _length) {
				throw ArgumentNullException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			} else if (sequence.IsEmpty()) {
				return -1;
			}

			throw NotImplementedException();
		}

		String& String::Remove(int startIndex)
		{
			// check argument
			if (startIndex >= _length) {
				throw ArgumentOutOfRangeException("startIndex exceedes string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// set range to zero
			_lmemset(_data + startIndex, 0, (_length - startIndex));

			// update length
			_length = startIndex;

			return (*this);
		}

		String& String::Remove(int startIndex, int count)
		{
			// check argument
			if ((startIndex + count) > _length) {
				throw ArgumentOutOfRangeException("startIndex plus count exceedes string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			} else if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			}

			// variables
			int length = _length - (startIndex + count);

			// set range to zero
			_lmemmove(_data + startIndex, _data + (startIndex + count), length);

			// update length
			_length -= count;

			return (*this);
		}

		String& String::Replace(const Char& before, const Char& after, CaseSensitivity sensitivity)
		{
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = 0; i < _length; i++) {
					if (_data[i] == before) {
						_data[i] = after.Value();
					}
				}
			case CaseSensitivity::CaseInsensitive:
				for (int i = 0; i < _length; i++) {
					if (_ltolower(_data[i]) == before.ToLower()) {
						_data[i] = after.Value();
					}
				}
			}

			return (*this);
		}

		String& String::Replace(const String& before, const String& after, CaseSensitivity sensitivity)
		{
			throw NotImplementedException();
		}
		
		/*
		Vector<String> String::Split(const Vector<Char>&, StringSplitOptions)
		{
		}

		Vector<String> String::Split(const Vector<Char>&, int, StringSplitOptions)
		{
		}

		Vector<String> String::Split(const String&, StringSplitOptions)
		{
		}

		Vector<String> String::Split(const String&, int, StringSplitOptions)
		{
		}
		*/

		String String::Substring(int startIndex) const
		{
			if (startIndex >= _length) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than or equal to zero");
			}

			return String(_data + startIndex);
		}

		String String::Substring(int startIndex, int count) const
		{
			if ((startIndex + count) >= _length) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than or equal to zero");
			} else if (count <= 0) {
				throw ArgumentOutOfRangeException("length must be greater than zero");
			}

			return String(_data, startIndex, count);
		}

		String& String::ToLower()
		{
			// variables
			const _lchar* limit = _data + _length;

			// compute result
			for (_lchar* ch = _data; ch != limit; ch++) {
				(*ch) = _ltolower(*ch);
			}

			return (*this);
		}

		String& String::ToUpper()
		{
			// variables
			const _lchar* limit = _data + _length;

			// compute result
			for (_lchar* ch = _data; ch != limit; ch++) {
				(*ch) = _ltoupper(*ch);
			}

			return (*this);
		}

		Char& String::operator[](int index)
		{
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return dynamic_cast<Char&>(_refChar = (_data + index));
		}

		const Char& String::operator[](int index) const
		{
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return dynamic_cast<const Char&>(_refChar = (_data + index));
		}

		String& String::operator=(const _lchar* string)
		{
			// check argument
			if (!string) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables 
			int length = _lstrlen(string);

			// check if capacity is big enough
			if (_capacity >= length) {
				// reset buffer
				_lmemset(_data, 0, _length);

				// set new values
				_lmemcpy(_data, string, length);
				_data[length] = 0;
				_length = length;
			} else {
				// reallocate buffer
				delete[] _data;
				_data = new _lchar[length + 1];

				// set new values
				_lmemcpy(_data, string, length);
				_data[length] = 0;
				_length = _capacity = length;
			}

			return (*this);
		}

		String& String::operator=(const String& string)
		{
			// variables 
			int length = string.Length;

			// check if capacity is big enough
			if (_capacity >= length) {
				// reset buffer
				_lmemset(_data, 0, _length);

				// set new values
				_lmemcpy(_data, string.Data, length);
				_data[length] = 0;
				_length = length;
			} else {
				// reallocate buffer
				delete[] _data;
				_data = new _lchar[length + 1];

				// set new values
				_lmemcpy(_data, string.Data, length);
				_data[length] = 0;
				_length = _capacity = length;
			}

			return (*this);
		}

		String& String::operator=(String&& string)
		{
			// delete[] current buffer
			delete[] _data;

			// move memory
			_data = string._data;
			_length = string._length;
			_capacity = string._capacity;

			// reset string
			string._data = new _lchar[1];
			string._length = 0;
			string._capacity = 0;

			return (*this);
		}

		String& String::operator=(const Char& ch)
		{
			if (_capacity > 1) {
				_lmemset(_data, 0, _length);
				_data[0] = ch.Value();
				_length = 1;
			} else {
				// reallocate buffer
				delete[] _data;
				_data = new _lchar[2];

				// set new values
				_data[0] = ch.Value();
				_data[1] = 0;
				_length = _capacity = 1;
			}

			return (*this);
		}

		String String::operator+(const String& string) const
		{
			// variables
			_lchar* buffer = new _lchar[_length + string.Length + 1];

			// copy new buffer
			_lmemcpy(buffer, _data, _length);
			_lmemcpy(buffer + _length, string.Data, string.Length);
			buffer[_length + string.Length] = 0;

			// set result and delete[] buffer
			return CreateWithExistingBuffer(buffer);
		}

		String& String::operator+=(const _lchar* str)
		{
			// variables
			int length = _lstrlen(str);

			// check if capacity is big enough
			if ((_capacity - _length) >= length) {
				_lmemcpy(_data + _length, str, length);
				_length += length;
			} else {
				// new buffer
				_lchar* buffer = new _lchar[_length + length + 1];

				// copy new buffer
				_lmemcpy(buffer, _data, _length);
				_lmemcpy(buffer + _length, str, length);
				buffer[_length + length] = 0;

				// set result and delete[] buffer
				delete[] _data;
				_data = buffer;
				_length += length;
				_capacity += length;
			}

			return (*this);
		}

		String& String::operator+=(const String& string)
		{
			// variables
			int length = string.Length;

			// check if capacity is big enough
			if ((_capacity - _length) >= length) {
				_lmemcpy(_data + _length, string.Data, length);
				_length += length;
			} else {
				// new buffer
				_lchar* buffer = new _lchar[_length + length + 1];
				
				// copy new buffer
				_lmemcpy(buffer, _data, _length);
				_lmemcpy(buffer + _length, string.Data, length);
				buffer[_length + length] = 0;

				// set result and delete[] buffer
				delete[] _data;
				_data = buffer;
				_length += length;
				_capacity += length;
			}

			return (*this);
		}

		String& String::operator+=(const Char& ch)
		{
			if ((_capacity - _length) >= 1) {
				_lmemset(_data, 0, _length);
				_data[0] = ch.Value();
				_length = 1;
			} else {
				// reallocate buffer
				_lchar* buffer = new _lchar[_length + 2];

				// copy new buffer
				_lmemcpy(buffer, _data, _length);
				buffer[_length] = ch.Value();
				buffer[_length + 1] = 0;

				// set result and delete[] buffer
				delete[] _data;
				_data = buffer;
				_length += 1;
				_capacity += 1;
			}

			return (*this);
		}

		bool String::operator==(const String& string) const
		{
			return (this->Compare(string) == 0);
		}

		bool String::operator!=(const String& string) const
		{
			return (this->Compare(string) != 0);
		}

		void String::Add(const Char& ch)
		{
			operator+=(ch);
		}

		Char& String::Back()
		{
			return operator[](_length - 1);
		}

		const Char& String::Back() const
		{
			return operator[](_length - 1);
		}

		SequenceIterator<Char> String::Begin() const
		{
			return SequenceIterator<Char>(this);
		}

		void String::Clear()
		{
			_lmemset(_data, 0, _length);
			_length = 0;
		}

		bool String::Contains(const Char& ch) const
		{
			return (_lmemchr(_data, ch.Value(), _length) != 0);
		}

		void String::CopyTo(ISequence<Char>& sequence, int startIndex) const
		{
			CopyTo(0, sequence, startIndex, _length);
		}

		int String::Count() const
		{
			return _length;
		}

		Char& String::Front()
		{
			return operator[](0);
		}

		const Char& String::Front() const
		{
			return operator[](0);
		}

		void String::Insert(int, const Char&)
		{
			throw NotImplementedException();
		}
		
		void String::Insert(const SequenceIterator<Char>&, const Char&)
		{
			throw NotImplementedException();
		}

		bool String::IsEmpty() const
		{
			return (_data[0] == 0);
		}

		bool String::RemoveAt(int index)
		{
			try {
				Remove(index);
			} catch (ArgumentOutOfRangeException&) {
				return false;
			}

			return true;
		}

		bool String::Remove(const SequenceIterator<Char>& iterator)
		{
			throw NotImplementedException();
		}

		void String::Resize(int count)
		{
			// check argument
			if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			}

			if (count <= _capacity) {
				_lmemset(_data, 0, count);

				// check for new length
				if (count < _length) {
					_length = count;
				}
			} else {
				// new buffer
				_lchar* buffer = new _lchar[count];
				_lmemset(buffer, 0, count);

				// copy old buffer delete it afterwards
				_lmemcpy(buffer, _data, _length);
				delete[] _data;

				// set internal buffer and length
				_data = buffer;
				_length = _capacity = count;
			}
		}

		String String::CreateWithExistingBuffer(_lchar* str)
		{
			// variables
			String string;

			// delete buffer
			delete[] string._data;

			// set values
			string._data = str;
			string._length = _lstrlen(str);
			string._capacity = string._length;

			// return result
			return string;
		}

		int String::GetLength(const Char* string)
		{
			int result = 0;

			for (const Char* ch = string; (*ch) != 0; ch++) {
				result++;
			}

			return result;
		}

		int String::KnuthMorrisPratt(const _lchar* text, int textLength, const _lchar* search, int searchLength)
		{
			// variables
			int* n = new int[searchLength + 1];
			int i = 0;
			int j = -1;

			// create prefix
			n[0] = -1;

			while (i < searchLength) {
				while (j >= 0 && search[i] != search[j]) {
					j = n[j];
				}
				i++;
				j++;
				n[i] = j;
			}

			// reset variables
			i = j = 0;

			// search
			while (i < textLength) {
				while (j >= 0 && text[i] != search[j]) {
					j = n[j];
				}
				i++;
				j++;

				if (j == searchLength) {
					delete[] n;
					return (i - j);
				}
			}

			delete[] n;
			return -1;
		}

		int String::KnuthMorrisPrattLast(const _lchar* text, int textLength, const _lchar* search, int searchLength)
		{
			// TODO: implement reverse search logic
			throw NotImplementedException();
		}

		int String::KnuthMorrisPrattInsensitive(const _lchar* text, int textLength, const _lchar* search, int searchLength)
		{
			// variables
			int* n = new int[searchLength + 1];
			int i = 0;
			int j = -1;

			// create prefix
			n[0] = -1;

			while (i < searchLength) {
				while (j >= 0 && _ltolower(search[i]) != _ltolower(search[j])) {
					j = n[j];
				}
				i++;
				j++;
				n[i] = j;
			}

			// reset variables
			i = j = 0;

			// search
			while (i < textLength) {
				while (j >= 0 && _ltolower(text[i]) != _ltolower(search[j])) {
					j = n[j];
				}
				i++;
				j++;

				if (j == searchLength) {
					delete[] n;
					return (i - j);
				}
			}

			delete[] n;
			return -1;
		}

		int String::KnuthMorrisPrattInsensitiveLast(const _lchar* text, int textLength, const _lchar* search, int searchLength)
		{
			// TODO: implement reverse search logic
			throw NotImplementedException();
		}

		String::RefChar::RefChar() :
			Char(),
			mRef(nullptr)
		{
		}

		String::RefChar::RefChar(_lchar* ch) :
			Char(),
			mRef(ch)
		{
		}

		String::RefChar::~RefChar()
		{
		}

		String::RefChar& String::RefChar::operator=(_lchar* ch)
		{
			mRef = ch;
			return (*this);
		}

		bool String::RefChar::IsBlank() const
		{
			return (_lisblank(*mRef) != 0);
		}

		bool String::RefChar::IsDigit() const
		{
			return (_lisdigit(*mRef) != 0);
		}

		bool String::RefChar::IsGraph() const
		{
			return (_lisgraph(*mRef) != 0);
		}

		bool String::RefChar::IsLetter() const
		{
			return (_lisalpha(*mRef) != 0);
		}

		bool String::RefChar::IsLetterOrDigit() const
		{
			return (_lisalnum(*mRef) != 0);
		}

		bool String::RefChar::IsLower() const
		{
			return (_lislower(*mRef) != 0);
		}

		bool String::RefChar::IsPunct() const
		{
			return (_lispunct(*mRef) != 0);
		}

		bool String::RefChar::IsUpper() const
		{
			return (_lisupper(*mRef) != 0);
		}

		bool String::RefChar::IsSpace() const
		{
			return (_lisspace(*mRef) != 0);
		}

		bool String::RefChar::IsPrint() const
		{
			return (_lisprint(*mRef) != 0);
		}

		bool String::RefChar::IsControl() const
		{
			return (_liscntrl(*mRef) != 0);
		}

		bool String::RefChar::IsHexadecimal() const
		{
			return (_lisxdigit(*mRef) != 0);
		}

		Char String::RefChar::ToLower() const
		{
			return static_cast<_lchar>(_ltolower(*mRef));
		}

		Char String::RefChar::ToUpper() const
		{
			return static_cast<_lchar>(_ltoupper(*mRef));
		}

		_lchar String::RefChar::Value() const
		{
			return (*mRef);
		}

		Char& String::RefChar::operator=(const Char& ch)
		{
			(*mRef) = ch.Value();
			return (*this);
		}

		Char String::RefChar::operator+(const Char& ch) const
		{
			return static_cast<_lchar>((*mRef) + ch.Value());
		}

		Char String::RefChar::operator-(const Char& ch) const
		{
			return static_cast<_lchar>((*mRef) - ch.Value());
		}

		Char& String::RefChar::operator+=(int value)
		{
			(*mRef) += static_cast<_lchar>(value);
			return (*this);
		}

		Char& String::RefChar::operator-=(int value)
		{
			(*mRef) -= static_cast<_lchar>(value);
			return (*this);
		}

		Char& String::RefChar::operator++()
		{
			(*mRef)++;
			return (*this);
		}

		Char& String::RefChar::operator--()
		{
			(*mRef)--;
			return (*this);
		}

		bool String::RefChar::operator==(const Char& ch) const
		{
			return ((*mRef) == ch.Value());
		}

		bool String::RefChar::operator!=(const Char& ch) const
		{
			return ((*mRef) != ch.Value());
		}
	}
}
