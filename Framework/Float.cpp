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

#include "Float.hpp"
#include "Char.hpp"
#include "String.hpp"

static const size_t sFloatCount = 32;

namespace Lupus {
	namespace System {
		String Float::ToString(float value)
		{
			_lchar result[sFloatCount];
			_lmemset(result, 0, sFloatCount);
			_lsprintf(result, sFloatCount, _lstring("%f"), value);
			return result;
		}

		String Float::ToString(double value)
		{
			_lchar result[sFloatCount];
			_lmemset(result, 0, sFloatCount);
			_lsprintf(result, sFloatCount, _lstring("%lf"), value);
			return result;
		}
		
		String Float::ToString(real value)
		{
			_lchar result[sFloatCount];
			_lmemset(result, 0, sFloatCount);
			_lsprintf(result, sFloatCount, _lstring("%Lf"), value);
			return result;
		}

		bool Float::TryParse(const String& string, float& result)
		{
			return (_lsscanf(string.Data, _lstring("%f"), &result) == 1);
		}

		bool Float::TryParse(const String& string, double& result)
		{
			return (_lsscanf(string.Data, _lstring("%lf"), &result) == 1);
		}

		bool Float::TryParse(const String& string, real& result)
		{
			return (_lsscanf(string.Data, _lstring("%Lf"), &result) == 1);
		}
	}
}
