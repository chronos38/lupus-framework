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

#ifndef LUPUS_STRING_HPP
#define LUPUS_STRING_HPP

#include "Types.hpp"
#include "Char.hpp"
#include "ISequence.hpp"
#include "Iterator.hpp"
#include "IComparable.hpp"
#include "ICopyable.hpp"

namespace Lupus {
	namespace System {
		// declarations
		template <typename T>
		class Vector;
		class String;
		class StringIterator;

		//! text search algorithm interface
		class LUPUS_API ITextSearchStrategy : public ICopyable<ITextSearchStrategy>
		{
		public:
			virtual ~ITextSearchStrategy() { }
			/**
			 * searches for a pattern in a text and return index to its first occurrence
			 *
			 * @param text native search string
			 * @param textLength length of search string without the null char
			 * @param search native search pattern string
			 * @param searchLength lenght of search pattern string
			 * @param sensitivity search case sensitive or case insensitive
			 * @return index at first occurrence or -1 if search pattern don't exist within given string
			 */
			virtual int Search(const char* text, int textLength, const char* search, int searchLength, CaseSensitivity sensitivity) const = 0;
		};

		//! string split flag
		enum class StringSplitOptions {
			None,
			RemoveEmptyEntries
		};

		//! String class used for internal string operations
		class LUPUS_API String : public Object, public ISequence<char>, public IComparable<String>
		{
			//! native string
			char* _data;
			//! string length
			int _length;
			//! string capacity
			int _capacity;
			//! text search algorithm
			Pointer<ITextSearchStrategy> _strategy;
			//! default search algorithm
			static Pointer<ITextSearchStrategy> _defaultStrategy;
		public:
			//! Return string length
			PropertyReader<int> Length = PropertyReader<int>(_length);
			//! Return string capacity
			PropertyReader<int> Capacity = PropertyReader<int>(_capacity);
			//! Return native string
			PropertyReader<char*> Data = PropertyReader<char*>(_data);
			//! Set text search algorithm
			PropertyWriter<Pointer<ITextSearchStrategy>> TextSearchAlgorithm = PropertyWriter<Pointer<ITextSearchStrategy>>(_strategy);
			//! Set default serach algorithm
			static PropertyWriter<Pointer<ITextSearchStrategy>> DefaultTextSearchAlgorithm;
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
			//! \sa String::String(const char*)
			String(const wchar_t*);
			//! \sa String::String(const char*, int, int)
			String(const wchar_t*, int startIndex, int length);
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
			int Compare(const String& string, CaseSensitivity sensitivity) const;
			/**
			 * Check if this instance contains a specific value
			 *
			 * @param string instance to be checked
			 * @param sensitivity flag for case sensitivity
			 * @return true if this instance contains given string
			 */
			bool Contains(const String& string, CaseSensitivity sensitivity = CaseSensitivity::CaseSensitive) const;
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
			 * Copy content from this string to given string
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param string destination string
			 * @param startIndex destination index for copying
			 */
			void CopyTo(String& string, int startIndex) const;
			/**
			 * Copy content from this string to given string
			 *
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @param sourceIndex starting index from this string
			 * @param string destination string
			 * @param destinationIndex destination index for copying
			 * @param count how many chars are copied
			 */
			void CopyTo(int sourceIndex, String& string, int destinationIndex, int count) const;
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
			/**
			 * Reverse the whole string
			 * @return reference to this instance
			 */
			String& Reverse();
			void ShrinkToFit();
			Vector<String> Split(const Vector<char>&, StringSplitOptions = StringSplitOptions::None) const;
			Vector<String> Split(const Vector<char>&, int, StringSplitOptions = StringSplitOptions::None) const;
			Vector<String> Split(const String&, StringSplitOptions = StringSplitOptions::None) const;
			Vector<String> Split(const String&, int, StringSplitOptions = StringSplitOptions::None) const;
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
			char& operator[](int);
			/**
			 * \b Exceptions
			 * - ArgumentOutOfRangeException
			 *
			 * @return Char at given index
			 */
			const char& operator[](int) const;
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
			 * @param str native string for appending
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
			//! \sa ISwappable::Swap
			virtual void Swap(Pointer<Iterator<char>>& lhs, Pointer<Iterator<char>>& rhs) override;
			//! \sa ISequence::Add
			virtual void Add(const char&) override;
			//! \sa ISequence::Back
			virtual char& Back() override;
			//! \sa ISequence::Back
			virtual const char& Back() const override;
			//! \sa Iterable::GetIterator
			virtual Pointer<Iterator<char>> GetIterator() const override;
			//! \sa ISequence::Clear
			virtual void Clear() override;
			//! \sa ISequence::Contains
			virtual bool Contains(const char&) const override;
			//! \sa ICollection::CopyTo
			virtual void CopyTo(Vector<char>&, int) const override;
			//! \sa ICollection::CopyTo
			virtual void CopyTo(int, Vector<char>&, int, int) const override;
			//! \sa ICollection::Count
			virtual int Count() const override;
			//! \sa ISequence::Front
			virtual char& Front() override;
			//! \sa ISequence::Front
			virtual const char& Front() const override;
			//! \sa ISequence::Insert
			virtual void Insert(int, const char&) override;
			//! \sa ISequence::IsEmpty
			virtual bool IsEmpty() const override;
			//! \sa ISequence::RemoveAt
			virtual void RemoveAt(int) override;
			//! \sa ISequence::Resize
			virtual void Resize(int) override;
			//! \sa ISequence::Compare
			virtual int Compare(const String& string) const override;
		protected:
			explicit String(int);
			static String CreateWithExistingBuffer(char*);
			static int GetLength(const Char*);
			static Vector<String> SplitEmptyEntries(const String&, const Vector<char>&, int);
			static Vector<String> SplitNoEmptyEntries(const String&, const Vector<char>&, int);
			static Vector<String> SplitEmptyEntries(const String&, const String&, int);
			static Vector<String> SplitNoEmptyEntries(const String&, const String&, int);
		private:
			class StringIterator : public Iterator<char>
			{
				friend class String;
				const String* _string = nullptr;
				int _current = 0;
			public:
				StringIterator() = delete;
				StringIterator(const StringIterator&) = delete;
				StringIterator(StringIterator&&) = delete;
				StringIterator(const String*);
				virtual ~StringIterator();
				virtual void First() override;
				virtual void Next() override;
				virtual bool IsDone() const override;
				virtual const char& CurrentItem() const override;
				StringIterator& operator=(const StringIterator&) = delete;
				StringIterator& operator=(StringIterator&&) = delete;
			};
		};

		//! implements knuth-morris-pratt text search algorithm
		class LUPUS_API KnuthMorrisPratt : public ITextSearchStrategy
		{
		public:
			//! \sa ICopyable::Copy
			virtual Pointer<ITextSearchStrategy> Copy() const override;
			//! \sa TextSearchStrategy::Search
			virtual int Search(const char* text, int textLength, const char* search, int searchLength, CaseSensitivity sensitivity) const override;
		private:
			int SearchSensitive(const char* text, int textLength, const char* search, int searchLength) const;
			int SearchInsensitive(const char* text, int textLength, const char* search, int searchLength) const;
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
