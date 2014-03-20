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

#include "Char.hpp"
#include <cwchar>
#include <cctype>

namespace Lupus {
	namespace System {
		Char::Char() :
			_value(0)
		{
		}

		Char::Char(char ch) :
			_value(ch)
		{
		}

		Char::Char(const Char& ch)
		{
			_value = ch._value;
		}

		Char::Char(Char&& ch)
		{
			_value = ch._value;
			ch._value = 0;
		}

		Char::~Char()
		{
		}

		bool Char::IsBlank() const
		{
			return (isblank(_value) != 0);
		}

		bool Char::IsDigit() const
		{
			return (isdigit(_value) != 0);
		}

		bool Char::IsGraph() const
		{
			return (isgraph(_value) != 0);
		}

		bool Char::IsLetter() const
		{
			return (isalpha(_value) != 0);
		}

		bool Char::IsLetterOrDigit() const
		{
			return (isalnum(_value) != 0);
		}

		bool Char::IsLower() const
		{
			return (islower(_value) != 0);
		}

		bool Char::IsPunct() const
		{
			return (ispunct(_value) != 0);
		}

		bool Char::IsUpper() const
		{
			return (isupper(_value) != 0);
		}

		bool Char::IsSpace() const
		{
			return (isspace(_value) != 0);
		}

		bool Char::IsPrint() const
		{
			return (isprint(_value) != 0);
		}

		bool Char::IsControl() const
		{
			return (iscntrl(_value) != 0);
		}

		bool Char::IsHexadecimal() const
		{
			return (isxdigit(_value) != 0);
		}

		Char& Char::ToLower()
		{
			_value = static_cast<char>(tolower(_value));
			return (*this);
		}

		Char Char::ToLower() const
		{
			return static_cast<char>(tolower(_value));
		}

		Char& Char::ToUpper()
		{
			_value = static_cast<char>(toupper(_value));
			return (*this);
		}

		Char Char::ToUpper() const
		{
			return static_cast<char>(toupper(_value));
		}

		Char& Char::operator=(char ch)
		{
			_value = ch;
			return (*this);
		}

		Char& Char::operator=(const Char& ch)
		{
			_value = ch._value;
			return (*this);
		}

		Char Char::operator+(int value) const
		{
			return static_cast<decltype(_value)>(_value + value);
		}

		Char Char::operator+(const Char& ch) const
		{
			return static_cast<decltype(_value)>(_value + (int)ch.Value);
		}

		Char Char::operator-(int value) const
		{
			return static_cast<decltype(_value)>(_value - value);
		}

		Char Char::operator-(const Char& ch) const
		{
			return static_cast<decltype(_value)>(_value - (int)ch.Value);
		}

		Char& Char::operator+=(int value)
		{
			_value += static_cast<decltype(_value)>(value);
			return (*this);
		}

		Char& Char::operator+=(const Char& ch)
		{
			_value += static_cast<decltype(_value)>(ch.Value);
			return (*this);
		}

		Char& Char::operator-=(int value)
		{
			_value -= static_cast<decltype(_value)>(value);
			return (*this);
		}

		Char& Char::operator-=(const Char& ch)
		{
			_value -= static_cast<decltype(_value)>(ch.Value);
			return (*this);
		}

		Char& Char::operator++()
		{
			_value++;
			return (*this);
		}

		Char& Char::operator--()
		{
			_value--;
			return (*this);
		}

		bool Char::operator==(const Char& ch) const
		{
			return (_value == ch.Value);
		}

		bool Char::operator!=(const Char& ch) const
		{
			return (_value != ch.Value);
		}

		Char::operator char() const
		{
			return _value;
		}
	}
}
