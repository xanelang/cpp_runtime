/*
 * int.hpp
 *
 *  Created on: 8 maj 2018
 *      Author: SERAGUD
 */

#ifndef INCLUDE_INT_HPP_
#define INCLUDE_INT_HPP_

#include <stdint.h>
#include "object.hpp"

class Double;

class String;

class Int: public Object {
public:
	uint64_t value;

	constexpr Int() :
			value(0) {
	}

	constexpr Int(uint64_t v) :
			value(v) {
	}

	Int operator+(Int other) const {
		return Int(value + other.value);
	}

	Int operator-(Int other) const {
		return Int(value - other.value);
	}

	Int operator*(Int other) const {
		return Int(value * other.value);
	}

	Int operator/(Int other) const {
		return Int(value / other.value);
	}

	Int operator%(Int other) const {
		return Int(value % other.value);
	}

	bool operator==(Int other) const {
		return value == other.value;
	}

	bool operator!=(Int other) const {
		return value != other.value;
	}

	bool operator>(Int other) const {
		return value > other.value;
	}

	bool operator<(Int other) const {
		return value < other.value;
	}

	bool operator<=(Int other) const {
		return value <= other.value;
	}

	bool operator>=(Int other) const {
		return value >= other.value;
	}

	bool operator==(uint64_t other) const {
		return value == other;
	}

	bool operator!=(uint64_t other) const {
		return value != other;
	}

	bool operator>(uint64_t other) const {
		return value > other;
	}

	bool operator<(uint64_t other) const {
		return value < other;
	}

	bool operator<=(uint64_t other) const {
		return value <= other;
	}

	bool operator>=(uint64_t other) const {
		return value >= other;
	}

	Double sqrt() const;

	Double toDouble() const;

	Reference<String> toString() const;

	const Type runtimeType() const;

	static const Type xaneType;

	static Int init(uint64_t val);
};

#endif /* INCLUDE_INT_HPP_ */
