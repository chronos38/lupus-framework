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

#include "Exception.hpp"
#include "String.hpp"

using namespace Lupus::System;

namespace Lupus {
	Exception::Exception() :
		Object()
	{
	}

	Exception::Exception(const String& message) :
		Object(),
		mMessage(new String(message))
	{
	}

	Exception::Exception(const String& message, const Exception& innerException) :
		Object(),
		mMessage(new String(message)),
		mInnerException(new Exception(innerException))
	{
	}

	Exception::Exception(const Exception& exception) :
		Object(),
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

	NullPointerException::NullPointerException() :
		Exception()
	{
	}

	NullPointerException::NullPointerException(const String& message) :
		Exception(message)
	{
	}

	NullPointerException::NullPointerException(const String& message, const Exception& innerException) :
		Exception(message, innerException)
	{
	}

	OutOfMemoryException::OutOfMemoryException() :
		Exception()
	{
	}

	OutOfMemoryException::OutOfMemoryException(const String& message) :
		Exception(message)
	{
	}

	OutOfMemoryException::OutOfMemoryException(const String& message, const Exception& innerException) :
		Exception(message, innerException)
	{
	}

	FormatException::FormatException() :
		Exception()
	{
	}

	FormatException::FormatException(const String& message) :
		Exception(message)
	{
	}

	FormatException::FormatException(const String& message, const Exception& innerException) :
		Exception(message, innerException)
	{
	}

	ArgumentException::ArgumentException() :
		Exception()
	{
	}

	ArgumentException::ArgumentException(const ArgumentException& argumentException) :
		Exception(argumentException)
	{
	}

	ArgumentException::ArgumentException(const String& message) :
		Exception(message)
	{
	}

	ArgumentException::ArgumentException(const String& message, const Exception& innerException) :
		Exception(message, innerException)
	{
	}

	ArgumentNullException::ArgumentNullException() :
		ArgumentException()
	{
	}

	ArgumentNullException::ArgumentNullException(const String& message) :
		ArgumentException(message)
	{
	}

	ArgumentNullException::ArgumentNullException(const String& message, const Exception& innerException) :
		ArgumentException(message, innerException)
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException() :
		ArgumentException()
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(const String& message) :
		ArgumentException(message)
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(const String& message, const Exception& innerException) :
		ArgumentException(message, innerException)
	{
	}

	NotSupportedException::NotSupportedException() :
		Exception()
	{
	}

	NotSupportedException::NotSupportedException(const String& message) :
		Exception(message)
	{
	}

	NotSupportedException::NotSupportedException(const String& message, const Exception& innerException) :
		Exception(message, innerException)
	{
	}

	NotImplementedException::NotImplementedException() :
		Exception()
	{
	}

	NotImplementedException::NotImplementedException(const String& message) :
		Exception(message)
	{
	}

	NotImplementedException::NotImplementedException(const String& message, const Exception& innerException) :
		Exception(message, innerException)
	{
	}

	SystemException::SystemException() :
		Exception()
	{
	}

	SystemException::SystemException(const String& message) :
		Exception(message)
	{
	}

	SystemException::SystemException(const String& message, const Exception& innerException) :
		Exception(message, innerException)
	{
	}

	ApplicationException::ApplicationException(const String& message) :
		Exception(message)
	{
	}

	ApplicationException::ApplicationException(const String& message, const Exception& innerException) :
		Exception(message, innerException)
	{
	}

	IteratorOutOfBoundException::IteratorOutOfBoundException(const String& message) :
		Exception(message)
	{
	}

	IteratorOutOfBoundException::IteratorOutOfBoundException(const String& message, const Exception& innerException) :
		Exception(message, innerException)
	{
	}
}
