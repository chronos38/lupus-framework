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

#ifndef LUPUS_EXCEPTION_HPP
#define LUPUS_EXCEPTION_HPP

#include "Object.hpp"

namespace Lupus {
	namespace System {
		class String;
	}
	
	class LUPUS_API Exception : public Object
	{
	public:
		Exception();
		Exception(const Exception&);
		Exception(const System::String& message);
		Exception(const System::String& message, const Exception& innerException);
		virtual ~Exception();
		virtual System::String Message() const final;
		virtual Exception InnerException() const final;
	private:
		const System::String* mMessage = nullptr;
		const Exception* mInnerException = nullptr;
	};

	class LUPUS_API NullPointerException : public Exception
	{
	public:
		using Exception::Exception;
		virtual ~NullPointerException() = default;
		NullPointerException(const System::String& message);
		NullPointerException(const System::String& message, const Exception& innerException);

	};

	class LUPUS_API OutOfMemoryException : public Exception
	{
	public:
		using Exception::Exception;
		virtual ~OutOfMemoryException() = default;
		OutOfMemoryException(const System::String& message);
		OutOfMemoryException(const System::String& message, const Exception& innerException);
	};

	class LUPUS_API FormatException : public Exception
	{
	public:
		using Exception::Exception;
		virtual ~FormatException() = default;
		FormatException(const System::String& message);
		FormatException(const System::String& message, const Exception& innerException);
	};

	class LUPUS_API ArgumentException : public Exception
	{
	public:
		using Exception::Exception;
		virtual ~ArgumentException() = default;
		ArgumentException(const ArgumentException&);
		ArgumentException(const System::String& message);
		ArgumentException(const System::String& message, const Exception& innerException);
	};

	class LUPUS_API ArgumentNullException : public ArgumentException
	{
	public:
		using ArgumentException::ArgumentException;
		virtual ~ArgumentNullException() = default;
		ArgumentNullException(const System::String& message);
		ArgumentNullException(const System::String& message, const Exception& innerException);
	};

	class LUPUS_API ArgumentOutOfRangeException : public ArgumentException
	{
	public:
		using ArgumentException::ArgumentException;
		virtual ~ArgumentOutOfRangeException() = default;
		ArgumentOutOfRangeException(const System::String& message);
		ArgumentOutOfRangeException(const System::String& message, const Exception& innerException);
	};

	class LUPUS_API NotSupportedException : public Exception
	{
	public:
		using Exception::Exception;
		virtual ~NotSupportedException() = default;
		NotSupportedException(const System::String& message);
		NotSupportedException(const System::String& message, const Exception& innerException);
	};

	class LUPUS_API NotImplementedException : public Exception
	{
	public:
		using Exception::Exception;
		virtual ~NotImplementedException() = default;
		NotImplementedException(const System::String& message);
		NotImplementedException(const System::String& message, const Exception& innerException);
	};

	class LUPUS_API SystemException : public Exception
	{
	public:
		using Exception::Exception;
		virtual ~SystemException() = default;
		SystemException(const System::String& message);
		SystemException(const System::String& message, const Exception& innerException);
	};
}

#endif
