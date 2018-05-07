/*
 * int.cpp
 *
 *  Created on: 4 maj 2018
 *      Author: SERAGUD
 */

#include "core.hpp"

#include <stdio.h>
#include <math.h>

using namespace std;

const Type Int::xaneType("Xane", "Core", "Int");

Int Int_init(uint64_t val) {
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
	snprintf(chars, size + 1, "%I64u", value);
	return String_init_fromBytes(chars, size);
}

const Type Int::runtimeType() const {
	return xaneType;
}
