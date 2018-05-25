/*
 * core.hpp
 *
 *  Created on: 4 maj 2018
 *      Author: SERAGUD
 */

#ifndef INCLUDE_CORE_HPP_
#define INCLUDE_CORE_HPP_

#include <stdint.h>
#include <type_traits>
#include <cstring>

#include "object.hpp"
#include "bool.hpp"
#include "int.hpp"
#include "double.hpp"
#include "string.hpp"
#include "array.hpp"
#include "vector.hpp"

void print(Reference<String> string, bool newLine = true);

void print(CString& string, bool newLine = true);

void print(CString&& string, bool newLine = true);

void print(Object* object, bool newLine);

void print(Reference<Object> object, bool newLine);

template<typename T>
Type Reference<T>::runtimeType() const {
	return T::xaneType;
}

template<typename T>
Reference<String> Reference<T>::toString() const {
	if (__rc__ == nullptr)
		return String::init_fromLiteral("null");
	return __rc__->ptr->toString();
}

#endif /* INCLUDE_CORE_HPP_ */
