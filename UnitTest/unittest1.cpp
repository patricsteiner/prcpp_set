#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MySet/MySet.h"
#include "../MySet/OrderedSet.h"
//#include "../MySet/OrderedSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(TestMySet)
	{
	public:

		TEST_METHOD(Creation)
		{
			Set s1;
			Set s11(s1);
			const int set2[] = { 1,2,3 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			Set s21(s2);
			Set s22 = s2;
			const int set3[] = { 4,5,5,6 };
			Set s3(set3, sizeof(set3) / sizeof(int));
		}

		TEST_METHOD(Contains)
		{
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			Assert::IsTrue(s1.contains(2));
			Assert::IsFalse(s1.contains(0));
			Assert::IsFalse(Set().contains(1));

			const int set2[] = { 2,1 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			Assert::IsTrue(s1.containsAll(s2));
			Assert::IsFalse(s2.containsAll(s1));
			Assert::IsFalse(Set().containsAll(s1));
			Assert::IsTrue(s1.containsAll(Set()));
		}

		TEST_METHOD(Empty)
		{
			Assert::IsTrue(Set().isEmpty());

			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			Assert::IsFalse(s1.isEmpty());
		}

		TEST_METHOD(Size)
		{
			Assert::IsTrue(Set().size() == 0);

			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			Assert::IsTrue(s1.size() == 3);
		}

		TEST_METHOD(Merge)
		{
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,2,4 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			const int set3[] = { 1,2,3,4 };
			Set s3(set3, sizeof(set3) / sizeof(int));

			Assert::IsTrue(Set::merge(s1, s2) == s3);
			Assert::IsTrue(Set::merge(s1, Set()) == s1);
			Assert::IsTrue(Set::merge(Set(), s1) == s1);
		}

		TEST_METHOD(Difference)
		{
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,2,4 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			const int set3[] = { 1 };
			Set s3(set3, sizeof(set3) / sizeof(int));
			const int set4[] = { 4 };
			Set s4(set4, sizeof(set4) / sizeof(int));

			Assert::IsTrue(Set::difference(s1, s2) == s3);
			Assert::IsTrue(Set::difference(s2, s1) == s4);
			Assert::IsTrue(Set::difference(Set(), s1) == Set());
			Assert::IsTrue(Set::difference(s1, Set()) == s1);
		}

		TEST_METHOD(Intersect)
		{
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,2,4 };
			Set s2(set2, sizeof(set2) / sizeof(int));

			Assert::IsTrue(Set::intersection(s1, s2) == Set::intersection(s2, s1));
			Assert::IsTrue(Set::intersection(Set(), s1) == Set());
			Assert::IsTrue(Set::intersection(s1, Set()) == Set());
		}

		TEST_METHOD(MoveSemantics)
		{
			// test move intersection
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,2,4 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			const int set3[] = { 2,3 };
			Set s3(set3, sizeof(set3) / sizeof(int));
			Assert::IsTrue(Set::intersection(s1, std::move(s2)) == s3);
			Assert::IsTrue(s2 == s3);
			Assert::IsTrue(s2.size() == s3.size());

			// test move difference
			// s1 und s3 sollten nicht veraendert worden sein, lediglich s2
			const int set4[] = { 1 };
			Set s4(set4, sizeof(set4) / sizeof(int));
			Assert::IsTrue(Set::difference(std::move(s1), std::move(s3)) == s4);
			Assert::IsTrue(s1 == s4);
			Assert::IsTrue(s1.size() == s4.size());
		}
	};

	TEST_CLASS(TestOrderedSet)
	{
	public:

		TEST_METHOD(Creation)
		{
			OrderedSet s1;
			OrderedSet s11(s1);
			const int set2[] = { 1,2,3 };
			OrderedSet s2(set2, sizeof(set2) / sizeof(int));
			OrderedSet s21(s2);
			OrderedSet s22 = s2;
			const int set3[] = { 4,5,5,6 };
			OrderedSet s3(set3, sizeof(set3) / sizeof(int));
		}

		TEST_METHOD(Contains)
		{
			const int set1[] = { 1,2,3 };
			OrderedSet s1(set1, sizeof(set1) / sizeof(int));
			Assert::IsTrue(s1.contains(2));
			Assert::IsFalse(s1.contains(0));
			Assert::IsFalse(OrderedSet().contains(1));

			const int set2[] = { 2,1 };
			OrderedSet s2(set2, sizeof(set2) / sizeof(int));
			Assert::IsTrue(s1.containsAll(s2));
			Assert::IsFalse(s2.containsAll(s1));
			Assert::IsFalse(OrderedSet().containsAll(s1));
			Assert::IsTrue(s1.containsAll(OrderedSet()));
		}

		TEST_METHOD(getSmaller)
		{
			const int set1[] = { 4,5,6,1,2,3 };
			OrderedSet s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 1,2,3 };
			OrderedSet s2(set2, sizeof(set2) / sizeof(int));
			OrderedSet s3 = s1.getSmaller(4);
			Assert::IsTrue(s3.contains(1));
			Assert::IsTrue(s3.contains(2));
			Assert::IsTrue(s3.contains(3));
			Assert::IsFalse(s3.contains(4));
			Assert::IsTrue(s1.containsAll(s2));
			Assert::IsTrue(s3.containsAll(s2) && s3.size() == 3);
		}

		TEST_METHOD(getLarger)
		{
			const int set1[] = { 4,5,6,1,2,3 };
			OrderedSet s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 5,6 };
			OrderedSet s2(set2, sizeof(set2) / sizeof(int));
			OrderedSet s3 = s1.getLarger(4);
			Assert::IsTrue(s3.contains(5));
			Assert::IsTrue(s3.contains(6));
			Assert::IsFalse(s3.contains(4));
			Assert::IsTrue(s1.containsAll(s2));
			Assert::IsTrue(s3.containsAll(s2) && s3.size() == 2);
		}

		TEST_METHOD(merge) {
			const int set1[] = { 1,2,3 };
			OrderedSet s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,4,5 };
			OrderedSet s2(set2, sizeof(set2) / sizeof(int));
			OrderedSet s3 = Set::merge(s1, s2);
			const int set4[] = { 1,2,3,4,5 };
			OrderedSet s4(set4, sizeof(set4) / sizeof(int));
			Assert::IsTrue(s3.containsAll(s4) && s3.size() == 5);
		}
	};

}
