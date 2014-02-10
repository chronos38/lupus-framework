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

#ifdef LUPUS_WINDOWS_PLATFORM
#include "Integer.hpp"
#include "Exception.hpp"
#include <cwchar>
#include <cwctype>

namespace lupus {
	namespace system {
		const int Char::MaxValue = WCHAR_MAX;
		const int Char::MinValue = WCHAR_MIN;

		Char::Char(int ch) :
			mValue(static_cast<wchar_t>(ch))
		{
		}

		bool Char::IsBlank() const
		{
			return (iswblank(mValue) != 0);
		}

		bool Char::IsDigit() const
		{
			return (iswdigit(mValue) != 0);
		}

		bool Char::IsGraph() const
		{
			return (iswgraph(mValue) != 0);
		}

		bool Char::IsLetter() const
		{
			return (iswalpha(mValue) != 0);
		}

		bool Char::IsLetterOrDigit() const
		{
			return (iswalnum(mValue) != 0);
		}

		bool Char::IsLower() const
		{
			return (iswlower(mValue) != 0);
		}

		bool Char::IsPunct() const
		{
			return (iswpunct(mValue) != 0);
		}

		bool Char::IsUpper() const
		{
			return (iswupper(mValue) != 0);
		}

		bool Char::IsSpace() const
		{
			return (iswspace(mValue) != 0);
		}

		bool Char::IsPrint() const
		{
			return (iswprint(mValue) != 0);
		}

		bool Char::IsControl() const
		{
			return (iswcntrl(mValue) != 0);
		}

		bool Char::IsHexadecimal() const
		{
			return (iswxdigit(mValue) != 0);
		}

		Char Char::ToLower() const
		{
			return static_cast<int>(towlower(mValue));
		}

		Char Char::ToUpper() const
		{
			return static_cast<int>(towupper(mValue));
		}
	}
}

#endif
