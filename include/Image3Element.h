/**
  * GreenPois0n Arsenic - Image3Element.h
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
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

	unsigned char* getData() {
		return mData;
	}

	unsigned int getFullSize() {
		return mFullSize;
	}

	unsigned int getDataSize() {
		return mDataSize;
	}

	unsigned int getSignature() {
		return mSignature;
	}

	Image3ElementType getType() {
		return mType;
	}

	Image3ElementHeader* getHeader() {
		return mHeader;
	}

protected:
	unsigned char* mData;
	unsigned int mDataSize;
	unsigned int mFullSize;
	unsigned int mSignature;
	Image3ElementType mType;
	Image3ElementHeader* mHeader;
};

}

#endif /* IMAGE3ELEMENT_H */
