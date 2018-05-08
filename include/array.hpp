/*
 * array.hpp
 *
 *  Created on: 8 maj 2018
 *      Author: SERAGUD
 */

#ifndef INCLUDE_ARRAY_HPP_
#define INCLUDE_ARRAY_HPP_

#include "core.hpp"
#include <algorithm>

using namespace std;

template<typename ElementType, size_t size>
class ArrayIterator;

template<typename ElementType, size_t size>
class FixedSizedContainer: public Object {
public:
	virtual Int length() = 0;

	virtual ElementType first() = 0;

	virtual ArrayIterator<ElementType, size> iterator() = 0;

	virtual ElementType last() = 0;

	// TODO asMap

	// TODO fillRange

	// TODO slice

	virtual Int indexOf(ElementType element) = 0;

	virtual Int lastIndexOf(ElementType element) = 0;

	virtual void set(uint64_t index, ElementType el) = 0;

	virtual ElementType get(uint64_t index) = 0;
};

template<typename ElementType, size_t size>
class Array: virtual public FixedSizedContainer<ElementType, size> {
	ElementType _elements[size];
public:
	Array(initializer_list<ElementType> elements) {
		// TODO check if elements size is size
		auto it = elements.begin();
		for(uint64_t i = 0; i < size; i++) {
			_elements[i] = *it++;
		}
	}

	Int length() {
		return size;
	}

	ElementType first() {
		// TODO throw or return optional?
		return _elements[0];
	}

	ArrayIterator<ElementType, size> iterator() {
		return ArrayIterator<ElementType, size>(*this, 0, size - 1);
	}

	ElementType last() {
		return _elements[size - 1];
	}

	Int indexOf(ElementType element) {
		for (uint64_t i = 0; i < size; i++) {
			ElementType& el = _elements[i];
			if (el == element) {
				return i;
			}
		}
		// TODO change return type to signed integer?
		return -1;
	}

	Int lastIndexOf(ElementType element) {
		for (uint64_t i = size - 1; size >= 0; i--) {
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

	const Type runtimeType() {
		return xaneType;
	}

	Reference<String> toString() {
		// TODO
		return Reference<String>(String::init_fromLiteral("Array"));
	}

	static const Type xaneType;
};

template<typename ElementType, size_t size>
const Type Array<ElementType, size>::xaneType = Type("Xane", "Core", "Array");

template<typename ElementType, size_t size>
class ArrayIterator: public Object {
	Array<ElementType, size>& _array;

	uint64_t _index;

	uint64_t _last;
public:
	ArrayIterator(Array<ElementType, size>& array, uint64_t start,
			uint64_t last) :
			_array(array), _index(start), _last(last) {
	}

	ElementType current() {
		// TODO throw if _list has been modified
		return _array.get(_index);
	}

	Bool moveNext() {
		// TODO throw if _list has been modified
		if (_index >= _last) {
			return false;
		}
		_index++;
		return true;
	}

	Bool hasNext() {
		// TODO throw if _list has been modified
		return _index < _last;
	}

	const Type runtimeType() {
		return xaneType;
	}

	Reference<String> toString() {
		// TODO
		return Reference<String>(String::init_fromLiteral("ArrayIterator"));
	}

	static const Type xaneType;
};

template<typename ElementType, size_t size>
const Type ArrayIterator<ElementType, size>::xaneType("Xane", "Core", "ArrayIterator");

#endif /* INCLUDE_ARRAY_HPP_ */
