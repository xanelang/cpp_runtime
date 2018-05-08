/*
 * bool.cpp
 *
 *  Created on: 8 maj 2018
 *      Author: SERAGUD
 */

#include "core.hpp"

Reference<String> Bool::toString() const {
	if(value) {
		return Reference<String>(String::init_fromLiteral("true"));
	}
	return Reference<String>(String::init_fromLiteral("false"));
}

const Type Bool::runtimeType() const {
	return xaneType;
}

const Type Bool::xaneType("Xane", "Core", "Bool");

Bool Bool::init(bool value) {
	return Bool(value);
}
