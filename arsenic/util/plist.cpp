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

			if (!mFile) {
				LOG4CXX_WARN(logger, "MemoryFile was null (wtf?)");
				return;
			}

			// Binary PList?
			if (memcmp((char*)file->readAll(), "bplist00", 8) == 0) {
				char* out = NULL;

				uint32_t size = 0;

				plist_from_bin((char*)file->readAll(), file->size(), &mNode);
				plist_to_xml(mNode, &out, &size);

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
		plist_t PList::getNode(uint32_t index) {
			return getNode(mNode, index);
		}

		plist_t PList::getNode(const char* key) {
			return getNode(mNode, key);
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

		plist_t PList::getNode(plist_t node, const char* key) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot get item, node was null");
				return NULL;
			}

			if (getType(node) == PLIST_DICT) {
				return plist_dict_get_item(node, key);
			}

			return NULL;
		}

		void PList::setNode(plist_t node, const char* key, plist_t item) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set node, node was null");
				return;
			}

			if (item == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set item, item was null");
				return;
			}

			if (getType(node) == PLIST_DICT) {
				plist_dict_set_item(node, key, item);
			}
		}

		void PList::setNode(const char* key, plist_t item) {
			setNode(mNode, key, item);
		}

		void PList::setNode(const char* key, plist_t item, uint32_t index) {
			setNode(getNode(key), item, index);
		}

		void PList::setNode(plist_t node, plist_t item, uint32_t index) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set node, node was null");
				return;
			}

			if (item == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set item, item was null");
				return;
			}

			if (getType(node) == PLIST_ARRAY) {
				plist_array_set_item(node, item, index);
			}
		}

		plist_type PList::getType(plist_t node) {
			return plist_get_node_type(node);
		}

		plist_type PList::getType(const char* node) {
			return getType(getNode(node));
		}

		void PList::setType(plist_t node, plist_type type) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set node type, node was null");
				return;
			}

			plist_set_type(node, type);
		}

		void PList::setType(const char* key, plist_type type) {
			setType(getNode(key), type);
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

		const char* PList::getString(const char* key) {
			return getString(getNode(key));
		}

		void PList::setString(plist_t node, const char* value) {

			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set node, node was null");
				return;
			}

			if (value == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set node value, value was null");
				return;
			}

			plist_set_string_val(node, value);
		}
		
		void PList::setString(const char* key, const char* value) {
			setString(getNode(key), value);
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

		bool PList::getBool(const char* key) {
			return getBool(getNode(key));
		}

		void PList::setBool(plist_t node, bool value) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set item, node was null");
				return;
			}

			uint8_t state = value ? 1 : 0;
			plist_set_bool_val(node, state);
		}

		void PList::setBool(const char* key, bool value) {
			setBool(getNode(key), value);
		}

		int PList::getInt(plist_t node) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot get item, node was null");
				return 0;
			}

			uint64_t tmp;
			plist_get_uint_val(node, &tmp);

			return (int)tmp;
		}

		int PList::getInt(const char* key) {
			return getInt(getNode(key));
		}

		void PList::setInt(plist_t node, uint32_t value) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set item, node was null");
				return;
			}

			plist_set_uint_val(node, value);
		}

		void PList::setInt(const char* key, uint32_t value) {
			setInt(getNode(key), value);
		}

		double PList::getReal(plist_t node) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot get item, node was null");
				return 0;
			}

			double tmp;
			plist_get_real_val(node, &tmp);
			return tmp;
		}

		double PList::getReal(const char* key) {
			return getReal(getNode(key));
		}

		void PList::setReal(plist_t node, double value) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set item, node was null");
				return;
			}

			plist_set_real_val(node, value);
		}

		void PList::setReal(const char* key, double value) {
			setReal(getNode(key), value);
		}

		unsigned char* PList::getData(plist_t node) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot get item, note was null");
				return NULL;
			}

			uint64_t size = 0;
			char* data = NULL;
			plist_get_data_val(node, &data, &size);

			return (unsigned char*)data;
		}

		unsigned char* PList::getData(const char* key) {
			return getData(getNode(key));
		}

		void PList::setData(plist_t node, unsigned char* data) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set item, node was null");
				return;
			}

			if (data == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set item, data was null");
				return;
			}

			plist_set_data_val(node, (const char*)data, strlen((const char*)data));
		}

		void PList::setData(const char* key, unsigned char* data) {
			setData(getNode(key), data);
		}

		int32_t PList::getDate(plist_t node) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot get item, node was null");
				return 0;
			}

			int32_t tmp = 0;
			int32_t tmpU = 0;
			plist_get_date_val(node, &tmp, &tmpU);

			return tmp;
		}

		int32_t PList::getDate(const char* key) {
			return getDate(getNode(key));
		}

		void PList::setDate(plist_t node, int32_t value) {
			if (node == NULL) {
				LOG4CXX_ERROR(logger, "Cannot set item, node was null");
				return;
			}

			int32_t valueU = value * 1000; // Miliseconds from seconds
			plist_set_date_val(node, value, valueU);
		}

		bool PList::compare(plist_t nodeA, plist_t nodeB) {
			if (plist_compare_node_value(nodeA, nodeB) == 1) {
				return true;
			}

			return false;
		}

		bool PList::save() {
			if (mFile == NULL) {
				LOG4CXX_ERROR(logger, "Cannot save plist, MemoryFile was null");
				return false;
			}

			mFile->write((unsigned char*)mNode);
			return mFile->save();
		}
	}
}