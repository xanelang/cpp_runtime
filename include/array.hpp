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

template<typename ElementType>
class Iterator;

template<typename ElementType>
struct Iterable: Object {
	virtual Iterator<ElementType> iterator() = 0;

	virtual Int length() = 0;

	virtual bool isEmpty() = 0;

	virtual bool isNotEmpty() = 0;

	virtual ElementType first() = 0;

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
class Array: virtual public Iterable<ElementType> {
	ElementType _elements[size];
public:
	Array(initializer_list<ElementType> elements) {
		// TODO check if elements size is size
		auto it = elements.begin();
		for (uint64_t i = 0; i < size; i++) {
			_elements[i] = *it++;
		}
	}

	Int length() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	bool isNotEmpty() {
		return size != 0;
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

template<typename ElementType>
class Iterator: public Object {
	Iterable<ElementType>* _iterable;

	uint64_t _index;
public:
	Iterator(): _iterable(nullptr), _index(0) {

	}

	Iterator(Iterable<ElementType>* array, uint64_t start) :
			_iterable(array), _index(start) {
	}

	Iterator(const Iterator& other): _iterable(other._iterable), _index(other._index) {

	}

	Iterator(const Iterator&& other): _iterable(other._iterable), _index(other._index) {

	}

	Iterator& operator=(const Iterator& other) {
		_iterable = other._iterable;
		_index = other._index;
		return *this;
	}

	Iterator& operator=(const Iterator&& other) {
		_iterable = other._iterable;
		_index = other._index;
		return *this;
	}

	Bool hasCurrent() {
		return _iterable->length() > _index;
	}

	Bool hasNext() {
		return _iterable->length() > (_index + 1);
	}

	ElementType current() {
		// TODO throw if _list has been modified
		return _iterable->get(_index);
	}

	Bool moveNext() {
		// TODO throw if _list has been modified
		if (_iterable->length() <= (_index + 1)) {
			return false;
		}
		_index++;
		return true;
	}

	const Type runtimeType() {
		return xaneType;
	}

	Reference<String> toString() {
		// TODO
		return Reference<String>(String::init_fromLiteral("Iterator"));
	}

	static const Type xaneType;
};

template<typename ElementType>
const Type Iterator<ElementType>::xaneType("Xane", "Core", "Iterator");

#endif /* INCLUDE_ARRAY_HPP_ */
