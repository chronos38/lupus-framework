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

#include "Exception.hpp"
#include "String.hpp"
#include "Char.hpp"
#include <memory>

namespace lupus {
	namespace system {
		Exception::Exception(const String& message) :
			mMessage(new String(message))
		{
		}

		Exception::Exception(const String& message, const Exception& innerException) :
			mMessage(new String(message)),
			mInnerException(new Exception(innerException))
		{
		}

		Exception::Exception(const Exception& exception) :
			mMessage(new String(exception.Message()))
		{
		}

		Exception::~Exception()
		{
			if (mMessage) {
				delete mMessage;
			}

			if (mInnerException) {
				delete mInnerException;
			}
		}

		String Exception::Message() const
		{
			if (mMessage) {
				return (*mMessage);
			}

			return "";
		}

		Exception Exception::InnerException() const
		{
			if (mInnerException) {
				return (*mInnerException);
			}

			return Exception();
		}

		NullPointerException::NullPointerException(const String& message) :
			Exception(message)
		{
		}

		NullPointerException::NullPointerException(const String& message, const Exception& innerException) :
			Exception(message, innerException)
		{
		}
	}
}
