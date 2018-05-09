/*
 * core.cpp
 *
 *  Created on: 4 maj 2018
 *      Author: SERAGUD
 */

#include "core.hpp"

#include <stdio.h>

void print(Reference<String> string, bool newLine) {
	if(!string.isValid()) {
		puts("null");
	}
	for (uint64_t i = 0; string->length > i; i++) {
		putchar(string->get(i));
	}
	if (newLine)
		putchar('\n');
}

void print(CString& string, bool newLine) {
	for (uint64_t i = 0; string.length > i; i++) {
		putchar(string.get(i));
	}
	if (newLine)
		putchar('\n');
}

void print(const CString&& string, bool newLine) {
	for (uint64_t i = 0; string.length > i; i++) {
		putchar(string.get(i));
	}
	if (newLine)
		putchar('\n');
}

void print(Object* object, bool newLine) {
	auto string = object->toString();
	for (uint64_t i = 0; string->length > i; i++) {
		putchar(string->get(i));
	}
	if (newLine)
		putchar('\n');
}

/*
void print(Object& object, bool newLine) {
	auto string = object.toString();
	for (uint64_t i = 0; string->length > i; i++) {
		putchar(string->get(i));
	}
	if (newLine)
		putchar('\n');
}

void print(Object&& object, bool newLine) {
	auto string = object.toString();
	for (uint64_t i = 0; string->length > i; i++) {
		putchar(string->get(i));
	}
	if (newLine)
		putchar('\n');
}
*/

void print(Reference<ReferencedObject> object, bool newLine) {
	Reference<String> string = object.toString();
	for (uint64_t i = 0; string->length > i; i++) {
		putchar(string->get(i));
	}
	if (newLine)
		putchar('\n');
}
