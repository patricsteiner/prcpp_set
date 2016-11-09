#include "stdafx.h"
#include <iostream>
#include "../MySet/MySet.h"

using namespace std;

int main() {
	const int set3[] = { 1,2,3 };
	const int set4[] = { 2,3,4 };
	Set s = Set::difference(Set(set3, sizeof(set3) / sizeof(int)),
		Set(set4, sizeof(set4) / sizeof(int)));
	cout << s << endl;
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
