/*
 * double.cpp
 *
 *  Created on: 4 maj 2018
 *      Author: SERAGUD
 */

#include "core.hpp"

#include <stdio.h>
#include <cmath>

using namespace std;

Double Double::init(double value) {
	return Double(value);
}

Int Double::toInt() const {
	return Int(value);
}

Double Double::sqrt() const {
	return Double(std::sqrt(value));
}

Reference<String> Double::toString() const {
	uint16_t size = snprintf(NULL, 0, "%f", value);
	char chars[size];
	snprintf(chars, size, "%f", value);
	return String::init_fromBytes(chars, size - 1);
}

const Type Double::runtimeType() const {
	return xaneType;
}

const Type Double::xaneType("Xane", "Core", "Double");
