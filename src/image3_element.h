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

#ifndef IMAGE3ELEMENT_H
#define IMAGE3ELEMENT_H

namespace GP {

typedef enum {
    kDataElement = 0x44415441, // DATA
    kTypeElement = 0x54595045, // TYPE
    kKbagElement = 0x4B424147, // KBAG
    kShshElement = 0x53485348, // SHSH
    kCertElement = 0x43455254, // CERT
    //kChipElement = 0x43484950, // CHIP
    //kProdElement = 0x50524F44, // PROD
    //kSdomElement = 0x53444F4D, // SDOM
    kVersElement = 0x56455253, // VERS
    kBordElement = 0x424F5244, // BORD
    kSepoElement = 0x5345504F, // SEPO
    kEcidElement = 0x45434944  // ECID
} Image3ElementType;

typedef struct {
    unsigned int signature;
    unsigned int full_size;
    unsigned int data_size;
} Image3ElementHeader;

class Image3Element {
public:
	Image3Element(Image3ElementHeader* header, unsigned char* data);
	virtual ~Image3Element();

	unsigned char* getData();
	unsigned int getFullSize();
	unsigned int getDataSize();
	unsigned int getSignature();
	Image3ElementType getType();
	Image3ElementHeader* getHeader();

protected:
	unsigned char* _data;
	unsigned int _dataSize;
	unsigned int _fullSize;
	unsigned int _signature;
	Image3ElementType _type;
	Image3ElementHeader* _header;
};

}

#endif /* IMAGE3ELEMENT_H */
