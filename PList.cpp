/**
  * GreenPois0n Arsenic - PList.cpp
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

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "Node.h"
#include "PList.h"
#include "RootNode.h"

namespace GP {

PList::PList() :
	mFile(0) {
}

PList::~PList() {
}

PList* PList::open(const AbstractFile* file) {
	Dictionary* root = new Dictionary();
	int size = file->size();
	char* data = (char*) file->read(size);
	char* begin = strstr(data, "<plist");
	char* end = strstr(data, "</plist");
	char* cursor = begin;
	while (end - cursor > 0) {
		char* key_start = strstr(cursor, "<key>");
		char* key_stop = strstr(key_start, "</key>");
		int key_size = key_stop - key_start;
		cursor = key_stop;
		char* type_start = strchr(cursor, '<');
		char* type_stop = strchr(cursor, '>');
		int type_size = type_stop - type_start;
		cursor = type_stop;
		//char* value_start = strstr(cursor,)
		//if (!cursor) break;
		//root->addNode(kStringNode);

	}
	PList* plist = new PList();
	return plist;

}


Node* Node::findNode(const String& key) {
	return NULL;
}

}
