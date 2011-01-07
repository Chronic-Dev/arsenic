//
//  plist.cpp
//  ArsenicX
//
//  Created by Jordan M on 07/01/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "plist.h"

using namespace std;

namespace GP {
    
    PList::Plist(const char* filename) {
        
        FILE* file = NULL;
        char* buffer = NULL;
        
        cout << "[*] Attempting to create plist from file (" + filename + ")" << endl;
        struct stat *filestats = (struct stat *)malloc(sizeof(struct stat));
        file = fopen(filename, "rb");
        
        fseek(file, 0, SEEK_END);
        int len = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        buffer = malloc(len);
        
        
        if (buffer == NULL) {
            
            cout << "[X] Failed to allocate memory" << endl;
            return;
        }
        
        fread(buffer, 1, len, file);
        fclose(file);
        
        //Is this a binary plist?
        
        if (memcmp(plist_entire, "bplist00", 8) == 0) {
            
            char* out = NULL;
            uint32_t size = 0;
            
            cout << "[*] Converting binary plist to xml" << endl;
            plist_from_bin(buffer, len, &root_node);
            plist_to_xml(root_node, &plist_out, &size);
            
            free(buffer);
            free(len);
            
            buffer = out;
            len = size;
        }
        
        plist_from_xml(buffer, len, root_node);
    }
    
    PList::~PList() {
        
        //destory
        plist_free(root_node);
        free(filename);
    }

}

