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
        
        fread(buffer, 1, len, file);
        fclose(file);
        
        //Is this a binary plist?
        
        if (memcmp(buffer, "bplist00", 8) == 0) {
            
            char* out = NULL;
            uint32_t size = 0;
            
            cout << "[*] Converting binary plist to xml" << endl;
            plist_from_bin(buffer, len, &_node);
            plist_to_xml(_node, &out, &size);
            
            free(buffer);
            
            buffer = out;
            len = size;
        }
        
        plist_from_xml(buffer, len, &_node);
        
        //Get the root node's type
        _type = plist_get_node_type(_node);
        
        if (_type == PLIST_DICT) {
            
            cout << "[!!] Root plist, has size: " << plist_dict_get_size(_node) << endl;
        }
    }
    
    PList::~PList() {
        
        //destory
        plist_free(_node);
        delete(filename);
    }
    
    plist_type PList::getType(const char* node_name) {
        
        return plist_get_node_type();
    }

}

