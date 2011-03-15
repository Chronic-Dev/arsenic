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

#include "sha1.h"

using namespace std;

namespace GP
{
    SHA1::SHA1(unsigned char* hash) {
        
        if (hash) {
            _hash = new unsigned char[SHA_DIGEST_LENGTH];
            memcpy(_hash, hash, SHA_DIGEST_LENGTH);
        }
    }
    
    SHA1::~SHA1() {
        
        if (_hash) {
            delete _hash;
            _hash = NULL;
        }
    }
    
    SHA1* SHA1::calculate(MemoryFile* file) {
        
        SHA_CTX ctx;
        unsigned char digest[SHA_DIGEST_LENGTH];
        memset(digest, '\0', SHA_DIGEST_LENGTH);
        
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, file->getData(), strlen((const char*)file->getData()));
        SHA1_Final(digest, &ctx);
        
        return (SHA1*)new SHA1(digest);
    }
    
    unsigned char* SHA1::getHash() {
        
        return _hash;
    }
    
    bool SHA1::equals(SHA1* compare) {
        
        if(! memcmp(_hash, compare->getHash(), 0x20)) {
            
            return true;
        } else {
            
            return false;
        }
    }
}
