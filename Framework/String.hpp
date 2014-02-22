/* Copyright � 2014 David Wolf <d.wolf@live.at>
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
		/// String class used for internal string operations
		class LUPUS_API String : public Object, public ISequence<Char>
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
			String& Append(const Char&);
			int Capacity() const;
			int Compare(const String&, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			bool Contains(const String&, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			void CopyTo(int, ISequence<Char>&, int, int) const;
			_lchar* Data();
			const _lchar* Data() const;
			int IndexOf(const Char&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			int IndexOf(const String&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			int IndexOfAny(const ISequence<Char>&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
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
			const Char& operator[](uint) const;
			Char& operator[](int);
			const Char& operator[](int) const;
			String& operator=(const _lchar*);
			String& operator=(const String&);
			String& operator=(String&&);
			String& operator=(const Char&);
			String operator+(const String&) const;
			String& operator+=(const _lchar*);
			String& operator+=(const String&);
			String& operator+=(const Char&);
			bool operator==(const String&) const;
			bool operator!=(const String&) const;
			// sequence overrides
			virtual void Add(const Char&) override;
			virtual Iterator<Char> Begin() const override;
			virtual Char& Back() override;
			virtual const Char& Back() const override;
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
			String(const wchar_t*);
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
			_lchar* mData;
			int mLength;
			int mCapacity;

			/// reference character
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
			class LUPUS_API StringIterator : public Object, public Iterator<Char>
			{
			public:
				StringIterator(_lchar*, const int&);
				StringIterator(const StringIterator&);
				StringIterator(StringIterator&&) = delete;
				virtual ~StringIterator();
				virtual bool Next();
				virtual void Reset();
				virtual Char* Value();
				virtual const Char* Value() const;
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
