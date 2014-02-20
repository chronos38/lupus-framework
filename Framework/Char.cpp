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

namespace Lupus {
	namespace System {
		Char::Char() :
			mValue(0)
		{
		}

		Char::Char(const Char& ch)
		{
			mValue = ch.mValue;
		}

		Char::Char(Char&& ch)
		{
			mValue = ch.mValue;
			ch.mValue = 0;
		}

		Char::~Char()
		{
		}

		wchar_t Char::Value() const
		{
			return mValue;
		}

		Char& Char::operator=(const Char& ch)
		{
			mValue = ch.mValue;
			return (*this);
		}

		Char& Char::operator+=(int value)
		{
			mValue += value;
			return (*this);
		}

		Char& Char::operator-=(int value)
		{
			mValue -= value;
			return (*this);
		}

		Char& Char::operator++()
		{
			mValue++;
			return (*this);
		}

		Char& Char::operator--()
		{
			mValue--;
			return (*this);
		}

		bool Char::operator==(const Char& ch) const
		{
			return (mValue == ch.Value());
		}

		bool Char::operator!=(const Char& ch) const
		{
			return (mValue != ch.Value());
		}
	}
}
