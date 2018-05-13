/*
 * object.hpp
 *
 *  Created on: 8 maj 2018
 *      Author: SERAGUD
 */

#ifndef INCLUDE_OBJECT_HPP_
#define INCLUDE_OBJECT_HPP_

class Type;

class String;

typedef void Void;

template<typename T>
class Reference;

/// Base class for a Xane Object
class Object {
public:
	virtual Type runtimeType();

	virtual Reference<String> toString();
};

/// Base class for Xane referenced Object
class ReferencedObject {
public:
	virtual ~ReferencedObject();

	virtual void deinit();

	virtual Type runtimeType();

	virtual Reference<String> toString();
};

struct RefCount {
	uint64_t sharedCount;
	uint64_t weakCount;
	ReferencedObject* ptr;

	RefCount(ReferencedObject* ptr) :
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
	RefCount* __rc__;

public:
	Reference() :
			__rc__(nullptr) {
	}

	Reference(T* ptr) :
			__rc__(new RefCount(ptr)) {
	}

	Reference(RefCount* counter) :
			__rc__(counter) {
		__rc__->incrementShared();
	}

	Reference(Reference<T>& other) :
			__rc__(other.__rc__) {
		__rc__->incrementShared();
	}

	Reference(Reference<T> && other) :
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
		__rc__ = new RefCount(other);
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
		return *dynamic_cast<T*>(__rc__->ptr);
	}

	T* operator->() const {
		if (__rc__ == nullptr) {
			// TODO throw
		}
		return dynamic_cast<T*>(__rc__->ptr);
	}

	template<class NT>
	Reference<NT> as() {
		if (__rc__ == nullptr) {
			// TODO throw
		}
		NT* cast = dynamic_cast<NT*>(__rc__->ptr);
		if(cast == nullptr) {
			// TODO throw
		}
		return Reference<NT>(__rc__);
	}

	Type runtimeType() const;

	Reference<String> toString() const;
};

class Type: public Object {
public:
	const char * const package;

	const char * const library;

	const char * const name;

	constexpr Type(const char * const package, const char * const library,
			const char * const name) :
			package(package), library(library), name(name) {
	}

	bool operator==(Type other) const;

	Reference<String> toString() const;

	const Type runtimeType() const {
		return xaneType;
	}

	static const Type xaneType;
};

class Null: public ReferencedObject {
public:
	constexpr Null() {
	}

	static constexpr Type xaneType = Type("Xane", "Core", "Null");
};

static constexpr Type anyType = Type("Xane", "Core", "Any");

#endif /* INCLUDE_OBJECT_HPP_ */
