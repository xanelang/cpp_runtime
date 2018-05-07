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

class Double;

class String;

class CString;

class Type;

template<typename T>
class Reference;

class Object {
public:
	virtual ~Object() {}

	virtual const Type runtimeType() const = 0;

	virtual Reference<String> toString() const = 0;
};

class ReferencedObject: public Object {
public:
	virtual void deinit() {
	}

	virtual Reference<String> toString() const = 0;
};

template<typename T>
struct RefCount {
private:
	uint64_t sharedCount;
	uint64_t weakCount;
	T* ptr;

	friend class Reference<T>;

public:
	RefCount(T* ptr) :
			sharedCount(1), weakCount(0), ptr(ptr) {
		if (ptr == nullptr) {
			// TODO throw?
		}
	}

	void incrementShared() {
		if (sharedCount == 0) {
			// TODO throw?
			return;
		}
		sharedCount++;
	}

	void decrementShared() {
		if (sharedCount == 0) {
			// TODO throw?
			return;
		}
		if (sharedCount != 0) {
			sharedCount--;
			if (sharedCount == 0) {
				ptr->deinit();
				delete ptr;
			}
		}
		if (sharedCount == 0 && weakCount == 0) {
			delete this;
		}
	}

	void incrementWeak() {
		if (sharedCount == 0) {
			// TODO throw?
			return;
		}
		weakCount++;
	}

	void decrementWeak() {
		if (weakCount == 0) {
			return;
		}
		weakCount--;
		if (sharedCount == 0 && weakCount == 0) {
			delete this;
		}
	}
};

template<typename T>
class Reference {
private:
	RefCount<T>* __rc__;

public:
	Reference() :
			__rc__(nullptr) {
	}

	Reference(T* ptr) :
			__rc__(new RefCount<T>(ptr)) {
	}

	Reference(Reference<T>& other) :
			__rc__(other.__rc__) {
		__rc__->incrementShared();
	}

	Reference(Reference<T>&& other) :
			__rc__(other.__rc__) {
		other.__rc__ = nullptr;
	}

	~Reference() {
		clear();
	}

	void clear() {
		if (__rc__ == nullptr)
			return;
		__rc__->decrementShared();
		__rc__ = nullptr;
	}

	void operator=(Reference<T> other) {
		clear();
		other.__rc__->incrementShared();
		__rc__ = other.__rc__;
	}

	void operator=(T* other) {
		clear();
		__rc__ = new RefCount<T>(other);
	}

	bool isValid() const {
		return __rc__ != nullptr;
	}

	T& get() const {
		if (__rc__ == nullptr) {
			// TODO throw
		}
		return *__rc__->ptr;
	}

	T* getPtr() const {
		if (__rc__ == nullptr) {
			// TODO throw
		}
		return __rc__->ptr;
	}

	T& operator*() const {
		if (__rc__ == nullptr) {
			// TODO throw
		}
		return *__rc__->ptr;
	}

	T* operator->() const {
		if (__rc__ == nullptr) {
			// TODO throw
		}
		return __rc__->ptr;
	}

	Type runtimeType() const;

	Reference<String> toString() const;
};

class Int: public Object {
public:
	uint64_t value;

	Int(): value(0) {}

	Int(uint64_t v): value(v) {}

	Int operator+(Int other) const {
		return Int(value + other.value);
	}

	Int operator-(Int other) const {
		return Int(value - other.value);
	}

	Int operator*(Int other) const {
		return Int(value * other.value);
	}

	Int operator/(Int other) const {
		return Int(value / other.value);
	}

	Int operator%(Int other) const {
		return Int(value % other.value);
	}

	bool operator==(Int other) const {
		return value == other.value;
	}

	bool operator!=(Int other) const {
		return value != other.value;
	}

	bool operator>(Int other) const {
		return value > other.value;
	}

	bool operator<(Int other) const {
		return value < other.value;
	}

	bool operator<=(Int other) const {
		return value <= other.value;
	}

	bool operator>=(Int other) const {
		return value >= other.value;
	}

	bool operator==(uint64_t other) const {
		return value == other;
	}

	bool operator!=(uint64_t other) const {
		return value != other;
	}

	bool operator>(uint64_t other) const {
		return value > other;
	}

	bool operator<(uint64_t other) const {
		return value < other;
	}

	bool operator<=(uint64_t other) const {
		return value <= other;
	}

	bool operator>=(uint64_t other) const {
		return value >= other;
	}

	Double sqrt() const;

	Double toDouble() const;

	Reference<String> toString() const;

	const Type runtimeType() const;

	static const Type xaneType;
};

class Double: public Object {
public:
	double value;

	Double(): value(0) {}

	Double(double v): value(v) {}

	Double operator+(Double other) const {
		return Double(value + other.value);
	}

	Double operator-(Double other) const {
		return Double(value - other.value);
	}

	Double operator*(Double other) const {
		return Double(value * other.value);
	}

	Double operator/(Double other) const {
		return Double(value / other.value);
	}

	Double operator%(Double other) const {
		return Double(uint64_t(value) % uint64_t(other.value));
	}

	Double operator+(Int other) const {
		return Double(value + other.value);
	}

	Double operator-(Int other) const {
		return Double(value - other.value);
	}

	Double operator*(Int other) const {
		return Double(value * other.value);
	}

	Double operator/(Int other) const {
		return Double(value / other.value);
	}

	Double operator%(Int other) const {
		return Double(uint64_t(value) % uint64_t(other.value));
	}

	Double sqrt() const;

	Int toInt() const;

	Reference<String> toString() const;

	const Type runtimeType() const;

	static const Type xaneType;
};

class CString: public Object {
public:
	char const * const chars;

	const Int length;

	CString(char const * ch);

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
	String(uint64_t length);

public:
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

	bool isEqual(Reference<String>) const;

	Reference<String> concat(Reference<String> other) const;

	Reference<String> concat(const CString& other) const;

	Reference<String> concat(const Object& other) const;

	Reference<String> concat(const Object&& other) const;

	Reference<String> concat(const Reference<ReferencedObject> other) const;

	static const Type xaneType;

	friend class CString;

	Reference<String> toString() const;

	const Type runtimeType() const;

	void deinit();
};

class Type {
public:
	const CString package;

	const CString library;

	const CString name;

	Type(const char * package, const char * library, const char * name);

	/* TODO
	Type(CString& package, CString& library, CString& name);

	Type(CString&& package, CString&& library, CString&& name);
	*/

	bool operator==(Type other) const;

	Reference<String> toString() const;
};

extern const Type nullType;

Int Int_init(uint64_t val);

Double Double_init(double val);

Reference<String> String_init_fromBytes(char const * chars, uint64_t size);

Reference<String> String_init_fromLiteral(char const * chars);

void print(const Reference<String> string, bool newLine = true);

void print(const CString& string, bool newLine = true);

void print(const CString&& string, bool newLine = true);

void print(const Object& object, bool newLine);

void print(const Object&& object, bool newLine);

void print(const Reference<Object> object, bool newLine);

template<typename T>
Type Reference<T>::runtimeType() const {
	return T::xaneType;
}

template<typename T>
Reference<String> Reference<T>::toString() const {
	if(__rc__ == nullptr) return String_init_fromLiteral("null");
	return __rc__->ptr->toString();
}

#endif /* INCLUDE_CORE_HPP_ */
