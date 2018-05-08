/*
 * double.hpp
 *
 *  Created on: 8 maj 2018
 *      Author: SERAGUD
 */

#ifndef INCLUDE_DOUBLE_HPP_
#define INCLUDE_DOUBLE_HPP_

#include <stdint.h>
#include "object.hpp"

class Int;

class String;

class Double: public Object {
public:
	double value;

	constexpr Double() :
			value(0) {
	}

	constexpr Double(double v) :
			value(v) {
	}

	Double operator+(Double other) const {
		return Double(value + other.value);
	}

	Double operator-(Double other) const {
		return Double(value - other.value);
	}

	Double operator*(Double other) const {
		return Double(value * other.value);
	}

	Double operator/(Double other) const {
		return Double(value / other.value);
	}

	Double operator%(Double other) const {
		return Double(uint64_t(value) % uint64_t(other.value));
	}

	Double operator+(Int other) const {
		return Double(value + other.value);
	}

	Double operator-(Int other) const {
		return Double(value - other.value);
	}

	Double operator*(Int other) const {
		return Double(value * other.value);
	}

	Double operator/(Int other) const {
		return Double(value / other.value);
	}

	Double operator%(Int other) const {
		return Double(uint64_t(value) % uint64_t(other.value));
	}

	Double sqrt() const;

	Int toInt() const;

	Reference<String> toString() const;

	const Type runtimeType() const;

	static const Type xaneType;

	static Double init(double value);
};

#endif /* INCLUDE_DOUBLE_HPP_ */
