#include "OrderedSet.h"

int * OrderedSet::begin() const {
	return Set::begin() + m_start;
}

OrderedSet OrderedSet::getSmaller(const int x) const {
	int i = 0;
	while (x > (*this)[i]) i++;
	return OrderedSet(*this, 0, i);
}

OrderedSet OrderedSet::getLarger(const int x) const {
	int i = 0;
	while (x >= (*this)[i]) i++;
	return OrderedSet(*this, i, m_size - i);
}