/* Copyright © 2014 David Wolf <d.wolf@live.at>
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

#include "Float.hpp"
#include "Char.hpp"
#include "String.hpp"
#include <cstdio>
#include <cstring>

static const size_t sFloatCount = 32;

namespace Lupus {
	namespace System {
		String Float::ToString(float value)
		{
			char result[sFloatCount];
			memset(result, 0, sFloatCount);
			snprintf(result, sFloatCount, ("%f"), value);
			return result;
		}

		String Float::ToString(double value)
		{
			char result[sFloatCount];
			memset(result, 0, sFloatCount);
			snprintf(result, sFloatCount, ("%lf"), value);
			return result;
		}
		
		String Float::ToString(real value)
		{
			char result[sFloatCount];
			memset(result, 0, sFloatCount);
			snprintf(result, sFloatCount, ("%Lf"), value);
			return result;
		}

		bool Float::TryParse(const String& string, float& result)
		{
			return (sscanf(string.Data, ("%f"), &result) == 1);
		}

		bool Float::TryParse(const String& string, double& result)
		{
			return (sscanf(string.Data, ("%lf"), &result) == 1);
		}

		bool Float::TryParse(const String& string, real& result)
		{
			return (sscanf(string.Data, ("%Lf"), &result) == 1);
		}
	}
}
