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

#ifndef LUPUS_CHAR_HPP
#define LUPUS_CHAR_HPP

#include "Object.hpp"

namespace Lupus {
	namespace System {
		/// Represents a unicode character
		class LUPUS_API Char : public Object
		{
		public:
			/// Default constructor
			Char();
			/// Apply single char value
			Char(char);
			/// Copy constructor
			Char(const Char&);
			/// Move constructor
			Char(Char&&);
			/// Destructor
			virtual ~Char();
			/**
			 * Check if value is a blank character
			 *
			 * @return true if character is blank, else false
			 */
			virtual bool IsBlank() const;
			/**
			 * Check if value is a digit
			 *
			 * @return true if character is a digit, else false
			 */
			virtual bool IsDigit() const;
			/**
			 * Check if value is a graph
			 *
			 * @return true if character is graph, else false
			 */
			virtual bool IsGraph() const;
			/**
			 * Check if value is a letter
			 *
			 * @return true if character is letter, else false
			 */
			virtual bool IsLetter() const;
			/**
			 * Check if value is a letter or digit
			 *
			 * @return true if character is letter or digit, else false
			 */
			virtual bool IsLetterOrDigit() const;
			/**
			 * Check if value is a lower letter character
			 *
			 * @return true if character is lower letter, else false
			 */
			virtual bool IsLower() const;
			/**
			 * Check if value is a punct character
			 *
			 * @return true if character is punct, else false
			 */
			virtual bool IsPunct() const;
			/**
			 * Check if value is a upper letter character
			 *
			 * @return true if character is upper letter, else false
			 */
			virtual bool IsUpper() const;
			/**
			 * Check if value is a space
			 *
			 * @return true if character is space, else false
			 */
			virtual bool IsSpace() const;
			/**
			 * Check if value is a printable character
			 *
			 * @return true if character is printable, else false
			 */
			virtual bool IsPrint() const;
			/**
			 * Check if value is a control sequence
			 *
			 * @return true if character is control sequence, else false
			 */
			virtual bool IsControl() const;
			/**
			 * Check if value is a hexadecimal character
			 *
			 * @return true if character is hexadecimal, else false
			 */
			virtual bool IsHexadecimal() const;
			/**
			 * Convert this instance to a lower character
			 *
			 * @return This instance
			 */
			virtual Char& ToLower();
			/**
			 * Create lower character from this instance
			 *
			 * @return New instance with lower value from this instance
			 */
			virtual Char ToLower() const;
			/**
			 * Convert this instance to a upper character
			 *
			 * @return This instance
			 */
			virtual Char& ToUpper();
			/**
			 * Create upper character from this instance
			 *
			 * @return New instance with upper value from this instance
			 */
			virtual Char ToUpper() const;
			/// Return value from this instance
			virtual _lchar Value() const;
			/// Apply character value to this instance
			virtual Char& operator=(char);
			/// Copy value from an other instance
			virtual Char& operator=(const Char&);
			/// Add a value from an other instance
			virtual Char operator+(int) const;
			/// Add a value from an other instance
			virtual Char operator+(const Char&) const;
			/// Subtract a value from an other instance
			virtual Char operator-(int) const;
			/// Subtract a value from an other instance
			virtual Char operator-(const Char&) const;
			/// Add a value to this instance
			virtual Char& operator+=(int);
			/// Add a value to this instance
			virtual Char& operator+=(const Char&);
			/// Subtract a value from this instance
			virtual Char& operator-=(int);
			/// Subtract a value from this instance
			virtual Char& operator-=(const Char&);
			/// Increment this instance
			virtual Char& operator++();
			/// Decrement this instance
			virtual Char& operator--();
			/// Compare two instances
			virtual bool operator==(const Char&) const;
			/// Compare two instances
			virtual bool operator!=(const Char&) const;
		public:
			static const int MaxValue;
			static const int MinValue;
#if defined(LUPUS_WINDOWS_PLATFORM)
		public:
			/// @sa Char::Char(char)
			Char(wchar_t);
			/// @sa Char::operator=(char)
			Char& operator=(wchar_t);
#endif
		private:
			_lchar mValue;
		};

		template <typename T>
		bool operator==(const Char& lhs, const T& rhs);
		template <typename T>
		bool operator==(const T& lhs, const Char& rhs);

		template <typename T>
		bool operator!=(const Char& lhs, const T& rhs);
		template <typename T>
		bool operator!=(const T& lhs, const Char& rhs);

		template<typename T>
		Char operator+(const Char& lhs, const T& rhs);
		template <typename T>
		Char operator+(const T& lhs, const Char& rhs);

		template<typename T>
		Char operator-(const Char& lhs, const T& rhs);
		template <typename T>
		Char operator-(const T& lhs, const Char& rhs);
	}
}

#include "Char.inl"

#endif
