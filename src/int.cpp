/*
 * int.cpp
 *
 *  Created on: 4 maj 2018
 *      Author: SERAGUD
 */

#include "core.hpp"

#include <stdio.h>
#include <cmath>

using namespace std;

Int Int::init(uint64_t val) {
	return Int(val);
}

Double Int::sqrt() const {
	return Double(std::sqrt(value));
}

Double Int::toDouble() const {
	return Double(value);
}

Reference<String> Int::toString() const {
	uint16_t size = std::log10(value) + 1;
	char chars[size + 1];
	snprintf(chars, size + 1, "%lu", value);
	return String::init_fromBytes(chars, size);
}

const Type Int::runtimeType() const {
	return xaneType;
}

const Type Int::xaneType = Type("Xane", "Core", "Int");
