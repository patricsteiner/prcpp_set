#pragma once
#include <algorithm>
#include "MySet.h"
class OrderedSet : public Set {
protected:
	size_t m_start;
	virtual int *begin() const override;
	virtual Set merge(const Set& set) const override;
public:
	OrderedSet() : Set(), m_start(0) {
		cout << "OrderedSet: default-ctor" << endl;
	}

	OrderedSet(const size_t size) : Set(size), m_start(0) {}

	OrderedSet(const Set& set) : Set(set), m_start(0) {
		cout << "OrderedSet: copy-ctor" << endl;
	}

	OrderedSet(const int* values, const size_t size) : Set(values, size), m_start(0) {
		cout << "OrderedSet: type-convert-ctor" << endl;
		int * beg = begin(); std::sort(beg, beg + m_size);
	}

	OrderedSet(OrderedSet set, int start, int size) : OrderedSet(set) {
		cout << "OrderedSet: Special-ctor" << endl;
		m_size = size;
		m_start = start;
	}

	~OrderedSet() {
		cout << "OrderedSet: default-dtor" << endl;
		m_values.reset();
	}

	// gibt eine neue Menge zurueck, die alle Elemente von this enthaelt,
	// die (strikt) kleiner als x sind
	OrderedSet getSmaller(const int x) const;
	// gibt eine neue Menge zurueck, die alle Elemente von this enthaelt,
	// die (strikt) groesser als x sind
	OrderedSet getLarger(const int x) const;

};

