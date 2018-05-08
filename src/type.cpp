/*
 * type.cpp
 *
 *  Created on: May 5, 2018
 *      Author: Issac
 */

#include "core.hpp"

// TODO using namespace std;

const Type Type::xaneType = Type("Xane", "Core", "Type");

bool Type::operator==(Type other) const {
	if(strcmp(name, other.name) != 0) return false;
	if(strcmp(library, other.library) != 0) return false;
	if(strcmp(package, other.package) != 0) return false;
	return true;
}

Reference<String> Type::toString() const {
	uint64_t pakLen = strlen(package);
	uint64_t libLen = strlen(library);
	uint64_t nameLen = strlen(name);
	auto ret = *new String(pakLen + libLen + nameLen + 4);
	uint64_t start = 0;
	ret.replaceRange(start, pakLen, package);
	start += pakLen;
	ret.replaceRange(start, 2, "::");
	start += 2;
	ret.replaceRange(start, libLen, library);
	start += libLen;
	ret.replaceRange(start, 2, "::");
	start += 2;
	ret.replaceRange(start, nameLen, name);
	return Reference<String>(&ret);
}
