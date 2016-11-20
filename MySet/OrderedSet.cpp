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

Set OrderedSet::merge(const Set & set) const {
	const OrderedSet* os = dynamic_cast<const OrderedSet*>(&set);
	if (!os) return Set::merge(set);
	else {
		int* newvals = new int[m_size + os->m_size];
		int* p1 = begin();
		int* p2 = os->begin();
		int i = 0, j = 0, k = 0;
		while (j < m_size || k < os->m_size) {
			if (p1[j] < p2[k]) newvals[i] = p1[j++];
			else if (p1[j] == p2[k]) { newvals[i] = p1[j]; j++; k++; }
			else newvals[i] = p2[k++];
			i++;
		}
		return OrderedSet(newvals, i);
	}
}