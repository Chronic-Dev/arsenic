/**
* GreenPois0n Arsenic
* Copyright (C) 2010-2011 Chronic-Dev Team
* Copyright (C) 2010-2011 GreySyntax
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

#ifndef PLIST_H_
#define PLIST_H_

#include "common.h"
#include "memoryfile.h"

extern "C" {
	#include <plist/plist.h>
}

namespace GP {

	class PList {

	public:
		PList(const char* filename);
		PList(const char* filename, plist_t node, plist_type type);
		PList(const char* filename, char* data);
		~PList();

		static PList* fromPartial(const char* container, const char* filename);
		PList* getNode(const char* key);

		//Methods
		plist_type getType(const char* node_name);
		plist_type getType(plist_t node);
		void getStringValue(const char* key, char** value);
		bool getBoolValue(const char* key);

	private:
		void setRootNode(char* buffer, int length);
		const char* _filename;
		plist_t _node;
		plist_type _type;
	};
}
#endif /* PLIST_H_ */
