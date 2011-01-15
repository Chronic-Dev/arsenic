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

/* for partial-zip */
char endianness = IS_LITTLE_ENDIAN;

void callback(ZipInfo* info, CDFile* file, size_t progress) {
    
    int percentDone = progress * 100/file->compressedSize;
    cout << "[!!] Getting " << percentDone << endl;
}

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
        
        setRootNode(buffer, len);
    }
    
    PList::PList(const char* filename, char* data) {
        
        _filename = filename;
        setRootNode(data, strlen(data));
    }
    
    PList::~PList() {
        
        //destory
        plist_free(_node);
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
    
    PList* PList::fromPartial(const char* container, const char* filename) {
        
        cout << "[*] Extracting PList using partial-zip" << endl;
        
        int len = strlen(container);
        char fname[len+7]; //account for file:// if it's missing
        
        //Somebody forgot file:// or http://
        if (strstr(container, "http://") == NULL && strstr(container, "file://") == NULL) {
            
            strcpy(fname, "file://");
        }
        
        strcat(fname, container);
        
        ZipInfo* info = PartialZipInit(fname);
        
        if (info == NULL) {
            
            cout << "[X] Failed to open url: " << fname << " (aborting)" << endl;
            return NULL;
        }
        
        PartialZipSetProgressCallback(info, callback);
        CDFile* file = PartialZipFindFile(info, filename);
        
        if (!file) {
            
            cout << "[X] Failed to find file (" << filename << ") in stream (aborting)" << endl;
            return NULL;
        }
        
        unsigned char* buffer = PartialZipGetFile(info, file);
        
        int bufferLen = file->size;
        
        buffer = (unsigned char*)realloc(buffer, bufferLen+1);
        buffer[bufferLen] = '\0';
        
        return new PList(filename, (char*)buffer);
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
        
        plist_from_xml(buffer, length, &_node);
        
        //Get the root node's type
        _type = plist_get_node_type(_node);
        
        if (_type == PLIST_DICT) {
            
            cout << "[!!] Root plist, has size: " << plist_dict_get_size(_node) << endl;
        }
    }
}