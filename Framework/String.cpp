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
			mData(new _lchar[1]),
			mLength(0),
			mCapacity(0)
		{
			mData[0] = 0;
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
			mData = new _lchar[length + 1];

			// set internal buffer
			for (int i = 0; i < length; i++) {
				mData[i] = source[i].Value();
			}

			mData[length] = 0;
			mLength = mCapacity = length;
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
			mData = new _lchar[count + 1];

			// set internal buffer
			for (int i = 0; i < count; i++) {
				mData[i] = source[i + startIndex].Value();
			}

			// terminate with zero and free not needed memory
			mData[count] = 0;
			mLength = mCapacity = count;
		}

		String::String(const String& string) :
			Object(),
			mData(new wchar_t[string.Length + 1]),
			mLength(string.Length),
			mCapacity(string.Length)
		{
			_lmemcpy(mData, string.Data(), mLength);
			mData[mLength] = 0;
		}

		String::String(String&& string) :
			String()
		{
			// variables
			_lchar* swapData = mData;
			int swapLength = mLength;
			int swapCapacity = mCapacity;

			// swap memory
			mData = string.mData;
			mLength = string.mLength;
			mCapacity = string.mCapacity;

			string.mData = swapData;
			string.mLength = swapLength;
			string.mCapacity = swapCapacity;
		}

		String::~String()
		{
			if (mData) {
				delete[] mData;
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

		int String::Capacity() const
		{
			return mCapacity;
		}

		int String::Compare(const String& string, CaseSensitivity sensitivity) const
		{
			// check length
			if (mLength != string.Length) {
				return (mLength - string.Length);
			}

			// variables
			const _lchar* data = string.Data();

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = 0; i < mLength; i++) {
					if (mData[i] != data[i]) {
						return (mData[i] - data[i]);
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = 0; i < mLength; i++) {
					if (_ltolower(mData[i]) != _ltolower(data[i])) {
						return (mData[i] - data[i]);
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
			} else if (mLength < string.Length) {
				return false;
			} else if (mLength == string.Length) {
				return (Compare(string, sensitivity) == 0);
			}

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return (KnuthMorrisPratt(mData, mLength, string.Data(), string.Length) != -1);
			case CaseSensitivity::CaseInsensitive:
				return (KnuthMorrisPrattInsensitive(mData, mLength, string.Data(), string.Length) != -1);
			}

			return false;
		}

		void String::CopyTo(int sourceIndex, ISequence<Char>& sequence, int destinationIndex, int count) const
		{
			// check argument
			if ((sourceIndex + count) > mLength) {
				throw ArgumentOutOfRangeException("sourceIndex plus count exceedes string length");
			} else if (sourceIndex < 0) {
				throw ArgumentOutOfRangeException("sourceIndex must be greater than zero");
			} else if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			}

			// variables
			int limit = sourceIndex + count;
			auto it = sequence.Begin();

			// set correct position
			for (int i = 0; i < destinationIndex; i++) {
				it.Next();
			}

			// copy values
			for (int i = sourceIndex; i < limit; i++, it.Next()) {
				it.CurrentItem() = mData[i];
			}
		}

		_lchar* String::Data()
		{
			return mData;
		}

		const _lchar* String::Data() const
		{
			return mData;
		}

		int String::IndexOf(const Char& ch, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= mLength) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// variables
			Char lower = ch.ToLower();

			// comput result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = startIndex; i < mLength; i++) {
					if (mData[i] == ch) {
						return i;
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = startIndex; i < mLength; i++) {
					if (_ltolower(mData[i]) == lower) {
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
			if (startIndex >= mLength) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return KnuthMorrisPratt(mData + startIndex, mLength - startIndex, string.Data(), string.Length);
			case CaseSensitivity::CaseInsensitive:
				return KnuthMorrisPrattInsensitive(mData + startIndex, mLength - startIndex, string.Data(), string.Length);
			}

			return -1;
		}

		int String::IndexOfAny(const ISequence<Char>& sequence, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= mLength) {
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
				for (int i = startIndex; i < mLength; i++) {
					_lchar& ch = mData[i];

					while (!iterator.IsDone()) {
						if (ch == iterator.CurrentItem()) {
							return i;
						}
					}

					iterator.First();
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = startIndex; i < mLength; i++) {
					_lchar ch = _ltolower(mData[i]);

					do {
						if (ch == (*iterator.Value()).ToLower()) {
							return i;
						}
					} while (iterator.Next());

					iterator.Reset();
				}
				break;
			}

			return -1;
		}

		int String::LastIndexOf(const Char& ch, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if ((mLength - startIndex) < 0) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// variables
			Char lower = ch.ToLower();

			// comput result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = (mLength - startIndex); i >= 0; i--) {
					if (mData[i] == ch) {
						return i;
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = (mLength - startIndex); i >= 0; i--) {
					if (_ltolower(mData[i]) == lower) {
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
			if (startIndex >= mLength) {
				throw ArgumentNullException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return KnuthMorrisPrattLast(mData + startIndex, mLength - startIndex, string.Data(), string.Length);
			case CaseSensitivity::CaseInsensitive:
				return KnuthMorrisPrattInsensitiveLast(mData + startIndex, mLength - startIndex, string.Data(), string.Length);
			}

			return -1;
		}

		int String::LastIndexOfAny(const ISequence<Char>& sequence, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= mLength) {
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
			if (startIndex >= mLength) {
				throw ArgumentOutOfRangeException("startIndex exceedes string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// set range to zero
			_lmemset(mData + startIndex, 0, (mLength - startIndex));

			// update length
			mLength = startIndex;

			return (*this);
		}

		String& String::Remove(int startIndex, int count)
		{
			// check argument
			if ((startIndex + count) > mLength) {
				throw ArgumentOutOfRangeException("startIndex plus count exceedes string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			} else if (count < 0) {
				throw ArgumentOutOfRangeException("count must be greater than zero");
			}

			// variables
			int length = mLength - (startIndex + count);

			// set range to zero
			_lmemmove(mData + startIndex, mData + (startIndex + count), length);

			// update length
			mLength -= count;

			return (*this);
		}

		String& String::Replace(const Char& before, const Char& after, CaseSensitivity sensitivity)
		{
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = 0; i < mLength; i++) {
					if (mData[i] == before) {
						mData[i] = after.Value();
					}
				}
			case CaseSensitivity::CaseInsensitive:
				for (int i = 0; i < mLength; i++) {
					if (_ltolower(mData[i]) == before.ToLower()) {
						mData[i] = after.Value();
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
			if (startIndex >= mLength) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than or equal to zero");
			}

			return String(mData + startIndex);
		}

		String String::Substring(int startIndex, int count) const
		{
			if ((startIndex + count) >= mLength) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than or equal to zero");
			} else if (count <= 0) {
				throw ArgumentOutOfRangeException("length must be greater than zero");
			}

			return String(mData, startIndex, count);
		}

		String& String::ToLower()
		{
			// variables
			const _lchar* limit = mData + mLength;

			// compute result
			for (_lchar* ch = mData; ch != limit; ch++) {
				(*ch) = _ltolower(*ch);
			}

			return (*this);
		}

		String& String::ToUpper()
		{
			// variables
			const _lchar* limit = mData + mLength;

			// compute result
			for (_lchar* ch = mData; ch != limit; ch++) {
				(*ch) = _ltoupper(*ch);
			}

			return (*this);
		}

		Char& String::operator[](uint index)
		{
			if (index >= static_cast<uint>(mLength)) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			}

			return dynamic_cast<Char&>(mCurrent = (&mData[index]));
		}

		const Char& String::operator[](uint index) const
		{
			if (index >= static_cast<uint>(mLength)) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			}

			return dynamic_cast<Char&>(mCurrent = (&mData[index]));
		}

		Char& String::operator[](int index)
		{
			if (index >= mLength) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return dynamic_cast<Char&>(mCurrent = (&mData[index]));
		}

		const Char& String::operator[](int index) const
		{
			if (index >= mLength) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return dynamic_cast<Char&>(mCurrent = (&mData[index]));
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
			if (mCapacity >= length) {
				// reset buffer
				_lmemset(mData, 0, mLength);

				// set new values
				_lmemcpy(mData, string, length);
				mData[length] = 0;
				mLength = length;
			} else {
				// reallocate buffer
				delete[] mData;
				mData = new _lchar[length + 1];

				// set new values
				_lmemcpy(mData, string, length);
				mData[length] = 0;
				mLength = mCapacity = length;
			}

			return (*this);
		}

		String& String::operator=(const String& string)
		{
			// variables 
			int length = string.Length;

			// check if capacity is big enough
			if (mCapacity >= length) {
				// reset buffer
				_lmemset(mData, 0, mLength);

				// set new values
				_lmemcpy(mData, string.Data(), length);
				mData[length] = 0;
				mLength = length;
			} else {
				// reallocate buffer
				delete[] mData;
				mData = new _lchar[length + 1];

				// set new values
				_lmemcpy(mData, string.Data(), length);
				mData[length] = 0;
				mLength = mCapacity = length;
			}

			return (*this);
		}

		String& String::operator=(String&& string)
		{
			// delete[] current buffer
			delete[] mData;

			// move memory
			mData = string.mData;
			mLength = string.mLength;
			mCapacity = string.mCapacity;

			// reset string
			string.mData = new _lchar[1];
			string.mLength = 0;
			string.mCapacity = 0;

			return (*this);
		}

		String& String::operator=(const Char& ch)
		{
			if (mCapacity > 1) {
				_lmemset(mData, 0, mLength);
				mData[0] = ch.Value();
				mLength = 1;
			} else {
				// reallocate buffer
				delete[] mData;
				mData = new _lchar[2];

				// set new values
				mData[0] = ch.Value();
				mData[1] = 0;
				mLength = mCapacity = 1;
			}

			return (*this);
		}

		String String::operator+(const String& string) const
		{
			// variables
			_lchar* buffer = new _lchar[mLength + string.Length + 1];

			// copy new buffer
			_lmemcpy(buffer, mData, mLength);
			_lmemcpy(buffer + mLength, string.Data(), string.Length);
			buffer[mLength + string.Length] = 0;

			// set result and delete[] buffer
			return CreateWithExistingBuffer(buffer);
		}

		String& String::operator+=(const _lchar* str)
		{
			// variables
			int length = _lstrlen(str);

			// check if capacity is big enough
			if ((mCapacity - mLength) >= length) {
				_lmemcpy(mData + mLength, str, length);
				mLength += length;
			} else {
				// new buffer
				_lchar* buffer = new _lchar[mLength + length + 1];

				// copy new buffer
				_lmemcpy(buffer, mData, mLength);
				_lmemcpy(buffer + mLength, str, length);
				buffer[mLength + length] = 0;

				// set result and delete[] buffer
				delete[] mData;
				mData = buffer;
				mLength += length;
				mCapacity += length;
			}

			return (*this);
		}

		String& String::operator+=(const String& string)
		{
			// variables
			int length = string.Length;

			// check if capacity is big enough
			if ((mCapacity - mLength) >= length) {
				_lmemcpy(mData + mLength, string.Data(), length);
				mLength += length;
			} else {
				// new buffer
				_lchar* buffer = new _lchar[mLength + length + 1];
				
				// copy new buffer
				_lmemcpy(buffer, mData, mLength);
				_lmemcpy(buffer + mLength, string.Data(), length);
				buffer[mLength + length] = 0;

				// set result and delete[] buffer
				delete[] mData;
				mData = buffer;
				mLength += length;
				mCapacity += length;
			}

			return (*this);
		}

		String& String::operator+=(const Char& ch)
		{
			if ((mCapacity - mLength) >= 1) {
				_lmemset(mData, 0, mLength);
				mData[0] = ch.Value();
				mLength = 1;
			} else {
				// reallocate buffer
				_lchar* buffer = new _lchar[mLength + 2];

				// copy new buffer
				_lmemcpy(buffer, mData, mLength);
				buffer[mLength] = ch.Value();
				buffer[mLength + 1] = 0;

				// set result and delete[] buffer
				delete[] mData;
				mData = buffer;
				mLength += 1;
				mCapacity += 1;
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
			return operator[](mLength - 1);
		}

		const Char& String::Back() const
		{
			return operator[](mLength - 1);
		}

		SequenceIterator<Char> String::Begin() const
		{
			return SequenceIterator<Char>(this);
		}

		void String::Clear()
		{
			_lmemset(mData, 0, mLength);
			mLength = 0;
		}

		bool String::Contains(const Char& ch) const
		{
			return (_lmemchr(mData, ch.Value(), mLength) != 0);
		}

		void String::CopyTo(ISequence<Char>& sequence, int startIndex) const
		{
			CopyTo(0, sequence, startIndex, mLength);
		}

		int String::Count() const
		{
			return mLength;
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
			return (mData[0] == 0);
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

			if (count <= mCapacity) {
				_lmemset(mData, 0, count);

				// check for new length
				if (count < mLength) {
					mLength = count;
				}
			} else {
				// new buffer
				_lchar* buffer = new _lchar[count];
				_lmemset(buffer, 0, count);

				// copy old buffer delete it afterwards
				_lmemcpy(buffer, mData, mLength);
				delete[] mData;

				// set internal buffer and length
				mData = buffer;
				mLength = mCapacity = count;
			}
		}

		String String::CreateWithExistingBuffer(_lchar* str)
		{
			// variables
			String string;

			// delete buffer
			delete[] string.mData;

			// set values
			string.mData = str;
			string.mLength = _lstrlen(str);
			string.mCapacity = string.mLength;

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
