#pragma once
#include "MySet.h"

int* Set::begin() const {
	return m_values.get() ? m_values.get() : nullptr;
}

int& Set::operator[](size_t i) const {
	return *(begin() + i);
}

bool Set::contains(const int e) const {
	for (size_t i = 0; i < m_size; i++) {
		if ((*this)[i] == e) return true;
	}
	return false;
}

bool Set::containsAll(const Set & set) const {
	for (size_t i = 0; i < set.size(); i++) {
		if (!contains(set[i])) return false;
	}
	return true;
}

bool Set::isEmpty() const {
	return size() == 0;
}

size_t Set::size() const {
	return m_size;
}

Set Set::merge(const Set & set) const {
	// erstelle eine neue Menge mit allen Elementen von this
	Set result(m_size + set.m_size);
	std::memcpy(result.begin(), begin(), m_size * sizeof(int));
	result.m_size = m_size;
	// fuege nur jene Elemente von set dazu, die in this noch nicht enthalten sind
	for (size_t i = 0; i < set.m_size; ++i) {
		if (!contains(set[i])) result[result.m_size++] = set[i];
	}
	return result;
}

Set Set::difference(const Set & set) const {
	int* newvalues = new int[set.size()];
	int newsize = 0;
	for (size_t i = 0; i < set.size(); ++i) {
		if (!contains(set[i])) newvalues[newsize++] = set[i];
	}
	return * new Set(newvalues, newsize);
}

Set Set::intersection(const Set & set) const {
	int* newvalues = new int[set.size()];
	int newsize = 0;
	for (size_t i = 0; i < set.size(); ++i) {
		if (contains(set[i])) newvalues[newsize++] = set[i];
	}
	return *new Set(newvalues, newsize);
}