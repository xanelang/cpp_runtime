/*
 * bool.hpp
 *
 *  Created on: 8 maj 2018
 *      Author: SERAGUD
 */

#ifndef INCLUDE_BOOL_HPP_
#define INCLUDE_BOOL_HPP_

#include "object.hpp"

class String;

struct Bool: public Object {
	bool value;

	constexpr Bool(bool value) :
			value(value) {
	}

	explicit operator bool() const {
		return value;
	}

	Reference<String> toString() const;

	const Type runtimeType() const;

	static const Type xaneType;

	static Bool init(bool value);
};

#endif /* INCLUDE_BOOL_HPP_ */
