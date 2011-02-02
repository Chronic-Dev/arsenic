/**
 * GreenPois0n Arsenic
 * Copyright (C) 2010 Chronic-Dev Team
 * Copyright (C) 2010 GreySyntax
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

using namespace std;

namespace GP {
	
	PList::PList(const char* filename) {
		_filename = filename;
		_node = NULL;
		_type = PLIST_NONE;
		
		FILE* file = NULL;
		char* buffer = NULL;
		
		cout << "[*] Attempting to create plist from file (" << filename << ")" << endl;
		file = fopen(filename, "rb");
		
		fseek(file, 0, SEEK_END);
		int len = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		buffer = (char*)malloc(len);
		if (buffer == NULL) {
			cout << "[X] Failed to allocate memory" << endl;
			return;
		}
		bzero(buffer, len);
		
		fread(buffer, 1, len, file);
		fclose(file);
		
		setRootNode(buffer, len);
	}
	
	PList::PList(const char* filename, char* data) {
		
		_filename = filename;
		_node = NULL;
		_type = PLIST_NONE;
		
		setRootNode(data, strlen(data));
	}

	PList::~PList() {
		//destory
		if (_node != NULL)
			plist_free(_node);
		if (_filename != NULL)
			delete(_filename);
	}
	
	long int PList::getType(const char* node_name) {
		if (_type == PLIST_DICT) {
			plist_t node = NULL;
			
			if ((node = plist_dict_get_item(_node, node_name)) != NULL) {
				return plist_get_node_type(node);
			}
		}
		
		return NULL;
	}
	
	long int PList::getType(plist_t node) {
		if (node != NULL) {
			return plist_get_node_type(node);
		}
		
		return NULL;
	}
	
	void PList::getStringValue(const char* key, char **value) {
		if (_type == PLIST_DICT) {
			plist_t node = NULL;
			
			if ((node = plist_dict_get_item(_node, key)) != NULL) {
				if (getType(node) == PLIST_STRING) {
					plist_get_string_val(node, value);
				}
			}
		}
	}
	
	void PList::getBoolValue(const char* key, uint8_t** value) {
		if (_type == PLIST_DICT) {
			plist_t node = NULL;
			
			if ((node = plist_dict_get_item(_node, key)) != NULL) {
				if (getType(node) == PLIST_BOOLEAN) {
					plist_get_bool_val(node, value);
					cout << "[BOOL :O] " << value << endl;
				}
			}
		}
	}
	
	PList* PList::fromPartial(const char* container, const char* filename) {
		
		return (PList*)(new PList(filename, (char*)MemoryFile::fromPartial(container, filename)->getData()));
	}
	
	void PList::setRootNode(char* buffer, int length) {
		//Is this a binary plist?
		
		if (buffer == NULL) {
			cout << "[X] Buffer was empty (aborting)" << endl;
			return;
		}
		
		if (memcmp(buffer, "bplist00", 8) == 0) {
			char* out = NULL;
			uint32_t size = 0;
			
			cout << "[*] Converting binary plist to xml" << endl;
			plist_from_bin(buffer, length, &_node);
			plist_to_xml(_node, &out, &size);
			
			free(buffer);
			
			buffer = out;
			length = size;
		}
		
		if(_node != NULL)
			plist_free(_node);

		plist_from_xml(buffer, length, &_node);
		
		//Get the root node's type
		_type = plist_get_node_type(_node);
		
		if (_type == PLIST_DICT) {
			cout << "[!!] Root plist, has size: " << plist_dict_get_size(_node) << endl;
		}
	}
}
