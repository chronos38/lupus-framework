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

#ifndef LUPUS_STRING_HPP
#define LUPUS_STRING_HPP

#include "Object.hpp"
#include "Char.hpp"
#include "ISequence.hpp"
#include "Iterator.hpp"

namespace Lupus {
	namespace System {
		/// string split flag
		enum class StringSplitOptions {
			None,
			RemoveEmptyEntries
		};

		/// String class used for internal string operations
		class LUPUS_API String : public Object, public ISequence<Char>
		{
			_lchar* mData;
			int mLength;
			int mCapacity;
		public:
			/// Create an empty string
			String();
			/**
			 * Create an instance from given native string
			 *
			 * \b Exceptions
			 * - ArgumentNullException
			 */
			String(const char* source);
			/**
			 * Create an instance from given framework string
			 *
			 * \b Exceptions
			 * - ArgumentNullException
			 */
			String(const Char* source);
			/**
			 * Create an instance form given native string, start index for native string and length
			 *
			 * \b Exceptions
			 * - ArgumentNullException
			 * - ArgumentOutOfRangeException
			 *
			 * @param source native string
			 * @param startIndex start index for native string
			 * @param count length beginning from start index
			 */
			String(const char* source, int startIndex, int count);
			/**
			 * Create an instance from given framework string, start index for framework string and length
			 *
			 * \b Exceptions
			 * - ArgumentNullException
			 * - ArgumentOutOfRangeException
			 *
			 * @param source framework string
			 * @param startIndex start index for native string
			 * @param length length beginning from start index
			 */
			String(const Char* source, int startIndex, int length);
			/// Copy string from given instance to this instance
			String(const String& string);
			/// Move string from given instance to this instance
			String(String&& string);
			/// Destructor
			virtual ~String();
			/**
			 * Append a copy from given instance to this instance
			 *
			 * @param string instance to append
			 */
			String& Append(const String& string);
			/**
			 * Append a single char to this instance
			 *
			 * @param ch char to append
			 */
			String& Append(const Char& ch);
			/// Return string capacity
			int Capacity() const;
			/**
			 * Compare two intances and return there difference
			 *
			 * @param string instance to be compared to this instance
			 * @param sensitivity flag for case sensitivity
			 * @return zero if the two strings are equal, else the difference at the first deviation
			 */
			int Compare(const String& string, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
			/**
			 * Check if this instance contains a specific value
			 *
			 * @param string instance to be checked
			 * @param sensitivity flag for case sensitivity
			 * @return true if this instance contains given string
			 */
			bool Contains(const String& string, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
			/**
			 * Copy content from this instance to a sequence container
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param sourceIndex starting index for this instance
			 * @param sequence container to copy into
			 * @param destinationIndex starting index in container
			 * @param count how many chars get copied
			 */
			void CopyTo(int sourceIndex, ISequence<Char>& sequence, int destinationIndex, int count) const;
			/// Return native string
			_lchar* Data();
			/// Return constant native string
			const _lchar* Data() const;
			/**
			 * Search for given char within this instance
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param ch char to search for
			 * @param startIndex at what index begins the search for this instance
			 * @param sensitivity defines the case sensitivity for search process
			 * @return index of first match or -1 if no such char was found
			 */
			int IndexOf(const Char& ch, int startIndex = 0, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
			/**
			 * Search for given string within this instance
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param string string to search for
			 * @param startIndex at what index begins the search for this instance
			 * @param sensitivity defines the case sensitivity for search process
			 * @return index of first match or -1 if no such string was found
			 */
			int IndexOf(const String& string, int startIndex = 0, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
			/**
			 * Search for given chars within this instance
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param sequence chars to search for
			 * @param startIndex at what index begins the search for this instance
			 * @param sensitivity defines the case sensitivity for search process
			 * @return index of first match or -1 if non of the given chars was found
			 */
			int IndexOfAny(const ISequence<Char>& sequence, int startIndex = 0, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
			/**
			 * Search for the last occurence of given char within this instance
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param ch char to search for
			 * @param startIndex at what index begins the search for this instance, counting from the last position
			 * @param sensitivity defines the case sensitivity for search process
			 * @return index of last match or -1 if no such char was found
			 */
			int LastIndexOf(const Char& ch, int startIndex = 0, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
			/**
			 * Search for the last occurence of given string within this instance
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param string string to search for
			 * @param startIndex at what index begins the search for this instance, counting from the last position
			 * @param sensitivity defines the case sensitivity for search process
			 * @return index of last match or -1 if no such string was found
			 */
			int LastIndexOf(const String& string, int startIndex = 0, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
			/**
			 * Search for the last occurence of given chars within this instance
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param sequence chars to search for
			 * @param startIndex at what index begins the search for this instance, counting from the last position
			 * @param sensitivity defines the case sensitivity for search process
			 * @return index of first match or -1 if non of the given chars was found
			 */
			int LastIndexOfAny(const ISequence<Char>& sequence, int startIndex = 0, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
			/// Return string length
			PropertyReader<int> Length = PropertyReader<int>(mLength);
			//int Length() const;
			/**
			 * Removes all char from given index to the end of string
			 *
			 * @param startIndex starting index for remove process
			 * @return reference to this instance
			 */
			String& Remove(int startIndex);
			/**
			 * Removes count chars beginning at startIndex from this instance
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param startIndex starting index for remove process
			 * @param count how many char to be removed
			 * @return reference to this instance
			 */
			String& Remove(int startIndex, int count);
			/**
			 * Replace all matching chars with given replacement char
			 *
			 * @param before old char
			 * @param after new char
			 * @param sensitivity defines the case sensitivity for replace process
			 * @return reference to this instance
			 */
			String& Replace(const Char& before, const Char& after, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive);
			/**
			 * Replace all matching strings with given replacement string
			 *
			 * @param before old string
			 * @param after new string
			 * @param sensitivity defines the case sensitivity for replace process
			 * @return reference to this instance
			 */
			String& Replace(const String& before, const String& after, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive);
			//Vector<String> Split(const Vector<Char>&, StringSplitOptions = StringSplitOptions::None) const;
			//Vector<String> Split(const Vector<Char>&, int, StringSplitOptions = StringSplitOptions::None) const;
			//Vector<String> Split(const String&, StringSplitOptions = StringSplitOptions::None) const;
			//Vector<String> Split(const String&, int, StringSplitOptions = StringSplitOptions::None) const;
			/**
			 * Create substring at starting index from this instance
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param startIndex starting index within this instance
			 * @return new substring from this instance
			 */
			String Substring(int startIndex) const;
			/**
			 * Create substring at starting index with count chars from this instance
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param startIndex starting index within this instance
			 * @param count how many chars are copied
			 * @return new substring from this instance
			 */
			String Substring(int startIndex, int count) const;
			/**
			 * Convert all chars from this instance to its lower equivalent
			 *
			 * @return reference to this instance
			 */
			String& ToLower();
			/**
			 * Convert all chars from this instance to its upper equivalent
			 *
			 * @return reference to this instance
			 */
			String& ToUpper();
			/**
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @return Char at given index
			 */
			Char& operator[](uint);
			/**
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @return Char at given index
			 */
			const Char& operator[](uint) const;
			/**
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @return Char at given index
			 */
			Char& operator[](int);
			/**
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @return Char at given index
			 */
			const Char& operator[](int) const;
			/**
			 * copy native string to this instance
			 *
			 * \b Exceptions
			 * - ArgumentNullException
			 *
			 * @return reference to this instance
			 */
			String& operator=(const _lchar*);
			/**
			 * copy string content to this instance
			 *
			 * @return reference to this instance
			 */
			String& operator=(const String&);
			/**
			 * move string content to this instance
			 *
			 * @return reference to this instance
			 */
			String& operator=(String&&);
			/**
			 * set string to single character
			 *
			 * @return reference to this instance
			 */
			String& operator=(const Char&);
			/**
			 * Append given string to a copy of this instance
			 *
			 * @param string string for appending
			 * @return resulting string
			 */
			String operator+(const String& string) const;
			/**
			 * Append given native string to this instance
			 *
			 * @param string native string for appending
			 * @return reference to this instance
			 */
			String& operator+=(const _lchar*);
			/**
			 * Append given string to this instance
			 *
			 * @param string string for appending
			 * @return reference to this instance
			 */
			String& operator+=(const String&);
			/**
			 * Append given char to this instance
			 *
			 * @param ch char for appending
			 * @return reference to this instance
			 */
			String& operator+=(const Char& ch);
			/**
			 * compare this instance to given string
			 *
			 * @param string other string for comparison
			 * @return true if this instance is equal to given string, otherwise false
			 */
			bool operator==(const String& string) const;
			/**
			 * compare this instance to given string
			 *
			 * @param string other string for comparison
			 * @return true if this instance is not equal to given string, otherwise false
			 */
			bool operator!=(const String&) const;
			virtual void Add(const Char&) override;
			virtual Char& Back() override;
			virtual const Char& Back() const override;
			virtual Iterator<Char> Begin() const override;
			virtual void Clear() override;
			virtual bool Contains(const Char&) const override;
			virtual void CopyTo(ISequence<Char>&, int) const override;
			virtual int Count() const override;
			virtual Char& Front() override;
			virtual const Char& Front() const override;
			virtual void Insert(int, const Char&) override;
			virtual void Insert(const Iterator<Char>&, const Char&) override;
			virtual bool IsEmpty() const override;
			virtual bool RemoveAt(int) override;
			virtual bool Remove(const Iterator<Char>&) override;
			virtual void Resize(int) override;
#if defined(LUPUS_WINDOWS_PLATFORM)
		public:
			/// @sa String::String(const char*)
			String(const wchar_t*);
			/// @sa String::String(const char*, int, int)
			String(const wchar_t*, int startIndex, int length);
#endif
		private:
			static String CreateWithExistingBuffer(_lchar*);
			static int GetLength(const Char*);
			static int KnuthMorrisPratt(const _lchar*, int, const _lchar*, int);
			static int KnuthMorrisPrattLast(const _lchar*, int, const _lchar*, int);
			static int KnuthMorrisPrattInsensitive(const _lchar*, int, const _lchar*, int);
			static int KnuthMorrisPrattInsensitiveLast(const _lchar*, int, const _lchar*, int);
			static _lchar* Mirror();
		private:
			/// reference char
			class LUPUS_API RefChar : public Char
			{
			public:
				RefChar();
				RefChar(_lchar*);
				virtual ~RefChar();
				virtual RefChar& operator=(_lchar*);
				virtual bool IsBlank() const override;
				virtual bool IsDigit() const override;
				virtual bool IsGraph() const override;
				virtual bool IsLetter() const override;
				virtual bool IsLetterOrDigit() const override;
				virtual bool IsLower() const override;
				virtual bool IsPunct() const override;
				virtual bool IsUpper() const override;
				virtual bool IsSpace() const override;
				virtual bool IsPrint() const override;
				virtual bool IsControl() const override;
				virtual bool IsHexadecimal() const override;
				virtual Char ToLower() const override;
				virtual Char ToUpper() const override;
				virtual _lchar Value() const override;
				virtual Char& operator=(char) override;
				virtual Char& operator=(const Char&) override;
				virtual Char operator+(const Char&) const override;
				virtual Char operator-(const Char&) const override;
				virtual Char& operator+=(int) override;
				virtual Char& operator-=(int) override;
				virtual Char& operator++() override;
				virtual Char& operator--() override;
				virtual bool operator==(const Char&) const override;
				virtual bool operator!=(const Char&) const override;
#if defined(LUPUS_WINDOWS_PLATFORM)
				virtual Char& operator=(wchar_t);
#endif
			private:
				_lchar* mRef;
			};

			mutable RefChar mCurrent;

			/// iterator
			class LUPUS_API StringIterator : public Iterator<Char>
			{
			public:
				StringIterator(_lchar*, const int&);
				StringIterator(const StringIterator&);
				StringIterator(StringIterator&&) = delete;
				virtual ~StringIterator();
				virtual bool Move(int) override;
				virtual bool Next() override;
				virtual void Reset() override;
				virtual Char* Value() override;
				virtual const Char* Value() const override;
				virtual StringIterator& operator=(const StringIterator&);
			private:
				_lchar* mPosition;
				_lchar* mInitialPosition;
				int mLength;
				mutable RefChar mValue;
			};
		};

		template <typename T>
		bool operator==(const String& lhs, const T& rhs);
		template <typename T>
		bool operator==(const T& lhs, const String& rhs);

		template <typename T>
		bool operator!=(const String& lhs, const T& rhs);
		template <typename T>
		bool operator!=(const T& lhs, const String& rhs);

		template <typename CharT>
		String operator+(const CharT* lhs, const String& rhs);
		template <typename CharT>
		String operator+(const String& lhs, const CharT* rhs);
	}
}

#include "String.inl"

#endif
