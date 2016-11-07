#include "stdafx.h"
#include <iostream>
#include "../MySet/MySet.h"

using namespace std;
int main() {
	Set s1;
	Set s11(s1);
	const int set2[] = { 1,2,3 };
	Set s2(set2, sizeof(set2) / sizeof(int));
	Set s21(s2);
	Set s22 = s2;
	return 0;
}
