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

#include "Char.hpp"
#include "String.hpp"
#include "Integer.hpp"
#include "Exception.hpp"
#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <climits>

namespace lupus {
	namespace system {
		Char::Char() :
			mValue(0)
		{
		}

		Char::Char(char ch) :
			mValue(static_cast<ushort>(ch))
		{
		}

		Char::Char(wchar_t ch) :
			mValue(static_cast<ushort>(ch))
		{
		}

		Char::Char(short ch) :
			mValue(static_cast<ushort>(ch))
		{
		}

		Char::Char(ushort ch) :
			mValue(ch)
		{
		}

		Char::Char(int ch) :
			mValue(static_cast<ushort>(ch & 0xffff))
		{
		}

		Char::Char(uint ch) :
			mValue(static_cast<ushort>(ch & 0xffff))
		{
		}

		bool Char::IsBlank() const
		{
			return (u_isblank(static_cast<UChar>(mValue)) == TRUE);
		}

		bool Char::IsDigit() const
		{
			return (u_isdigit(static_cast<UChar>(mValue)) == TRUE);
		}

		bool Char::IsGraph() const
		{
			return (u_isgraph(static_cast<UChar>(mValue)) == TRUE);
		}

		bool Char::IsLetter() const
		{
			return (u_isalpha(static_cast<UChar>(mValue)) == TRUE);
		}

		bool Char::IsLetterOrDigit() const
		{
			return (IsLetter() || IsDigit());
		}

		bool Char::IsLower() const
		{
			return (u_islower(static_cast<UChar>(mValue)) == TRUE);
		}

		bool Char::IsPunct() const
		{
			return (u_ispunct(static_cast<UChar>(mValue)) == TRUE);
		}

		bool Char::IsTitle() const
		{
			return (u_istitle(static_cast<UChar>(mValue)) == TRUE);
		}

		bool Char::IsUpper() const
		{
			return (u_isupper(static_cast<UChar>(mValue)) == TRUE);
		}

		bool Char::IsWhiteSpace() const
		{
			return (u_isWhitespace(static_cast<UChar>(mValue)) == TRUE);
		}

		Char Char::ToLower() const
		{
			return static_cast<uint>(u_tolower(static_cast<UChar>(mValue)));
		}

		Char Char::ToUpper() const
		{
			return static_cast<uint>(u_toupper(static_cast<UChar>(mValue)));
		}

		Char Char::ToTitle() const
		{
			return static_cast<uint>(u_totitle(static_cast<UChar>(mValue)));
		}

		ushort Char::Unicode() const
		{
			return mValue;
		}
	}
}
