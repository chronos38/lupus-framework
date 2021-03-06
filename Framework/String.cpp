/* Copyright � 2014 David Wolf <d.wolf@live.at>
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

#include "String.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include <cstring>
#include <cctype>

namespace Lupus {
	namespace System {
		Pointer<ITextSearchStrategy> String::_defaultStrategy = new KnuthMorrisPratt();
		PropertyWriter<Pointer<ITextSearchStrategy>> String::DefaultTextSearchAlgorithm = 
			PropertyWriter<Pointer<ITextSearchStrategy>>(String::_defaultStrategy);

		String::String() :
			_data(new char[DEFAULT_ARRAY_SIZE]),
			_length(0),
			_capacity(DEFAULT_ARRAY_SIZE - 1),
			_strategy(_defaultStrategy->Copy())
		{
			memset(_data, 0, DEFAULT_ARRAY_SIZE);
		}

		String::String(const char* source) :
			_data(nullptr),
			_strategy(_defaultStrategy->Copy())
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables
			int length = strlen(source);

			// code
			_data = new char[length + 1];
			strncpy(_data, source, length);
			_data[length] = 0;
			_length = _capacity = length;
		}

		String::String(const char* source, int startIndex, int length) :
			_data(nullptr),
			_strategy(_defaultStrategy->Copy())
		{
			// check source string
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than or equal to zero");
			} else if (length <= 0) {
				throw ArgumentOutOfRangeException("length must be greater than zero");
			}

			// code
			_data = new char[length + 1];
			strncpy(_data, source + startIndex, length);
			_data[length] = 0;
			_length = _capacity = length;
		}

		String::String(const Char* source) :
			_strategy(_defaultStrategy->Copy())
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
			_data = new char[length + 1];

			// set internal buffer
			for (int i = 0; i < length; i++) {
				_data[i] = source[i].Value;
			}

			_data[length] = 0;
			_length = _capacity = length;
		}

		String::String(const Char* source, int startIndex, int count) :
			_strategy(_defaultStrategy->Copy())
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
			_data = new char[count + 1];

			// set internal buffer
			for (int i = 0; i < count; i++) {
				_data[i] = source[i + startIndex].Value;
			}

			// terminate with zero and free not needed memory
			_data[count] = 0;
			_length = _capacity = count;
		}

		String::String(const String& string) :
			_data(new char[string.Length + 1]),
			_length(string.Length),
			_capacity(string.Length),
			_strategy(_defaultStrategy->Copy())
		{
			strncpy(_data, string.Data, _length);
			_data[_length] = 0;
		}

		String::String(String&& string) :
			String()
		{
			Lupus::Swap(_data, string._data);
			Lupus::Swap(_length, string._length);
			Lupus::Swap(_capacity, string._capacity);
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
			const char* data = string.Data;

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
					if (tolower(_data[i]) != tolower(data[i])) {
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

			return (_strategy->Search(_data, _length, string._data, string._length, sensitivity) != -1);
		}

		void String::CopyTo(String& string, int startIndex) const
		{
			CopyTo(0, string, startIndex, _length);
		}

		void String::CopyTo(int sourceIndex, String& string, int destinationIndex, int count) const
		{
			// check argument
			if ((sourceIndex + count) > _length) {
				throw ArgumentOutOfRangeException("sourceIndex plus count exceedes string length");
			} else if (sourceIndex < 0) {
				throw ArgumentOutOfRangeException("sourceIndex must be greater than zero");
			} else if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			} else if ((destinationIndex + count) > string._length) {
				throw ArgumentOutOfRangeException("destinationIndex plus count exceedes string length");
			} else if (destinationIndex < 0) {
				throw ArgumentOutOfRangeException("destinationIndex must be greater than zero");
			}

			// copy values
			strncpy(string._data + destinationIndex, _data + sourceIndex, count);
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
					if (tolower(_data[i]) == lower) {
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
			int result = _strategy->Search(_data + startIndex, _length, string._data, string._length, sensitivity);

			return (result == -1 ? -1 : (startIndex + result));
		}

		int String::IndexOfAny(const ISequence<char>& sequence, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= _length) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			} else if (sequence.IsEmpty()) {
				return -1;
			}

			// comput result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = startIndex; i < _length; i++) {
					char& ch = _data[i];

					foreach(item, sequence) {
						if (ch == item->CurrentItem()) {
							return i;
						}
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = startIndex; i < _length; i++) {
					int ch = tolower(_data[i]);

					foreach(item, sequence) {
						if (ch == tolower(item->CurrentItem())) {
							return i;
						}
					}
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
					if (tolower(_data[i]) == lower) {
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

			// variables
			String textString(*this);
			String searchString(string);
			int result = -1;

			// comput result
			result = _strategy->Search(
				textString.Reverse().Data + startIndex, 
				textString._length - startIndex, 
				searchString.Reverse().Data, 
				searchString._length, 
				sensitivity);
			
			return (result == -1 ? -1 : (_length - string._length - result - startIndex));
		}

		int String::LastIndexOfAny(const ISequence<char>& sequence, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= _length) {
				throw ArgumentNullException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			} else if (sequence.IsEmpty()) {
				return -1;
			}

			// variables
			String string(*this);
			
			// compute
			return (string.Reverse().IndexOfAny(sequence, startIndex, sensitivity));
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
			_data[startIndex] = 0;

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
			int length = (startIndex + count);

			// set range to zero
			for (int i = startIndex; i < length; i++) {
				_data[i] = _data[i + count];
			}

			// update length
			_length -= count;

			return (*this);
		}

		String& String::Replace(const Char& before, const Char& after, CaseSensitivity sensitivity)
		{
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = _length - 1; i >= 0; i--) {
					if (_data[i] == before) {
						_data[i] = after.Value;
					}
				}
			case CaseSensitivity::CaseInsensitive:
				for (int i = _length - 1; i >= 0; i--) {
					if (tolower(_data[i]) == before.ToLower()) {
						_data[i] = after.Value;
					}
				}
			}

			return (*this);
		}

		String& String::Replace(const String& before, const String& after, CaseSensitivity sensitivity)
		{
			// variables
			int index = 0;

			// replace loop
			while ((index = IndexOf(before, index, sensitivity)) != -1) {
				for (int i = 0; i < before._length; i++) {
					RemoveAt(index);
				}
				for (int i = 0; i < after._length; i++) {
					Insert(index + i, after[i]);
				}
			}

			return (*this);
		}

		String& String::Reverse()
		{
			// variables
			char* swap = _data;
			char* data = new char[_length + 1];

			// reverse string
			for (int i = (_length - 1), j = 0; i >= 0; i--, j++) {
				data[j] = _data[i];
			}

			_data = data;
			delete[] swap;
			_data[_length] = 0;

			return (*this);
		}

		void String::ShrinkToFit()
		{
			char* swap = new char[_length + 1];
			strncpy(swap, _data, _length);
			_capacity = _length;
			Lupus::Swap(swap, _data);
			delete swap;

			if (_capacity <= 0) {
				_data[0] = 0;
			}
		}
		
		Vector<String> String::Split(const Vector<char>& delimiter, StringSplitOptions splitOptions) const
		{
			return Split(delimiter, _length, splitOptions);
		}

		Vector<String> String::Split(const Vector<char>& delimiter, int count, StringSplitOptions splitOptions) const
		{
			// check argument
			if (count < 0) {
				throw ArgumentOutOfRangeException("count is negativ");
			}

			switch (splitOptions) {
			case StringSplitOptions::None:
				return SplitEmptyEntries(*this, delimiter, count);
			case StringSplitOptions::RemoveEmptyEntries:
				return SplitNoEmptyEntries(*this, delimiter, count);
			}

			return Vector<String>();
		}

		Vector<String> String::Split(const String& delimiter, StringSplitOptions splitOptions) const
		{	
			switch (splitOptions) {
			case StringSplitOptions::None:
				return SplitEmptyEntries(*this, delimiter, _length);
			case StringSplitOptions::RemoveEmptyEntries:
				return SplitNoEmptyEntries(*this, delimiter, _length);
			}

			return Vector<String>();
		}

		Vector<String> String::Split(const String& delimiter, int count, StringSplitOptions splitOptions) const
		{
			// check argument
			if (count < 0) {
				throw ArgumentOutOfRangeException("count is negativ");
			}

			switch (splitOptions) {
			case StringSplitOptions::None:
				return SplitEmptyEntries(*this, delimiter, count);
			case StringSplitOptions::RemoveEmptyEntries:
				return SplitNoEmptyEntries(*this, delimiter, count);
			}

			return Vector<String>();
		}

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
			const char* limit = _data + _length;

			// compute result
			for (char* ch = _data; ch != limit; ch++) {
				(*ch) = static_cast<char>(tolower(*ch));
			}

			return (*this);
		}

		String& String::ToUpper()
		{
			// variables
			const char* limit = _data + _length;

			// compute result
			for (char* ch = _data; ch != limit; ch++) {
				(*ch) = static_cast<char>(toupper(*ch));
			}

			return (*this);
		}

		char& String::operator[](int index)
		{
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return (_data[index]);
		}

		const char& String::operator[](int index) const
		{
			if (index >= _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return (_data[index]);
		}

		String& String::operator=(const char* string)
		{
			// check argument
			if (!string) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables 
			int length = strlen(string);

			// check if capacity is big enough
			if (_capacity >= length) {
				// set new values
				strncpy(_data, string, length);
				_data[length] = 0;
				_length = length;
			} else {
				// reallocate buffer
				delete[] _data;
				_data = new char[length + 1];

				// set new values
				strncpy(_data, string, length);
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
				// set new values
				strncpy(_data, string.Data, length);
				_data[length] = 0;
				_length = length;
			} else {
				// reallocate buffer
				delete[] _data;
				_data = new char[length + 1];

				// set new values
				strncpy(_data, string.Data, length);
				_data[length] = 0;
				_length = _capacity = length;
			}

			return (*this);
		}

		String& String::operator=(String&& string)
		{
			Lupus::Swap(_data, string._data);
			Lupus::Swap(_length, string._length);
			Lupus::Swap(_capacity, string._capacity);
			return (*this);
		}

		String& String::operator=(const Char& ch)
		{
			if (_capacity > 1) {
				_data[0] = ch.Value;
				_data[1] = 0;
				_length = 1;
			} else {
				// reallocate buffer
				delete[] _data;
				_data = new char[DEFAULT_ARRAY_SIZE];

				// set new values
				_data[0] = ch.Value;
				_data[1] = 0;
				_length = 1;
				_capacity = DEFAULT_ARRAY_SIZE - 1;
			}

			return (*this);
		}

		String String::operator+(const String& string) const
		{
			// variables
			char* buffer = new char[_length + string.Length + 1];

			// copy new buffer
			strncpy(buffer, _data, _length);
			strncpy(buffer + _length, string.Data, string.Length);
			buffer[_length + string.Length] = 0;

			// set result and delete[] buffer
			return CreateWithExistingBuffer(buffer);
		}

		String& String::operator+=(const char* str)
		{
			// variables
			int length = strlen(str);

			// check if capacity is big enough
			if ((_capacity - _length) >= length) {
				strncpy(_data + _length, str, length);
				_length += length;
			} else {
				// new buffer
				char* buffer = new char[_length + length + 1];

				// copy new buffer
				strncpy(buffer, _data, _length);
				strncpy(buffer + _length, str, length);
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
				strncpy(_data + _length, string.Data, length);
				_length += length;
			} else {
				// new buffer
				char* buffer = new char[_length + length + 1];
				
				// copy new buffer
				strncpy(buffer, _data, _length);
				strncpy(buffer + _length, string.Data, length);
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
				_data[0] = ch.Value;
				_data[1] = 0;
				_length = 1;
			} else {
				// reallocate buffer
				char* buffer = new char[_length + 2];

				// copy new buffer
				strncpy(buffer, _data, _length);
				buffer[_length] = ch.Value;
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
			return (Compare(string) == 0);
		}

		bool String::operator!=(const String& string) const
		{
			return (Compare(string) != 0);
		}

		void String::Swap(Pointer<Iterator<char>>& lhs, Pointer<Iterator<char>>& rhs)
		{
			try {
				StringIterator& first = dynamic_cast<StringIterator&>(*lhs);
				StringIterator& second = dynamic_cast<StringIterator&>(*rhs);

				if (this != first._string || this != second._string) {
					throw InvalidIteratorException();
				} else if (lhs->IsDone() || rhs->IsDone()) {
					throw IteratorOutOfBoundException();
				}

				Lupus::Swap(_data[first._current], _data[second._current]);

			} catch (...) {
				throw InvalidIteratorException();
			}
		}

		void String::Add(const char& ch)
		{
			operator+=(ch);
		}

		char& String::Back()
		{
			return operator[](_length - 1);
		}

		const char& String::Back() const
		{
			return operator[](_length - 1);
		}

		Pointer<Iterator<char>> String::GetIterator() const
		{
			return new StringIterator(this);
		}

		void String::Clear()
		{
			_data[0] = 0;
			_length = 0;
		}

		bool String::Contains(const char& ch) const
		{
			for (int i = _length - 1; i >= 0; i--) {
				if (_data[i] == ch) {
					return true;
				}
			}

			return false;
		}

		void String::CopyTo(Vector<char>& vector, int startIndex) const
		{
			CopyTo(0, vector, startIndex, vector.Length);
		}

		void String::CopyTo(int sourceIndex, Vector<char>& vector, int destinationIndex, int count) const
		{
			// check argument
			if ((sourceIndex + count) > _length) {
				throw ArgumentOutOfRangeException("sourceIndex plus count exceedes string length");
			} else if (sourceIndex < 0) {
				throw ArgumentOutOfRangeException("sourceIndex must be greater than zero");
			} else if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			} else if ((destinationIndex + count) > vector.Count()) {
				throw ArgumentOutOfRangeException("destinationIndex plus count exceedes collection length");
			} else if (destinationIndex < 0) {
				throw ArgumentOutOfRangeException("destinationIndex must be greater than zero");
			}

			// variables
			int limit = sourceIndex + count;

			// copy values
			for (int i = sourceIndex, j = destinationIndex; i < limit; i++, j++) {
				vector[j] = _data[i];
			}
		}

		int String::Count() const
		{
			return _length;
		}

		char& String::Front()
		{
			return operator[](0);
		}

		const char& String::Front() const
		{
			return operator[](0);
		}

		void String::Insert(int index, const char& ch)
		{
			// check arguments
			if (index > _length) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			// variables
			String string(_length + 1);

			// set result
			CopyTo(0, string, 0, index);
			string[index] = ch;
			CopyTo(index, string, index + 1, _length - index);
			Lupus::Swap(string, *this);
		}

		bool String::IsEmpty() const
		{
			return (_data[0] == 0);
		}

		void String::RemoveAt(int index)
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

		void String::Resize(int count)
		{
			// check argument
			if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			}

			if (count <= _capacity) {
				_data[count] = 0;

				// check for new length
				if (count < _length) {
					_length = count;
				}
			} else {
				// new buffer
				char* buffer = new char[count];

				// copy old buffer delete it afterwards
				strncpy(buffer, _data, _length);
				delete[] _data;

				// set internal buffer and length
				_data = buffer;
				_length = _capacity = count;
			}
		}

		int String::Compare(const String& string) const
		{
			return Compare(string, CaseSensitivity::CaseSensitive);
		}

		String::String(int capacity) :
			_data(new char[capacity + 1]),
			_length(capacity),
			_capacity(capacity),
			_strategy(_defaultStrategy->Copy())
		{
			memset(_data, ' ', capacity);
			_data[capacity] = 0;
		}

		String String::CreateWithExistingBuffer(char* str)
		{
			// variables
			String string;

			// delete buffer
			delete[] string._data;

			// set values
			string._data = str;
			string._length = strlen(str);
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

		Vector<String> String::SplitEmptyEntries(const String& string, const Vector<char>& delimiter, int count)
		{
			// variables
			int lastIndex = -1;
			Vector<String> vector;

			// compute result
			for (int i = 0; i < string._length; i++) {
				foreach(item, delimiter) {
					if (string._data[i] != item->CurrentItem()) {
						continue;
					} else if (i == lastIndex + 1) {
						vector.Add(String());
					} else {
						vector.Add(String(string._data, lastIndex + 1, i - lastIndex - 1));
					}

					lastIndex = i;

					if (vector.Length >= count - 1) {
						vector.Add(String(string._data, lastIndex + 1, string._length - i - 1));
						return vector;
					}

					break;
				}
			}

			if (lastIndex != string._length - 1) {
				vector.Add(String(string._data, lastIndex + 1, string._length - lastIndex - 1));
			}

			return vector;
		}

		Vector<String> String::SplitNoEmptyEntries(const String& string, const Vector<char>& delimiter, int count)
		{
			// variables
			int lastIndex = -1;
			Vector<String> vector;

			// compute result
			for (int i = 0; i < string._length; i++) {
				foreach(item, delimiter) {
					if (string._data[i] != item->CurrentItem()) {
						continue;
					} else if (i != lastIndex + 1) {
						vector.Add(String(string._data, lastIndex + 1, i - lastIndex - 1));
					}

					lastIndex = i;

					if (vector.Length >= count - 1) {
						vector.Add(String(string._data, lastIndex + 1, string._length - i - 1));
						return vector;
					}

					break;
				}
			}

			if (lastIndex != string._length - 1) {
				vector.Add(String(string._data, lastIndex + 1, string._length - lastIndex - 1));
			}

			return vector;
		}

		Vector<String> String::SplitEmptyEntries(const String& string, const String& delimiter, int count)
		{
			// variables
			int index = 0;
			int lastIndex = -1;
			Vector<String> vector;

			while (index != -1) {
				index = string.IndexOf(delimiter, lastIndex + 1);
				
				if (lastIndex + 1 == index) {
					vector.Add(String());
				} else {
					// TODO: readable calculation
					int startIndex = ((lastIndex == -1) ? (0) : (lastIndex + delimiter._length));
					int length = ((index == -1) ? (string._length - lastIndex - delimiter._length) : (index - lastIndex - delimiter._length));
					vector.Add(String(string._data, startIndex, length));
				}

				lastIndex = index;

				if (vector.Length >= count - 1) {
					// TODO: readable calculation
					int startIndex = ((lastIndex == -1) ? (0) : (lastIndex + delimiter._length));
					int length = ((lastIndex == -1) ? (string._length) : (string._length - lastIndex - delimiter._length));
					vector.Add(String(string._data, startIndex, length));
					return vector;
				}
			}

			return vector;
		}

		Vector<String> String::SplitNoEmptyEntries(const String& string, const String& delimiter, int count)
		{
			// variables
			int index = 0;
			int lastIndex = -1;
			Vector<String> vector;

			while ((index = string.IndexOf(delimiter, index)) != -1) {
				if (lastIndex + 1 != index) {
					vector.Add(String(string._data, lastIndex + delimiter.Length, index - lastIndex - 1));
				}

				lastIndex = index;

				if (vector.Length >= count - 1) {
					vector.Add(String(string._data, lastIndex + delimiter.Length, string._length - index - 1));
					return vector;
				}
			}
		}

		String::StringIterator::StringIterator(const String* string) :
			_string(string)
		{
			if (!string) {
				throw ArgumentNullException();
			}
		}

		String::StringIterator::~StringIterator()
		{
		}

		void String::StringIterator::First()
		{
			_current = 0;
		}

		void String::StringIterator::Next()
		{
			_current++;
		}

		bool String::StringIterator::IsDone() const
		{
			return (_current >= _string->Count());
		}

		const char& String::StringIterator::CurrentItem() const
		{
			if (IsDone()) {
				throw IteratorOutOfBoundException();
			}

			return (_string->operator[](_current));
		}

		Pointer<ITextSearchStrategy> KnuthMorrisPratt::Copy() const
		{
			return new KnuthMorrisPratt();
		}

		int KnuthMorrisPratt::Search(const char* text, int textLength, const char* search, int searchLength, CaseSensitivity sensitivity) const
		{
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return SearchSensitive(text, textLength, search, searchLength);
			case CaseSensitivity::CaseInsensitive:
				return SearchInsensitive(text, textLength, search, searchLength);
			}

			return -1;
		}

		int KnuthMorrisPratt::SearchSensitive(const char* text, int textLength, const char* search, int searchLength) const
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

		int KnuthMorrisPratt::SearchInsensitive(const char* text, int textLength, const char* search, int searchLength) const
		{
			// variables
			int* n = new int[searchLength + 1];
			int i = 0;
			int j = -1;

			// create prefix
			n[0] = -1;

			while (i < searchLength) {
				while (j >= 0 && tolower(search[i]) != tolower(search[j])) {
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
				while (j >= 0 && tolower(text[i]) != tolower(search[j])) {
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
	}
}
