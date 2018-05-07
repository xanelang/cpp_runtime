/*
 * type.cpp
 *
 *  Created on: May 5, 2018
 *      Author: Issac
 */

#include "core.hpp"

// TODO using namespace std;

Type::Type(const char * package, const char * library,
		const char * name) :
		package(package), library(library), name(name) {
	print(this->name);
}

/*
Type::Type(CString& package, CString& library, CString& name): package(package), library(library), name(name) {

}

Type::Type(CString&& package, CString&& library, CString&& name): package(package), library(library), name(name) {

}
*/

bool Type::operator==(Type other) const {
	if (!package.isEqual(other.package)) {
		return false;
	}
	if (!library.isEqual(other.library)) {
		return false;
	}
	if (!name.isEqual(other.name)) {
		return false;
	}
	return true;
}


Reference<String> Type::toString() const {
	return package.concat(CString("::"))
			->concat(library)
			->concat(CString("::"))
			->concat(name);
}

const Type nullType("Xane", "Core", "Null");
