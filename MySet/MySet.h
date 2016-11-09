#pragma once
#include <memory>
#include <iostream>

using namespace std;
class Set {
protected:
	shared_ptr<int> m_values;
	size_t m_size;

	Set(const size_t size) : m_values(new int[size], default_delete<int[]>()), m_size(0) {
		cout << "private-ctor " << endl;
	}

	// geschützte Instanzmethoden
	int *begin() const; // gibt einen Zeiger auf das erste Element // der Menge zurueck (nullptr falls leer)
	int& operator[](size_t i) const; // gibt das i-te Element des Mengen-Arrays // zurueck
	Set merge(const Set& set) const; // gibt als neue Menge die Vereinigungs- // menge dieser Menge mit set zurueck
	Set difference(const Set& set) const; // gibt als neue Menge die Differenzmenge // zwischen set und dieser Menge // (set \ this) zurueck
	Set intersection(const Set& set) const; // gibt als neue Menge die Schnittmenge // dieser Menge mit set zurueck

public:
	Set() : m_size(0) {
		cout << "default-ctor " << endl;
	}

	Set(const Set& set) : m_values(set.m_values), m_size(set.m_size) {
		cout << "copy-ctor" << endl;
	}

	Set(const int* values, const size_t size) : Set(size) {
		cout << "type-convert-ctor" << endl;
		for (size_t i = 0; i < size; i++) {
			if (!contains(*(values + i))) {
				(*this)[i] = *(values + i);
				m_size++;
			}
		}
	}

	~Set() {
		m_values.reset();
		cout << "default-dtor" << endl;
	}

	// Instanzmethoden
	bool contains(const int e) const;
	bool containsAll(const Set& set) const;
	bool isEmpty() const;
	size_t size() const;
	bool operator==(const Set& set) const { return containsAll(set) && set.containsAll((Set &) *this); }

	friend ostream& operator<<(ostream& os, const Set& s) {
		const int* const vptr = s.begin();
		os << "{";
		if (!s.isEmpty()) os << vptr[0];
		for (size_t i = 1; i < s.m_size; ++i) { os << ", " << vptr[i]; }
		os << "}";
		return os;
	}
	// Klassen-Methoden
	// Vereinigungsmenge
	static Set merge(const Set& set1, const Set& set2) { return set1.merge(set2); }
	// Differenzmenge set1\set2
	static Set difference(const Set& set1, const Set& set2) { return set2.difference(set1); }
	// Schnittmenge
	static Set intersection(const Set& set1, const Set& set2) { return set1.intersection(set2); }

	// Differenzmenge set1\set2
	static Set difference(const Set& set1, Set&& set2) { return set2.difference(move(set1)); }
	static Set difference(Set&& set1, Set&& set2) { return set2.difference(move(set1)); }
	// Schnittmenge
	static Set intersection(const Set& set1, Set&& set2) { return set1.intersection(move(set2)); }
	static Set intersection(Set&& set1, const Set& set2) { return set2.intersection(move(set1)); }
	static Set intersection(Set&& set1, Set&& set2) { return set1.intersection(move(set2)); }
};