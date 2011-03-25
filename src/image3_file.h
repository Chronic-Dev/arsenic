/**
* GreenPois0n Arsenic
* Copyright (C) 2010-2011 Chronic-Dev Team
* Copyright (C) 2010-2011 Joshua Hill
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

#ifndef IMAGE3FILE_H
#define IMAGE3FILE_H

#include <cstdio>
#include <cstring>
#include "image3_element.h"
#include "memory_file.h"

namespace GP {

typedef enum {
    kNorContainer  = 0x696D6733, // img3
    kImg3Container = 0x496D6733, // Img3
    k8900Container = 0x30303938, // 8900
    kImg2Container = 0x494D4732  // IMG2
} Image3Container;

typedef struct {
    unsigned int signature;
    unsigned int full_size;
    unsigned int data_size;
    unsigned int shsh_offset;
    unsigned int image_type;
} Image3Header;

class Image3File {
public:
	Image3File();
	virtual ~Image3File();

	static Image3File* open(MemoryFile* file);
	MemoryFile* decrypt(const char* key = NULL, const char* iv = NULL);

	Image3File* setIV(const char* iv);
	Image3File* setKey(const char* key);
	Image3File* setKeyAndIV(const char* key, const char* iv);

	Image3Element* getElement(Image3ElementType type);

protected:
	bool _isDecrypted;
	unsigned char* _IV;
	unsigned char* _key;
	unsigned char* _patched;
	unsigned char* _original;
	unsigned char* _decrypted;
	unsigned int _signature;
	unsigned int _dataSize;
	unsigned int _fullSize;
	unsigned int _shshOffset;
	unsigned int _imageType;

	MemoryFile* _file;
	Image3Header* _header;
	Image3Element* _typeElement;
	Image3Element* _dataElement;
	Image3Element* _versElement;
	Image3Element* _sepoElement;
	Image3Element* _bordElement;
	Image3Element* _kbag1Element;
	Image3Element* _kbag2Element;
	Image3Element* _ecidElement;
	Image3Element* _shshElement;
	Image3Element* _certElement;
};

}

#endif /* IMAGE3FILE_H */
