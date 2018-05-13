/*
 * object.cpp
 *
 *  Created on: 8 maj 2018
 *      Author: SERAGUD
 */

#include "core.hpp"

Type Object::runtimeType() {
	return anyType;
}

Reference<String> Object::toString() {
	return String::init_fromLiteral("Any");
}

void ReferencedObject::deinit() {

}

ReferencedObject::~ReferencedObject() {
}

Type ReferencedObject::runtimeType() {
	return anyType;
}

Reference<String> ReferencedObject::toString() {
	return String::init_fromLiteral("Any");
}
