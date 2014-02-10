/* This file is part of LupusFramwork.
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

#include "Object.hpp"

namespace lupus {
	namespace system {
		// forwared declaration for char class
		class Char;

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
			//void CopyTo(uint, Array<Char>&, uint, uint) const;
			Char* Data();
			const Char* Data() const;
			int IndexOf(const Char&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			int IndexOf(const String&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			//int IndexOfAny(const Array<Char>&, uint = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			bool IsEmpty() const;
			int LastIndexOf(const Char&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			int LastIndexOf(const String&, int = 0, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
			int Length() const;
			String& Remove(int);
			String& Remove(int, int);
			String& Replace(const Char&, const Char&, CaseSensitivity = CaseSensitivity::CaseSensitive);
			String& Replace(const String&, const String&, CaseSensitivity = CaseSensitivity::CaseSensitive);
			//Array<String> Split(const Array<Char>&, StringSplitOptions = StringSplitOptions::None) const;
			//Array<String> Split(const Array<Char>&, int, StringSplitOptions = StringSplitOptions::None) const;
			//Array<String> Split(const String&, StringSplitOptions = StringSplitOptions::None) const;
			//Array<String> Split(const String&, int, StringSplitOptions = StringSplitOptions::None) const;
			String Substring(int) const;
			String Substring(int, int) const;
			String& ToLower();
			String& ToUpper();
			Char& operator[](uint);
			const Char& operator[](uint) const;
			Char& operator[](int);
			const Char& operator[](int) const;
			String& operator=(const Char*);
			String& operator=(const String&);
			String& operator=(String&&);
			String operator+(const String&) const;
			String& operator+=(const String&);
			bool operator==(const String&) const;
			bool operator!=(const String&) const;
#if defined(LUPUS_WINDOWS_PLATFORM)
			String(const wchar_t*);
			String(const wchar_t*, int startIndex, int length);
#endif
		protected:
			static int GetLength(const Char*);
			static int KnuthMorrisPrattSensitive(const Char*, int, const Char*, int);
			static int KnuthMorrisPrattInsensitive(const Char*, int, const Char*, int);
			static int KnuthMorrisPrattSensitiveLast(const Char*, int, const Char*, int);
			static int KnuthMorrisPrattInsensitiveLast(const Char*, int, const Char*, int);
		private:
			Char* mData = nullptr;
			int mLength = 0;
			int mCapacity = 0;
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
