/*
 * vector.hpp
 *
 *  Created on: 25 maj 2018
 *      Author: SERAGUD
 */

#ifndef INCLUDE_VECTOR_HPP_
#define INCLUDE_VECTOR_HPP_

#include "core.hpp"
#include "array.hpp"

using namespace std;

template<typename ElementType>
struct ReArray: Iterable<ElementType> {
	virtual void add(ElementType element) = 0;

	virtual void addAll(Iterable<ElementType>* elements) = 0;

	// TODO insert

	// TODO insertAll

	virtual void removeAt(Int index) = 0;

	virtual bool remove(ElementType element) = 0;

	// virtual void removeRange() = 0;

	virtual void clear() = 0;
};

template<typename ElementType, size_t Capacity>
class Vector: virtual public ReArray<ElementType> {
	ElementType _elements[Capacity];

	uint64_t _size = 0;

public:
	Vector() {

	}

	Vector(initializer_list<ElementType> elements) {
		_size = elements.size();
		// TODO check elements size is less than Capacity
		auto it = elements.begin();
		for(uint64_t i = 0; _size > i; i++) {
			_elements[i] = *it++;
		}
	}

	Int length() {
		return _size;
	}

	bool isEmpty() {
		return _size == 0;
	}

	bool isNotEmpty() {
		return _size != 0;
	}

	ElementType first() {
		// TODO throw or return optional?
		return _elements[0];
	}

	Iterator<ElementType> iterator() {
		return Iterator<ElementType>(this, 0);
	}

	ElementType last() {
		// TODO check if not empty
		return _elements[_size - 1];
	}

	Int indexOf(ElementType element) {
		for (uint64_t i = 0; _size > i; i++) {
			ElementType& el = _elements[i];
			if (el == element) {
				return i;
			}
		}
		// TODO change return type to signed integer?
		return -1;
	}

	Int lastIndexOf(ElementType element) {
		for (uint64_t i = _size - 1; _size >= 0; i--) {
			ElementType& el = _elements[i];
			if (el == element) {
				return i;
			}
		}
		// TODO change return type to signed integer?
		return -1;
	}

	void set(uint64_t index, ElementType el) {
		_elements[index] = el;
	}

	ElementType get(uint64_t index) {
		// TODO
		return _elements[index];
	}

	void add(ElementType element) {
		if(_size >= Capacity) {
			// TODO throw?
			return;
		}
		_elements[_size] = element;
		++_size;
	}

	void addAll(Iterable<ElementType>* elements) {
		uint64_t otherLen = elements->length().value;
		if((_size + otherLen) > Capacity) {
			// TODO throw?
			return;
		}
		for(uint64_t i = 0; otherLen > i; i++) {
			_elements[_size + i] = elements->get(i);
		}
		_size = _size + otherLen;
	}

	void removeAt(Int index) {
		// TODO check index
		for(uint64_t i = index.value; (_size - 1) > i; ++i) {
			_elements[i] = _elements[i + 1];
		}
		--_size;
	}

	bool remove(ElementType element) {
		for(uint64_t i = 0; i < _size; i++) {
			if(element == _elements[i]) {
				removeAt(i);
				return true;
			}
		}
		return false;
	}

	void clear() {
		_size = 0;
	}

	const Type runtimeType() {
		return xaneType;
	}

	Reference<String> toString() {
		// TODO
		return Reference<String>(String::init_fromLiteral("Array"));
	}

	static const Type xaneType;
};

template<typename ElementType, size_t Capacity>
const Type Vector<ElementType, Capacity>::xaneType = Type("Xane", "Core", "Vector");

#endif /* INCLUDE_VECTOR_HPP_ */
