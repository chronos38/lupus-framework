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

#ifndef LUPUS_FLOAT_HPP
#define LUPUS_FLOAT_HPP

#include "Types.hpp"

namespace Lupus {
	namespace System {
		class String;

		//! provides conversion routines for floating-point numbers
		class LUPUS_API Float
		{
		public:
			/**
			 * convert a single precision floating-point numbers to a string
			 *
			 * @param f floating-point number
			 * @return conversion result as a string
			 */
			static String ToString(float f);
			/**
			 * convert a double precision floating-point numbers to a string
			 *
			 * @param d double precision floating-point number
			 * @return conversion result as a string
			 */
			static String ToString(double d);
			/**
			 * convert a 128-bit floating-point numbers to a string
			 *
			 * @param r 128-bit floating-point number
			 * @return conversion result as a string
			 */
			static String ToString(real r);
			/**
			 * convert a string to a single precision floating-point number
			 *
			 * @param string string for conversion
			 * @param result output argument for conversion
			 * @return true if successful, otherwise false
			 */
			static bool TryParse(const String& string, float& result);
			/**
			 * convert a string to a double precision floating-point number
			 *
			 * @param string string for conversion
			 * @param result output argument for conversion
			 * @return true if successful, otherwise false
			 */
			static bool TryParse(const String& string, double& result);
			/**
			 * convert a string to a 128-bit floating-point numbers
			 *
			 * @param string string for conversion
			 * @param result output argument for conversion
			 * @return true if successful, otherwise false
			 */
			static bool TryParse(const String& string, real& result);
		};
	}
}

#endif
