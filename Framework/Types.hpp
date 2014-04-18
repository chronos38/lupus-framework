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

#ifndef LUPUS_TYPES_HPP
#define LUPUS_TYPES_HPP

#include "Preprocessor.hpp"

// windows stuff
#ifdef LUPUS_WINDOWS_PLATFORM
// ignore "'Lupus::PropertyReader<T>' needs to have dll-interface"
#pragma warning(disable:4251)
// deavtivate SDL
#define _CRT_SECURE_NO_WARNINGS 1
// windows header
#include <Windows.h>
//! snprintf
#define snprintf sprintf_s
#endif

// unix stuff
#ifdef LUPUS_UNIX_PLATFORM
#endif

// headers
#include <initializer_list>

namespace Lupus {
	//! single signed byte
	typedef signed char sbyte;
	//! single unsigned byte
	typedef unsigned char ubyte;
	//! unsigned integer
	typedef unsigned short ushort;
	//! unsigned integer
	typedef unsigned int uint;
	//! unsigned long integer
	typedef unsigned long ulong;
	//! >=64-bit signed integer
	typedef long long llong;
	//! >=64-bit unsigned integer
	typedef unsigned long long ullong;
	//! 128-bit float point number
	typedef long double real;
	//! default allocation size for every class with array implementation
	static const int DEFAULT_ARRAY_SIZE = 32;

	namespace System {
		// declarations
		class String;

		//! sensitivity flag
		enum class CaseSensitivity {
			CaseSensitive,
			CaseInsensitive
		};
	}

	//! unique pointer type for memory allocation
	template <typename T>
	class Pointer
	{
		T* _pointer = nullptr;
	public:
		Pointer();
		Pointer(const Pointer<T>&) = delete;
		Pointer(Pointer<T>&&);
		Pointer(T* pointer);
		~Pointer();
		T* Release();
		T& operator[](int);
		const T& operator[](int) const;
		T& operator*();
		const T& operator*() const;
		T* operator->();
		const T* operator->() const;
		Pointer<T>& operator=(const Pointer<T>&) = delete;
		Pointer<T>& operator=(Pointer<T>&&);
		Pointer<T>& operator=(T*);
	};

	//! provides a reading interface for class members
	template <typename T>
	class PropertyReader
	{
		T& _reference;
	public:
		PropertyReader() = delete;
		PropertyReader(const PropertyReader<T>&) = default;
		PropertyReader<T>& operator=(const PropertyReader<T>&);
		PropertyReader(T& reference);
		operator T() const;
	};

	//! provides a writing interface for class members
	template <typename T>
	class PropertyWriter
	{
		T& _reference;
	public:
		PropertyWriter() = delete;
		PropertyWriter(const PropertyWriter<T>&) = default;
		PropertyWriter<T>& operator=(const PropertyWriter<T>&);
		PropertyWriter(T& reference);
		T operator=(const T& value);
	};

	// provides a reading and writing interface for class members
	template <typename T>
	class PropertyAccess
	{
		T& _reference;
	public:
		PropertyAccess() = delete;
		PropertyAccess(const PropertyAccess<T>&) = default;
		PropertyAccess<T>& operator=(const PropertyAccess<T>&);
		PropertyAccess(T& reference);
		T operator=(const T& value);
		operator T() const;
	};

	//! base class for every type in this library
	class LUPUS_API Object
	{
	public:
		//! allocate system resources
		Object();
		//! free system resources
		virtual ~Object();
		//! get unique hash code for this instance 
		virtual ulong GetHashCode() const;
		//! get name from in inherited class
		virtual System::String GetName() const final;
		//! get ownership for this instance
		virtual void Lock() final;
		//! try to get ownership for this instance
		virtual bool TryLock() final;
		//! release ownership from this instance
		virtual void Unlock() final;
#if defined(LUPUS_WINDOWS_PLATFORM)
	private:
		HANDLE _mutex;
#elif defined(LUPUS_UNIX_PLATFORM)
	private:
		// TODO: add unix mutex
#endif
	};

	template <typename T, typename U>
	bool operator==(const PropertyReader<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator==(const U& lhs, const PropertyReader<T>& rhs);
	template <typename T, typename U>
	bool operator!=(const PropertyReader<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator!=(const U& lhs, const PropertyReader<T>& rhs);

	template <typename T, typename U>
	bool operator==(const PropertyWriter<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator==(const U& lhs, const PropertyWriter<T>& rhs);
	template <typename T, typename U>
	bool operator!=(const PropertyWriter<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator!=(const U& lhs, const PropertyWriter<T>& rhs);

	template <typename T, typename U>
	bool operator==(const PropertyAccess<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator==(const U& lhs, const PropertyAccess<T>& rhs);
	template <typename T, typename U>
	bool operator!=(const PropertyAccess<T>& lhs, const U& rhs);
	template <typename T, typename U>
	bool operator!=(const U& lhs, const PropertyAccess<T>& rhs);
}

#include "Exception.hpp"
#include "Utility.hpp"
#include "Pointer.inl"
#include "Property.inl"

#endif
