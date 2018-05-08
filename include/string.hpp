/*
 * string.hpp
 *
 *  Created on: 8 maj 2018
 *      Author: SERAGUD
 */

#ifndef INCLUDE_STRING_HPP_
#define INCLUDE_STRING_HPP_

#include "object.hpp"

class String;

#define NewROString(x) CString(x, sizeof(x))

class CString: public Object {
public:
	char const * const chars;

	const Int length;

	constexpr CString(char const * const ch, uint64_t length) :
			chars(ch), length(length) {
	}

	char operator[](uint64_t i) const;

	char operator[](Int i) const;

	char get(uint64_t index) const;

	char get(Int index) const;

	bool isEqual(const CString& other) const;

	Reference<String> concat(const CString other) const;

	Reference<String> concat(Reference<String> other) const;

	static const Type xaneType;

	friend class String;

	Reference<String> toString() const;

	const Type runtimeType() const;
};


class String: public ReferencedObject {
public:
	String(uint64_t length);

	String(char const* bytes, uint64_t length);

	String(char const* bytes, Int length);

	String(const String& a, const String& b);

	String(const String& a, const Reference<String> b);

	String(const CString& other);

	~String();

	Int length;

	char* const chars;

	char operator[](uint64_t i) const;

	char operator[](Int i) const;

	char get(uint64_t index) const;

	char get(Int index) const;

	void set(uint64_t index, char val);

	void set(Int index, char val);

	void replaceRange(uint64_t start, uint64_t length, char const * val);

	void replaceRange(uint64_t start, Reference<String> string);

	void replaceRange(uint64_t start, CString& string);

	bool isEqual(Reference<String>);

	Reference<String> concat(Reference<String> other);

	Reference<String> concat(CString& other);

	Reference<String> concat(Object& other);

	Reference<String> concat(Object&& other);

	Reference<String> concat(Reference<ReferencedObject> other);

	static const Type xaneType;

	friend class CString;

	Reference<String> toString();

	const Type runtimeType() const;

	void deinit();

	static Reference<String> init_fromBytes(char const * chars, Int size);

	static Reference<String> init_fromLiteral(char const * chars);
};

#endif /* INCLUDE_STRING_HPP_ */
