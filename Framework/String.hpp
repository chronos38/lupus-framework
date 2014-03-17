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
		//! string split flag
		enum class StringSplitOptions {
			None,
			RemoveEmptyEntries
		};

		//! String class used for internal string operations
		class LUPUS_API String : public Object, public ISequence<char>
		{
			//! native string
			char* _data;
			//! string length
			int _length;
			//! string capacity
			int _capacity;
		public:
			//! Return string length
			PropertyReader<int> Length = PropertyReader<int>(_length);
			//! Return string capacity
			PropertyReader<int> Capacity = PropertyReader<int>(_capacity);
			//! Return native string
			PropertyReader<char*> Data = PropertyReader<char*>(_data);
			//! Create an empty string
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
			//! Copy string from given instance to this instance
			String(const String& string);
			//! Move string from given instance to this instance
			String(String&& string);
			//! Destructor
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
			void CopyTo(int sourceIndex, ISequence<char>& sequence, int destinationIndex, int count) const;
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
			int IndexOfAny(const ISequence<char>& sequence, int startIndex = 0, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
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
			int LastIndexOfAny(const ISequence<char>& sequence, int startIndex = 0, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
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
			virtual char& operator[](int) final;
			/**
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @return Char at given index
			 */
			virtual const char& operator[](int) const final;
			/**
			 * copy native string to this instance
			 *
			 * \b Exceptions
			 * - ArgumentNullException
			 *
			 * @return reference to this instance
			 */
			String& operator=(const char*);
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
			String& operator+=(const char*);
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
			virtual void Add(const char&) override;
			virtual char& Back() override;
			virtual const char& Back() const override;
			virtual SequenceIterator<char> Begin() const override;
			virtual void Clear() override;
			virtual bool Contains(const char&) const override;
			virtual void CopyTo(ISequence<char>&, int) const override;
			virtual int Count() const override;
			virtual char& Front() override;
			virtual const char& Front() const override;
			virtual void Insert(int, const char&) override;
			virtual void Insert(const SequenceIterator<char>&, const char&) override;
			virtual bool IsEmpty() const override;
			virtual bool RemoveAt(int) override;
			virtual bool Remove(const SequenceIterator<char>&) override;
			virtual void Resize(int) override;
#if defined(LUPUS_WINDOWS_PLATFORM)
		public:
			//! @sa String::String(const char*)
			String(const wchar_t*);
			//! @sa String::String(const char*, int, int)
			String(const wchar_t*, int startIndex, int length);
#endif
		private:
			static String CreateWithExistingBuffer(char*);
			static int GetLength(const Char*);
			static int KnuthMorrisPratt(const char*, int, const char*, int);
			static int KnuthMorrisPrattLast(const char*, int, const char*, int);
			static int KnuthMorrisPrattInsensitive(const char*, int, const char*, int);
			static int KnuthMorrisPrattInsensitiveLast(const char*, int, const char*, int);
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
