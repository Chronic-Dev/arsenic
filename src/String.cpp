/**
  * GreenPois0n Arsenic - String.cpp
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <cstring>

#include "String.h"

namespace GP {

String::String(const char* data) :
	Node(kStringNode) {
	mData = strdup(data);
	mLength = strlen(data);
}

String::String(const String& data) :
	Node(kStringNode) {
	mData = strdup(data.get());
	mLength = strlen(data.get());
}

String::~String() {
	if(mData) {
		free(mData);
		mData = NULL;
	}
}

const char* String::get() {
	return mData;
}

void String::set(const char* data) {
	if(data) {
	if(mData) {
		delete mData;
		mData = NULL;
	}
	mData = strdup(data);
}

bool String::compare(const String& what) {
	if(!strcmp(mData, what.get())) {
		return true;
	}
	return false;
}

bool String::compare(const char* what) {
	if(!strcmp(mData, what)) {
		return true;
	}
	return false;
}

int String::length() {
	mLength = strlen(mData);
	return mLength;
}

void concat(const char* what) {
	unsigned int addSize = strlen(what);
	unsigned int oldSize = strlen(mData);
	unsigned int newSize = oldSize + addSize;
	if(newSize > mLength) {
		unsigned char* tmp = malloc(newSize+1);
		if(tmp == NULL) {
			return NULL;
		}
		strncpy(tmp, mData, newSize);
		strncat(tmp, what, newSize);
		free(mData);
		mData = tmp;
	}
}

void concat(String& what) {
	unsigned int addSize = what.length();
	unsigned int oldSize = strlen(mData);
	unsigned int newSize = oldSize + addSize;
	if(newSize > mLength) {
		unsigned char* tmp = malloc(newSize+1);
		if(tmp == NULL) {
			return NULL;
		}
		strncpy(tmp, mData, newSize);
		strncat(tmp, what.get(), newSize);
		free(mData);
		mData = tmp;
	}
}

}
