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

#include "plist.h"

namespace Arsenic {
	namespace Util {

		// Constructor
		PList::PList(MemoryFile* file) {
			mFile = file;

			if (! mFile) {
				LOG4CXX_WARNING(logger, "MemoryFile was null (wtf?");
				return;
			}

			// Binary PList?
			if (memcmp((char*)file->readAll(), "bplist00", 8) == 0) {
				char* out = NULL;

				uint32_t size = 0;

				plist_from_bin((char*)file->readAll(), file->size(), &mNode);
				plist_to_xml(mNode, &out, length);

				file->write((unsigned char*)out);
				free(out);
			}

			if (mNode != NULL) {
				plist_free(mNode);
			}

			plist_from_xml((char*)file->readAll(), file->size(), &mNode);

			mType = getType(mNode);
		}

		// Destructor
		PList::~PList() {

			if (mNode) {
				plist_free(mNode);
			}

			if (mFile) {
				delete mFile;
			}
		}

		// PList operations
		plist_t PList::getNode(const char* key) {
			return getNode(mNode, key);
		}

		plist_t PList::getNode(plist_t node, const char* key)
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot get item, node was null");]
				return NULL;
			}

			if (getType(node) == PLIST_DICT) {
				return plist_dict_get_item(node, key);
			}

			return NULL;
		}

		plist_t PList::getNode(uint32_t index) {
			return getNode(mNode, index);
		}

		plist_t PList::getNode(plist_t node, uint32_t index) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot get item, node was null");
				return NULL;
			}

			if (getType(node) == PLIST_ARRAY) {
				return plist_array_get_item(node, index);
			}

			return NULL;
		}

		plist_type PList::getType(const char* node) {
			return getType(getNode(node));
		}

		plist_type PList::getType(plist_t node) {
			return plist_get_node_type(node);
		}

		const char* PList::getString(const char* key) {
			return getString(getNode(key));
		}

		const char* PList::getString(plist_t node) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot get item, node was null");
				return NULL;
			}

			if (getType(node) == PLIST_STRING) {
				char* tmp = NULL;

				plist_get_string_val(node, &tmp);

				return (const char*)tmp;
			}

			return NULL;
		}
		
		bool PList::getBool(const char* key) {
			return getBool(getNode(key));
		}

		bool PList::getBool(plist_t node) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot get item, node was null");
				return false;
			}

			if (getType(node) == PLIST_BOOLEAN) {
				uint8_t test = 0;
				plist_get_bool_val(node, &test);

				if (test == 1) {
					return true;
				}
			}

			return false;
		}
	}
}