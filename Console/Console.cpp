#include "stdafx.h"
#include <iostream>
#include "../MySet/MySet.h"
#include "../MySet/OrderedSet.h"

using namespace std;

int main() {
	const int set1[] = { 777, 1,2,3 };
	OrderedSet s1(set1, sizeof(set1) / sizeof(int));
	const int set2[] = { -900, -2,-1,0,1,2,3, 888 };
	OrderedSet s2(set2, sizeof(set2) / sizeof(int));
	OrderedSet s3 = Set::merge(s1, s2);
	cout << "YYYYYYY "  << s3 << endl;
	return 0;
}

int main4() {
	const int set1[] = { 4,5,6,1,2,3 };
	OrderedSet s1(set1, sizeof(set1) / sizeof(int));
	const int set2[] = { 1,2,3 };
	OrderedSet s2 = s1.getSmaller(4);
	OrderedSet s3 = s1.getLarger(4);
	cout << "XXX" << s2 << endl;
	cout << "XXX" << s3 << endl;
	cout << boolalpha << s2.contains(1) << endl;
	return 0;
}

int main3() {
	const int set3[] = { 1,2,3 };
	const int set4[] = { 2,3,4 };
	Set s = Set::difference(Set(set3, sizeof(set3) / sizeof(int)),
		Set(set4, sizeof(set4) / sizeof(int)));
	cout << s << endl;
	return 0;
}

int main2() {
	Set s1;
	Set s11(s1);
	const int set2[] = { 1,2,3 };
	Set s2(set2, sizeof(set2) / sizeof(int));
	Set s21(s2);
	Set s22 = s2;
	return 0;
}
