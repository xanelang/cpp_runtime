/*
 * string.cpp
 *
 *  Created on: 4 maj 2018
 *      Author: SERAGUD
 */

#include "core.hpp"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory>
#include <string.h>

using namespace std;

const Type String::xaneType("Xane", "Core", "String");

String::String(uint64_t length) :
		length(length), chars((char *) malloc(length)) {

}

String::String(char const* bytes, uint64_t length) :
		length(length), chars((char *) malloc(length)) {
	// TODO use memcpy?
	for (uint64_t i = 0; i < length; i++) {
		chars[i] = bytes[i];
	}
}

String::String(char const* bytes, Int length) :
		length(length), chars((char *) malloc(length.value)) {
	// TODO use memcpy?
	for (uint64_t i = 0; length > i; i++) {
		chars[i] = bytes[i];
	}
}

String::String(const String& a, const String& b) :
		length(a.length + b.length), chars(
				(char *) malloc((a.length + b.length).value)) {
	// TODO use memcpy?
	for (uint64_t i = 0; a.length > i; i++) {
		chars[i] = a[i];
	}
	for (uint64_t i = 0; b.length > i; i++) {
		chars[a.length.value + i] = b[i];
	}
}

String::String(const String& a, const Reference<String> b) :
		length(a.length + b->length), chars(
				(char *) malloc((a.length + b->length).value)) {
	// TODO use memcpy?
	for (uint64_t i = 0; a.length > i; i++) {
		chars[i] = a[i];
	}
	for (uint64_t i = 0; b->length > i; i++) {
		chars[a.length.value + i] = b->get(i);
	}
}

String::String(const CString& other) :
		length(other.length), chars((char *) malloc(length.value)) {
	// TODO use memcpy?
	for (uint64_t i = 0; length > i; i++) {
		chars[i] = other[i];
	}
}

String::~String() {
	if (chars != nullptr)
		delete[] chars;
}

char String::operator[](uint64_t index) const {
	if (length <= index) {
		// TODO throw?
	}

	return chars[index];
}

char String::operator[](Int index) const {
	if (length <= index) {
		// TODO throw?
	}

	return chars[index.value];
}

char String::get(uint64_t index) const {
	if (length <= index) {
		// TODO throw?
	}

	return chars[index];
}

char String::get(Int index) const {
	if (length <= index) {
		// TODO throw?
	}

	return chars[index.value];
}

bool String::isEqual(Reference<String> other) const {
	if (length != other->length)
		return false;
	for (uint64_t i = 0; length > i; i++) {
		if (get(i) != other->get(i))
			return false;
	}
	return true;
}

Reference<String> String::concat(Reference<String> other) const {
	return Reference<String>(new String(*this, *other));
}

Reference<String> String::concat(const CString& other) const {
	auto string = new String(length.value + other.length.value);
	for (uint64_t i = 0; length > i; i++) {
		string->chars[i] = get(i);
	}
	for (uint64_t i = 0; other.length > i; i++) {
		string->chars[length.value + i] = other[i];
	}
	return Reference<String>(string);
}

Reference<String> String::concat(const Object& other) const {
	return Reference<String>(new String(*this, other.toString()));
}

Reference<String> String::concat(const Object&& other) const {
	return Reference<String>(new String(*this, other.toString()));
}

Reference<String> String::concat(const Reference<ReferencedObject> other) const {
	return Reference<String>(new String(*this, other.toString()));
}

Reference<String> String::toString() const {
	return Reference<String>(new String(*this));
}

const Type String::runtimeType() const {
	return xaneType;
}

void String::deinit() {

}

Reference<String> String_init_fromBytes(char const * bytes, uint64_t size) {
	return Reference<String>(new String(bytes, size));
}

Reference<String> String_init_fromLiteral(char const * bytes) {
	return Reference<String>(new String(bytes, strlen(bytes)));
}
