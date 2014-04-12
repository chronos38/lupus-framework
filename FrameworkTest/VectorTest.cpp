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
			Assert::AreEqual(8, (int)Vector<int>(8).Length, L"Vector(int)", LINE_INFO());
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

		TEST_METHOD(VectorAddTest)
		{
			// variables
			Vector<int> vec;

			// add 1
			vec.Add(1);
			Assert::AreEqual(1, (int)vec.Length, L"", LINE_INFO());
			Assert::AreEqual(1, vec[0], L"", LINE_INFO());

			// add 2
			vec.Add(2);
			Assert::AreEqual(2, (int)vec.Length, L"", LINE_INFO());
			Assert::AreEqual(1, vec[0], L"", LINE_INFO());
			Assert::AreEqual(2, vec[1], L"", LINE_INFO());

			// add 3
			vec.Add(3);
			Assert::AreEqual(3, (int)vec.Length, L"", LINE_INFO());
			Assert::AreEqual(1, vec[0], L"", LINE_INFO());
			Assert::AreEqual(2, vec[1], L"", LINE_INFO());
			Assert::AreEqual(3, vec[2], L"", LINE_INFO());
		}

		TEST_METHOD(VectorFrontBackTest)
		{
			// variables
			Vector<int> vec({ 1, 2, 3 });

			// front
			Assert::AreEqual(1, vec.Front(), L"", LINE_INFO());
			// back
			Assert::AreEqual(3, vec.Back(), L"", LINE_INFO());
		}

		TEST_METHOD(VectorClearTest)
		{
			// variables
			Vector<int> vec({ 1, 2, 3 });

			// clear
			vec.Clear();

			Assert::AreEqual(0, (int)vec.Length, L"", LINE_INFO());

			try {
				vec[0];
			} catch (ArgumentOutOfRangeException&) {
			}
		}

		TEST_METHOD(VectorContainsTest)
		{
			// variables
			Vector<int> vec({ 1, 2, 3 });

			// contains
			Assert::IsTrue(vec.Contains(1), L"", LINE_INFO());
			Assert::IsTrue(vec.Contains(2), L"", LINE_INFO());
			Assert::IsTrue(vec.Contains(3), L"", LINE_INFO());
			Assert::IsFalse(vec.Contains(4), L"", LINE_INFO());
		}

		TEST_METHOD(VectorCopyToTest)
		{
			// variables
			Vector<int> source({ 1, 2, 3 });
			Vector<int> target(6);

			// copy
			source.CopyTo(target, 0);
			Assert::AreEqual(1, target[0], L"", LINE_INFO());
			Assert::AreEqual(2, target[1], L"", LINE_INFO());
			Assert::AreEqual(3, target[2], L"", LINE_INFO());

			// copy
			source.CopyTo(0, target, 3, 3);
			Assert::AreEqual(1, target[0], L"", LINE_INFO());
			Assert::AreEqual(2, target[1], L"", LINE_INFO());
			Assert::AreEqual(3, target[2], L"", LINE_INFO());
			Assert::AreEqual(1, target[3], L"", LINE_INFO());
			Assert::AreEqual(2, target[4], L"", LINE_INFO());
			Assert::AreEqual(3, target[5], L"", LINE_INFO());
		}

		TEST_METHOD(VectorInsertTest)
		{
			// variables
			Vector<int> vec({ 1, 2, 3 });

			// insert
			vec.Insert(0, 4);
			Assert::AreEqual(4, vec[0], L"", LINE_INFO());

			vec.Insert(1, 5);
			Assert::AreEqual(5, vec[1], L"", LINE_INFO());

			vec.Insert(2, 6);
			Assert::AreEqual(6, (int)vec.Length, L"", LINE_INFO());
			Assert::AreEqual(4, vec[0], L"", LINE_INFO());
			Assert::AreEqual(5, vec[1], L"", LINE_INFO());
			Assert::AreEqual(6, vec[2], L"", LINE_INFO());
			Assert::AreEqual(1, vec[3], L"", LINE_INFO());
			Assert::AreEqual(2, vec[4], L"", LINE_INFO());
			Assert::AreEqual(3, vec[5], L"", LINE_INFO());
		}

		TEST_METHOD(VectorRemoveAtTest)
		{
			// variables
			Vector<int> vec({ 1, 2, 3 });

			// remove
			Assert::IsTrue(vec.RemoveAt(1), L"", LINE_INFO());
			Assert::AreEqual(2, (int)vec.Length, L"", LINE_INFO());
			Assert::AreEqual(1, vec[0], L"", LINE_INFO());
			Assert::AreEqual(3, vec[1], L"", LINE_INFO());

			Assert::IsFalse(vec.RemoveAt(3), L"", LINE_INFO());
		}

		TEST_METHOD(VectorResizeTest)
		{
			// variables
			Vector<int> vec(8);

			// resize
			vec.Resize(4);
			Assert::AreEqual(4, (int)vec.Length, L"", LINE_INFO());
			Assert::AreEqual(8, (int)vec.Capacity, L"", LINE_INFO());

			// resize
			vec.Resize(16);
			Assert::AreEqual(16, (int)vec.Length, L"", LINE_INFO());
			Assert::AreEqual(16, (int)vec.Capacity, L"", LINE_INFO());
		}

		TEST_METHOD(VectorShrinkTest)
		{
			// variables
			Vector<int> vec({ 1, 2, 3 });

			// shrink
			vec.Resize(100);
			vec.Resize(3);
			vec.ShrinkToFit();
			Assert::AreEqual(3, (int)vec.Capacity, L"", LINE_INFO());
		}

		TEST_METHOD(VectorOperatorTest)
		{
			// variables
			Vector<int> source({ 1, 2, 3 });
			Vector<int> copy, move, sequ;

			// operator= copy
			copy = source;
			Assert::AreEqual(3, (int)copy.Length, L"", LINE_INFO());
			Assert::AreEqual(1, copy[0], L"", LINE_INFO());
			Assert::AreEqual(2, copy[1], L"", LINE_INFO());
			Assert::AreEqual(3, copy[2], L"", LINE_INFO());

			// operator= move
			move = std::move(source);
			Assert::AreEqual(0, (int)source.Length, L"", LINE_INFO());
			Assert::AreEqual(3, (int)move.Length, L"", LINE_INFO());
			Assert::AreEqual(1, move[0], L"", LINE_INFO());
			Assert::AreEqual(2, move[1], L"", LINE_INFO());
			Assert::AreEqual(3, move[2], L"", LINE_INFO());

			// TODO: add sequence operator=
		}
	};
}
