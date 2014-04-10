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

#ifndef LUPUS_PREPROCESSOR_HPP
#define LUPUS_PREPROCESSOR_HPP

// Platform makro
#if defined(__linux) || defined(__linux__) || defined(__gnu_linx)
#  define LUPUS_LINUX_PLATFORM
#  define LUPUS_UNIX_PLATFORM
#elif defined(__APPLE__) || defined(__MACH__)
#  define LUPUS_APPLE_PLATTFORM
#  define LUPUS_UNIX_PLATFORM
#elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#  define LUPUS_WINDOWS_PLATFORM
#else
#  error platform not supported
#endif

// DLL export symbols
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#  ifdef LUPUS_DLL_EXPORT
#    ifdef __GNUC__
#      define LUPUS_API __attribute__ ((dllexport))
#    else
#      define LUPUS_API __declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      define LUPUS_API __attribute__ ((dllimport))
#    else
#      define LUPUS_API __declspec(dllimport)
#    endif
#  endif
#else
#  if __GNUC__ >= 4
#    define LUPUS_API __attribute__ ((visibility ("default")))
#  else
#    define LUPUS_API
#  endif
#endif

#endif
