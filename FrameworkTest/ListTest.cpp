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

#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Framework\String.hpp"
#include "..\Framework\Exception.hpp"
#include "..\Framework\List.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Lupus;
using namespace Lupus::System;

namespace FrameworkTest {
	TEST_CLASS(ListTest)
	{
		TEST_METHOD(ListConstructorTest)
		{
			List<int> list1({ 1, 1, 1 });
			List<int> list2(list1);
			List<int> list3(dynamic_cast<ICollection<int>&>(list1));
			List<int> list4(std::move(list1));

			// empty list
			Assert::AreEqual(0, List<int>().Count(), L"", LINE_INFO());

			// filled list
			Assert::AreEqual(8, List<int>(8).Count(), L"", LINE_INFO());

			// initializer list
			Assert::AreEqual(3, List<int>({ 1, 1, 1 }).Count(), L"", LINE_INFO());

			// copy vector
			Assert::AreEqual(3, List<int>(List<int>({ 1, 1, 1 })).Count(), L"", LINE_INFO());

			for (int i = 0; i < 3; i++) {
				Assert::IsTrue(list2[i] == list3[i], L"", LINE_INFO());
				Assert::IsTrue(list2[i] == list4[i], L"", LINE_INFO());
			}
		}

		TEST_METHOD(ListAddTest)
		{
		}

		TEST_METHOD(ListFrontBackTest)
		{
		}

		TEST_METHOD(ListClearTest)
		{
		}

		TEST_METHOD(ListContainsTest)
		{
		}

		TEST_METHOD(ListCopyToTest)
		{
		}

		TEST_METHOD(ListInsertTest)
		{
		}

		TEST_METHOD(ListRemoveAtTest)
		{
		}

		TEST_METHOD(ListResizeTest)
		{
		}

		TEST_METHOD(ListSortTest)
		{
		}

		TEST_METHOD(ListOperatorTest)
		{
		}
	};
}
