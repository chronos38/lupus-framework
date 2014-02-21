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

namespace Lupus {
	namespace System {
		// forwared declaration for char class
		template <typename T>
		class ISequence;

		/// String class used for internal string operations
		class LUPUS_API String : public Object
		{
		public:
			String();
			String(const char*);
			String(const Char*);
			String(const char*, int startIndex, int length);
			String(const Char*, int startIndex, int length);
			String(const String&);
			String(String&&);
			virtual ~String();
			String& Append(const String&);
			int Capacity() const;
			int Compare(const String&, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			bool Contains(const String&, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			void CopyTo(int, ISequence<Char>&, int, int) const;
			_lchar* Data();
			const _lchar* Data() const;
			int IndexOf(const Char&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			int IndexOf(const String&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			int IndexOfAny(const ISequence<Char>&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			bool IsEmpty() const;
			int LastIndexOf(const Char&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			int LastIndexOf(const String&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			int Length() const;
			String& Remove(int);
			String& Remove(int, int);
			String& Replace(const Char&, const Char&, CaseSensitivity = CaseSensitivity::CaseSensitive);
			String& Replace(const String&, const String&, CaseSensitivity = CaseSensitivity::CaseSensitive);
			//Vector<String> Split(const Vector<Char>&, StringSplitOptions = StringSplitOptions::None) const;
			//Vector<String> Split(const Vector<Char>&, int, StringSplitOptions = StringSplitOptions::None) const;
			//Vector<String> Split(const String&, StringSplitOptions = StringSplitOptions::None) const;
			//Vector<String> Split(const String&, int, StringSplitOptions = StringSplitOptions::None) const;
			String Substring(int) const;
			String Substring(int, int) const;
			String& ToLower();
			String& ToUpper();
			Char& operator[](uint);
			Char operator[](uint) const;
			Char& operator[](int);
			Char operator[](int) const;
			String& operator=(const _lchar*);
			String& operator=(const String&);
			String& operator=(String&&);
			String operator+(const String&) const;
			String& operator+=(const String&);
			bool operator==(const String&) const;
			bool operator!=(const String&) const;
#if defined(LUPUS_WINDOWS_PLATFORM)
		public:
			String(const wchar_t*);
			String(const wchar_t*, int startIndex, int length);
#endif
		protected:
			static int GetLength(const Char*);
			static int KnuthMorrisPratt(const _lchar*, int, const _lchar*, int);
			static int KnuthMorrisPrattLast(const _lchar*, int, const _lchar*, int);
			static int KnuthMorrisPrattInsensitive(const _lchar*, int, const _lchar*, int);
			static int KnuthMorrisPrattInsensitiveLast(const _lchar*, int, const _lchar*, int);
		private:
			_lchar* mData;
			int mLength;
			int mCapacity;

			// reference character
			class LUPUS_API RefChar : public Char
			{
			public:
				RefChar();
				RefChar(_lchar&);
				virtual ~RefChar();
				virtual RefChar& operator=(_lchar*);
				virtual bool IsBlank() const;
				virtual bool IsDigit() const;
				virtual bool IsGraph() const;
				virtual bool IsLetter() const;
				virtual bool IsLetterOrDigit() const;
				virtual bool IsLower() const;
				virtual bool IsPunct() const;
				virtual bool IsUpper() const;
				virtual bool IsSpace() const;
				virtual bool IsPrint() const;
				virtual bool IsControl() const;
				virtual bool IsHexadecimal() const;
				virtual Char ToLower() const;
				virtual Char ToUpper() const;
				virtual _lchar Value() const;
				virtual Char& operator=(char);
				virtual Char& operator=(const Char&);
				virtual Char operator+(const Char&) const;
				virtual Char operator-(const Char&) const;
				virtual Char& operator+=(int);
				virtual Char& operator-=(int);
				virtual Char& operator++();
				virtual Char& operator--();
				virtual bool operator==(const Char&) const;
				virtual bool operator!=(const Char&) const;
#if defined(LUPUS_WINDOWS_PLATFORM)
				virtual Char& operator=(wchar_t);
#endif
			private:
				_lchar* mRef;
			} mCurrent;
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
