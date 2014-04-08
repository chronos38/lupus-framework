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
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Framework\Char.hpp"
#include "..\Framework\String.hpp"
#include "..\Framework\Exception.hpp"
#include "..\Framework\Vector.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Lupus;
using namespace Lupus::System;

namespace FrameworkTest
{
	TEST_CLASS(StringTest)
	{
	public:
		TEST_METHOD(StringConstructorTest)
		{
			// variables
			Char ch[] = { 'a', 'b', 'c', 'd', 'e', 'f', '\0' };

			// default constructor
			Assert::AreEqual(0, (int)String().Length, L"default constructor", LINE_INFO());

			// (const char*) constructor
			Assert::AreEqual(3, (int)String("abc").Length, L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual(3, (int)String("abc").Capacity, L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual('a', String("abc")[0], L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual('b', String("abc")[1], L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual('c', String("abc")[2], L"(const char*) constructor", LINE_INFO());

			// (const wchar_t*) constructor
			Assert::AreEqual(3, (int)String(L"abc").Length, L"(const wchar_t*) constructor", LINE_INFO());
			Assert::AreEqual(3, (int)String(L"abc").Capacity, L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual('a', String(L"abc")[0], L"(const wchar_t*) constructor", LINE_INFO());
			Assert::AreEqual('b', String(L"abc")[1], L"(const wchar_t*) constructor", LINE_INFO());
			Assert::AreEqual('c', String(L"abc")[2], L"(const wchar_t*) constructor", LINE_INFO());

			// (const Char*) constructor
			Assert::AreEqual(6, (int)String(ch).Length, L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual(6, (int)String(ch).Capacity, L"(const char*) constructor", LINE_INFO());
			Assert::AreEqual('a', String(ch)[0], L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual('b', String(ch)[1], L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual('c', String(ch)[2], L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual('d', String(ch)[3], L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual('e', String(ch)[4], L"(const Char*) constructor", LINE_INFO());
			Assert::AreEqual('f', String(ch)[5], L"(const Char*) constructor", LINE_INFO());

			// (const char*,int,int) constructor
			Assert::AreEqual(2, (int)String("abcdef", 2, 2).Length, L"(const wchar_t*, int, int) constructor", LINE_INFO());
			Assert::AreEqual(2, (int)String("abcdef", 2, 2).Capacity, L"(const wchar_t*, int, int) constructor", LINE_INFO());
			Assert::AreEqual('c', String("abcdef", 2, 2)[0], L"(const wchar_t*, int, int) constructor", LINE_INFO());
			Assert::AreEqual('d', String("abcdef", 2, 2)[1], L"(const wchar_t*, int, int) constructor", LINE_INFO());

			// (const wchar_t*,int,int) constructor
			Assert::AreEqual(2, (int)String(L"abcdef", 2, 2).Length, L"(const wchar_t*, int, int) constructor", LINE_INFO());
			Assert::AreEqual(2, (int)String(L"abcdef", 2, 2).Capacity, L"(const wchar_t*, int, int) constructor", LINE_INFO());
			Assert::AreEqual('c', String(L"abcdef", 2, 2)[0], L"(const wchar_t*, int, int) constructor", LINE_INFO());
			Assert::AreEqual('d', String(L"abcdef", 2, 2)[1], L"(const wchar_t*, int, int) constructor", LINE_INFO());

			// (const Char*,int,int) constructor
			Assert::AreEqual(2, (int)String(ch, 2, 2).Length, L"(const wchar_t*, int, int) constructor", LINE_INFO());
			Assert::AreEqual(2, (int)String(ch, 2, 2).Capacity, L"(const wchar_t*, int, int) constructor", LINE_INFO());
			Assert::AreEqual('c', String(ch, 2, 2)[0], L"(const wchar_t*, int, int) constructor", LINE_INFO());
			Assert::AreEqual('d', String(ch, 2, 2)[1], L"(const wchar_t*, int, int) constructor", LINE_INFO());
		}

		TEST_METHOD(StringAppendTest)
		{
			// variables
			String string;

			// operator+=
			string += "abc";
			Assert::AreEqual(3, (int)string.Length, L"operator+=", LINE_INFO());
			Assert::AreEqual(63, (int)string.Capacity, L"operator+=", LINE_INFO());
			Assert::AreEqual('a', string[0], L"operator+=", LINE_INFO());
			Assert::AreEqual('b', string[1], L"operator+=", LINE_INFO());
			Assert::AreEqual('c', string[2], L"operator+=", LINE_INFO());

			// Append
			string.Append("def");
			Assert::AreEqual(6, (int)string.Length, L"Append", LINE_INFO());
			Assert::AreEqual(63, (int)string.Capacity, L"Append", LINE_INFO());
			Assert::AreEqual('a', string[0], L"Append", LINE_INFO());
			Assert::AreEqual('b', string[1], L"Append", LINE_INFO());
			Assert::AreEqual('c', string[2], L"Append", LINE_INFO());
			Assert::AreEqual('d', string[3], L"Append", LINE_INFO());
			Assert::AreEqual('e', string[4], L"Append", LINE_INFO());
			Assert::AreEqual('f', string[5], L"Append", LINE_INFO());
		}

		TEST_METHOD(StringCompareTest)
		{
			// variables
			String string("ABCdef");

			// case sensitive
			Assert::IsTrue(string.Compare("ABCdef") == 0, L"case sensitive", LINE_INFO());
			Assert::IsTrue(string.Compare("abcdef") != 0, L"case sensitive", LINE_INFO());
			Assert::IsTrue(string.Compare("ABC") != 0, L"case sensitive", LINE_INFO());

			// case insensitive
			Assert::IsTrue(string.Compare("ABCdef", CaseSensitivity::CaseInsensitive) == 0, L"case insensitive", LINE_INFO());
			Assert::IsTrue(string.Compare("abcdef", CaseSensitivity::CaseInsensitive) == 0, L"case insensitive", LINE_INFO());
			Assert::IsTrue(string.Compare("abcDEF", CaseSensitivity::CaseInsensitive) == 0, L"case insensitive", LINE_INFO());
			Assert::IsTrue(string.Compare("ABC", CaseSensitivity::CaseInsensitive) != 0, L"case insensitive", LINE_INFO());
		}

		TEST_METHOD(StringContainsTest)
		{
			// variables
			String string("ABCdef");

			// case sensitive
			Assert::IsTrue(string.Contains(""), L"case sensitive", LINE_INFO());
			Assert::IsTrue(string.Contains("ABC"), L"case sensitive", LINE_INFO());
			Assert::IsTrue(string.Contains("def"), L"case sensitive", LINE_INFO());
			Assert::IsFalse(string.Contains("ABCdefg"), L"case sensitive", LINE_INFO());
			Assert::IsFalse(string.Contains("abc"), L"case sensitive", LINE_INFO());

			// case insensitive
			Assert::IsTrue(string.Contains("abc", CaseSensitivity::CaseInsensitive), L"case insensitive", LINE_INFO());
			Assert::IsTrue(string.Contains("DEF", CaseSensitivity::CaseInsensitive), L"case insensitive", LINE_INFO());
			Assert::IsTrue(string.Contains("abcDEF", CaseSensitivity::CaseInsensitive), L"case insensitive", LINE_INFO());
			Assert::IsFalse(string.Contains("fedcba", CaseSensitivity::CaseInsensitive), L"case insensitive", LINE_INFO());
		}

		TEST_METHOD(StringIndexOfTest)
		{
			// variables
			String string("ABCdef");

			// (Char) case sensitive
			Assert::AreEqual(0, string.IndexOf('A'), L"(Char) case sensitive", LINE_INFO());
			Assert::AreEqual(2, string.IndexOf('C', 2), L"(Char, int) case sensitive", LINE_INFO());
			Assert::AreEqual(-1, string.IndexOf('d', 4), L"(Char, int) case sensitive", LINE_INFO());

			// (Char) case insensitive
			Assert::AreEqual(4, string.IndexOf('E', 2, CaseSensitivity::CaseInsensitive), L"(Char) case insensitive", LINE_INFO());

			// (String) case sensitive
			Assert::AreEqual(2, string.IndexOf("Cd"), L"(String) case sensitive", LINE_INFO());
			Assert::AreEqual(-1, string.IndexOf("Cd", 3), L"(String, int) case sensitive", LINE_INFO());

			// (String) case insensitive
			Assert::AreEqual(2, string.IndexOf("cD", 0, CaseSensitivity::CaseInsensitive), L"(String) case sensitive", LINE_INFO());
			Assert::AreEqual(-1, string.IndexOf("cD", 3, CaseSensitivity::CaseInsensitive), L"(String, int) case sensitive", LINE_INFO());
		}

		TEST_METHOD(StringIndexOfAnyTest)
		{
			// variables
			String string("ABCdef");

			// TODO: add implementation when first sequence containers are finished
		}

		TEST_METHOD(StringLastIndexOfTest)
		{
			// variables
			String string("AaBbAaBb");

			// (Char) case sensitive
			Assert::AreEqual(6, string.LastIndexOf('B'), L"(Char) case sensitive", LINE_INFO());
			Assert::AreEqual(5, string.LastIndexOf('a', 2), L"(Char, int) case sensitive", LINE_INFO());
			Assert::AreEqual(4, string.LastIndexOf('A', 4), L"(Char, int) case sensitive", LINE_INFO());

			// (Char) case insensitive
			Assert::AreEqual(5, string.LastIndexOf('A', 2, CaseSensitivity::CaseInsensitive), L"(Char) case insensitive", LINE_INFO());

			// (String) case sensitive
			Assert::AreEqual(4, string.LastIndexOf("Aa"), L"(String) case sensitive", LINE_INFO());
			Assert::AreEqual(0, string.LastIndexOf("Aa", 3), L"(String, int) case sensitive", LINE_INFO());

			// (String) case insensitive
			Assert::AreEqual(4, string.LastIndexOf("aA", 0, CaseSensitivity::CaseInsensitive), L"(String) case sensitive", LINE_INFO());
			Assert::AreEqual(0, string.LastIndexOf("aA", 3, CaseSensitivity::CaseInsensitive), L"(String, int) case sensitive", LINE_INFO());

			// (Char) cas sensitive
			Assert::AreEqual(-1, string.LastIndexOf('C'), L"(Char) case sensitive -1", LINE_INFO());
		}

		TEST_METHOD(StringRemoveTest)
		{
			// variables
			String string("ABCdefGHIjkl");

			// (int) remove
			Assert::IsTrue(string.Remove(6).Compare("ABCdef") == 0, L"(int) remove", LINE_INFO());

			// (int,int) remove
			Assert::IsTrue(string.Remove(0,3).Compare("def") == 0, L"(int, int) remove", LINE_INFO());
		}

		TEST_METHOD(StringReplaceTest)
		{
			// variables
			String string("AaBbAaBb");

			// (Char, Char) case sensitive
			Assert::IsTrue(string.Replace('A', 'a').Compare("aaBbaaBb") == 0, L"(Char, Char) case sensitive", LINE_INFO());

			// (Char, Char) case insensitive
			Assert::IsTrue(string.Replace('B', 'C', CaseSensitivity::CaseInsensitive).Compare("aaCCaaCC") == 0, L"(Char, Char) case insensitive", LINE_INFO());

			// (String, String) case sensitive
			Assert::IsTrue(string.Replace("aa", "AA").Compare("AACCAACC") == 0, L"(String, String) case sensitive", LINE_INFO());

			// (String, String) case insensitive
			Assert::IsTrue(string.Replace("aacc", "bbee", CaseSensitivity::CaseInsensitive).Compare("bbeebbee") == 0, L"(String, String) case insensitive", LINE_INFO());
		}

		TEST_METHOD(StringSubstringTest)
		{
			// variables
			String string("ABCdef");

			// (int) substring
			Assert::IsTrue(string.Substring(2).Compare("Cdef") == 0, L"(int) substring", LINE_INFO());

			// (int, int) substring
			Assert::IsTrue(string.Substring(2, 2).Compare("Cd") == 0, L"(int) substring", LINE_INFO());
		}

		TEST_METHOD(StringToLowerTest)
		{
			// variables
			String string("ABCdef");

			// test
			Assert::IsTrue(string.ToLower().Compare("abcdef") == 0, L"to lower", LINE_INFO());
		}

		TEST_METHOD(StringToUpperTest)
		{
			// variables
			String string("ABCdef");

			// test
			Assert::IsTrue(string.ToUpper().Compare("ABCDEF") == 0, L"to upper", LINE_INFO());
		}

		TEST_METHOD(StringSplitTest)
		{
			// variables
			String string("ABCDABCDABCD");
			Vector<Char> delimiter = { 'C' };
			Vector<String> result;

			// test
			result = string.Split(delimiter);
			Assert::IsTrue(result.Length == 4);
			Assert::IsTrue(result[0] == "AB");
			Assert::IsTrue(result[1] == "DAB");
			Assert::IsTrue(result[2] == "DAB");
			Assert::IsTrue(result[3] == "D");

			// test
			result = string.Split(delimiter, 2);
			Assert::IsTrue(result.Length == 2);
			Assert::IsTrue(result[0] == "AB");
			Assert::IsTrue(result[1] == "DABCDABCD");

			// test
			delimiter = { 'A', 'B' };
			result = string.Split(delimiter);
			Assert::IsTrue(result.Length == 7);
			Assert::IsTrue(result[0] == "");
			Assert::IsTrue(result[1] == "");
			Assert::IsTrue(result[2] == "CD");
			Assert::IsTrue(result[3] == "");
			Assert::IsTrue(result[4] == "CD");
			Assert::IsTrue(result[5] == "");
			Assert::IsTrue(result[6] == "CD");

			// test
			result = string.Split(delimiter, 3);
			Assert::IsTrue(result.Length == 3);
			Assert::IsTrue(result[0] == "");
			Assert::IsTrue(result[1] == "");
			Assert::IsTrue(result[2] == "CDABCDABCD");
		}

		TEST_METHOD(StringSplitStringTest)
		{
			// variables
			String string("ABCDABCDABCD");
			String delimiter = "C";
			Vector<String> result;

			// test
			result = string.Split(delimiter);
			Assert::IsTrue(result.Length == 4);
			Assert::IsTrue(result[0] == "AB");
			Assert::IsTrue(result[1] == "DAB");
			Assert::IsTrue(result[2] == "DAB");
			Assert::IsTrue(result[3] == "D");

			// test
			result = string.Split(delimiter, 2);
			Assert::IsTrue(result.Length == 2);
			Assert::IsTrue(result[0] == "AB");
			Assert::IsTrue(result[1] == "DABCDABCD");

			// test
			delimiter = "AB";
			result = string.Split(delimiter);
			Assert::IsTrue(result.Length == 4);
			Assert::IsTrue(result[0] == "");
			Assert::IsTrue(result[1] == "CD");
			Assert::IsTrue(result[2] == "CD");
			Assert::IsTrue(result[3] == "CD");

			// test
			result = string.Split(delimiter, 3);
			Assert::IsTrue(result.Length == 3);
			Assert::IsTrue(result[0] == "");
			Assert::IsTrue(result[1] == "CD");
			Assert::IsTrue(result[2] == "CDABCD");
		}

		TEST_METHOD(StringSplitNoEmptyTest)
		{
			// variables
			String string("ABCDABCDABCD");
			Vector<Char> delimiter = { 'C' };
			Vector<String> result;

			// test
			result = string.Split(delimiter, StringSplitOptions::RemoveEmptyEntries);
			Assert::IsTrue(result.Length == 4);
			Assert::IsTrue(result[0] == "AB");
			Assert::IsTrue(result[1] == "DAB");
			Assert::IsTrue(result[2] == "DAB");
			Assert::IsTrue(result[3] == "D");

			// test
			result = string.Split(delimiter, 2, StringSplitOptions::RemoveEmptyEntries);
			Assert::IsTrue(result.Length == 2);
			Assert::IsTrue(result[0] == "AB");
			Assert::IsTrue(result[1] == "DABCDABCD");

			// test
			delimiter = { 'A', 'B' };
			result = string.Split(delimiter, StringSplitOptions::RemoveEmptyEntries);
			Assert::IsTrue(result.Length == 3);
			Assert::IsTrue(result[0] == "CD");
			Assert::IsTrue(result[1] == "CD");
			Assert::IsTrue(result[2] == "CD");

			// test
			result = string.Split(delimiter, 3, StringSplitOptions::RemoveEmptyEntries);
			Assert::IsTrue(result.Length == 3);
			Assert::IsTrue(result[0] == "CD");
			Assert::IsTrue(result[1] == "CD");
			Assert::IsTrue(result[2] == "BCD");
		}

		TEST_METHOD(StringOperatorTest)
		{
			// variables
			String string("ABCdef");

			Assert::IsTrue(string != "a", L"!=", LINE_INFO());
			Assert::IsFalse(string == "a", L"!=", LINE_INFO());

			Assert::IsTrue((string + "GHI") == "ABCdefGHI", L"+", LINE_INFO());

			string += "GHI";
		}
	};
}