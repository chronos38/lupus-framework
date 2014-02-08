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

#ifndef LUPUS_EXCEPTION_HPP
#define LUPUS_EXCEPTION_HPP

#include "Object.hpp"

namespace lupus {
	namespace system {
		class String;

		class LUPUS_API Exception : public Object
		{
		public:
			Exception() = default;
			Exception(const Exception&);
			Exception(const String& message);
			Exception(const String& message, const Exception& innerException);
			virtual ~Exception();
			virtual String Message() const final;
			virtual Exception InnerException() const final;
		private:
			const String* mMessage = nullptr;
			const Exception* mInnerException = nullptr;
		};

		class LUPUS_API NullPointerException : public Exception
		{
		public:
			NullPointerException() = default;
			virtual ~NullPointerException() = default;
			NullPointerException(const String& message);
			NullPointerException(const String& message, const Exception& innerException);
		};

		class LUPUS_API OutOfMemoryException : public Exception
		{
		public:
			OutOfMemoryException() = default;
			virtual ~OutOfMemoryException() = default;
			OutOfMemoryException(const String& message);
			OutOfMemoryException(const String& message, const Exception& innerException);
		};

		class LUPUS_API FormatException : public Exception
		{
		public:
			FormatException() = default;
			virtual ~FormatException() = default;
			FormatException(const String& message);
			FormatException(const String& message, const Exception& innerException);
		};

		class LUPUS_API ArgumentException : public Exception
		{
		public:
			ArgumentException() = default;
			virtual ~ArgumentException() = default;
			ArgumentException(const ArgumentException&);
			ArgumentException(const String& message);
			ArgumentException(const String& message, const Exception& innerException);
		};

		class LUPUS_API ArgumentNullException : public ArgumentException
		{
		public:
			ArgumentNullException() = default;
			virtual ~ArgumentNullException() = default;
			ArgumentNullException(const String& message);
			ArgumentNullException(const String& message, const Exception& innerException);
		};

		class LUPUS_API ArgumentOutOfRangeException : public ArgumentException
		{
		public:
			ArgumentOutOfRangeException() = default;
			virtual ~ArgumentOutOfRangeException() = default;
			ArgumentOutOfRangeException(const String& message);
			ArgumentOutOfRangeException(const String& message, const Exception& innerException);
		};
	}
}

#endif
