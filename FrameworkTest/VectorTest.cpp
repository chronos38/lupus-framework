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
#include "..\Framework\String.hpp"
#include "..\Framework\Exception.hpp"
#include "..\Framework\Vector.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Lupus;
using namespace Lupus::System;

namespace FrameworkTest {
	TEST_CLASS(VectorTest)
	{
		TEST_METHOD(VectorConstructorTest)
		{
			// variables
			Vector<int> vec1({ 1, 1, 1 });
			Vector<int> vec2(vec1);
			Vector<int> vec3(dynamic_cast<ISequence<int>&>(vec1));

			// empty Vector
			Assert::AreEqual(0, (int)Vector<int>().Length, L"Vector()", LINE_INFO());

			// filled vector
			Assert::AreEqual(0, (int)Vector<int>(8).Length, L"Vector(int)", LINE_INFO());
			Assert::AreEqual(8, (int)Vector<int>(8).Capacity, L"Vector(int)", LINE_INFO());

			// initializer list
			Assert::AreEqual(3, (int)Vector<int>({ 1, 1, 1 }).Length, L"Vector(init)", LINE_INFO());
			Assert::AreEqual(3, (int)Vector<int>({ 1, 1, 1 }).Capacity, L"Vector(init)", LINE_INFO());

			// copy vector
			Assert::AreEqual(3, (int)Vector<int>(Vector<int>({ 1, 1, 1 })).Length, L"Vector(copy)", LINE_INFO());
			Assert::AreEqual(3, (int)Vector<int>(Vector<int>({ 1, 1, 1 })).Capacity, L"Vector(copy)", LINE_INFO());

			for (int i = 0; i < 3; i++) {
				Assert::IsTrue(vec1[i] == vec2[i], L"Vector(copy)", LINE_INFO());
				Assert::IsTrue(vec1[i] == vec3[i], L"Vector(sequence)", LINE_INFO());
			}
		}
	};
}