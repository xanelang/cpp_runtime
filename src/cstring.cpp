/*
 * cstring.cpp
 *
 *  Created on: May 5, 2018
 *      Author: Issac
 */

#include "core.hpp"
#include "string.h"

char CString::operator[](uint64_t index) const {
	if (length <= index) {
		// TODO throw?
	}

	return chars[index];
}

char CString::operator[](Int index) const {
	if (length <= index) {
		// TODO throw?
	}

	return chars[index.value];
}

char CString::get(uint64_t index) const {
	if (length <= index) {
		// TODO throw?
	}

	return chars[index];
}

char CString::get(Int index) const {
	if (length <= index) {
		// TODO throw?
	}

	return chars[index.value];
}

bool CString::isEqual(const CString& other) const {
	if(length != other.length) return false;
	for(uint64_t i = 0; length > i; i++) {
		if(get(i) != other.get(i)) return false;
	}
	return true;
}

Reference<String> CString::concat(const CString other) const {
	auto string = new String(length.value + other.length.value);
	for (uint64_t i = 0; length > i; i++) {
		string->chars[i] = get(i);
	}
	for (uint64_t i = 0; other.length > i; i++) {
		string->chars[length.value + i] = other[i];
	}
	return Reference<String>(string);
}

Reference<String> CString::concat(Reference<String> other) const {
	auto string = new String(length.value + other->length.value);
	for (uint64_t i = 0; length > i; i++) {
		string->chars[i] = get(i);
	}
	for (uint64_t i = 0; other->length > i; i++) {
		string->chars[length.value + i] = other->get(i);
	}
	return Reference<String>(string);
}

Reference<String> CString::toString() const {
	return Reference<String>(new String(*this));
}

const Type CString::runtimeType() const {
	return xaneType;
}

const Type CString::xaneType("Xane", "Core", "CString");
