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

#ifndef ARSENIC_UTIL_PLIST_H_
#define ARSENIC_UTIL_PLIST_H_

#include "../core/common.h"
#include "../io/memoryfile.h"

extern "C" {
	#include <plist/plist.h>
}

using namespace Arsenic::IO;

namespace Arsenic {
	namespace Util {
		class PList {
			public:
				// Constructor
				PList(MemoryFile* file);

				// Destructor
				~PList();

				// PList operations
				plist_t getNode(uint32_t index);
				plist_t getNode(const char* key);
				plist_t getNode(plist_t node, uint32_t index);
				plist_t getNode(plist_t node, const char* key);

				void setNode(plist_t node, const char* key, plist_t item);
				void setNode(const char* key, plist_t item);
				void setNode(plist_t node, plist_t item, uint32_t index);
				void setNode(const char* key, plist_t item, uint32_t index);

				plist_type getType(plist_t node);
				plist_type getType(const char* key);

				void setType(plist_t node, plist_type type);
				void setType(const char* key, plist_type type);

				const char* getString(plist_t node);
				const char* getString(const char* key);

				void setString(plist_t node, const char* value);
				void setString(const char* key, const char* value);

				bool getBool(plist_t node);
				bool getBool(const char* key);

				void setBool(plist_t node, bool value);
				void setBool(const char* key, bool value);

				int getInt(plist_t node);
				int getInt(const char* key);

				void setInt(plist_t node, uint32_t value);
				void setInt(const char* key, uint32_t value);

				double getReal(plist_t node);
				double getReal(const char* key);
				
				void setReal(plist_t node, double value);
				void setReal(const char* key, double value);

				unsigned char* getData(plist_t node);
				unsigned char* getData(const char* key);

				void setData(plist_t node, unsigned char* data);
				void setData(const char* key, unsigned char* data);

				int32_t getDate(plist_t node);
				int32_t getDate(const char* key);

				void setDate(plist_t node, int32_t value);
				void setDate(const char* key, int32_t value);

				bool compare(plist_t nodeA, plist_t nodeB);

				bool save();

			private:
				plist_t mNode;
				plist_type mType;
				MemoryFile* mFile;
		};
	}
}
#endif /* ARSENIC_UTIL_PLIST_H_ */