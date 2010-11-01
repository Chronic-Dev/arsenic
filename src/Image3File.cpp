/**
  * GreenPois0n Arsenic - Image3File.cpp
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

#include <openssl/aes.h>

#include "Image3File.h"
#include "Image3Element.h"
#include "AbstractFile.h"
#include "MemoryFile.h"

namespace GP {

Image3File::Image3File() :
	mIV(0), mKey(0), mOriginal(0), mFile(0), mHeader(0), mDecrypted(0),
			mTypeElement(0), mDataElement(0), mVersElement(0), mSepoElement(0),
			mBordElement(0), mKbag1Element(0), mKbag2Element(0),
			mEcidElement(0), mShshElement(0), mCertElement(0) {
	mIsDecrypted = false;
}

Image3File::~Image3File() {
	if (mDecrypted) {
		delete[] mDecrypted;
		mDecrypted = NULL;
	}

	if(mIV) {
		delete[] mIV;
		mIV = NULL;
	}

	if(mKey) {
		delete[] mKey;
		mKey = NULL;
	}

	if(mOriginal) {
		delete mOriginal;
		mOriginal = NULL;
	}

	if(mFile) {
		delete mFile;
		mFile = NULL;
	}

	if(mHeader) {
		delete mHeader;
		mHeader = NULL;
	}

	if(mDecrypted) {
		delete mDecrypted;
		mDecrypted = NULL;
	}

	if(mTypeElement) {
		delete mTypeElement;
		mTypeElement = NULL;
	}

	if(mDataElement) {
		delete mDataElement;
		mDataElement = NULL;
	}

	if(mVersElement) {
		delete mVersElement;
		mVersElement = NULL;
	}

	if(mSepoElement) {
		delete mSepoElement;
		mSepoElement = NULL;
	}

	if(mBordElement) {
		delete mBordElement;
		mBordElement = NULL;
	}

	if(mKbag1Element) {
		delete mKbag1Element;
		mKbag1Element = NULL;
	}

	if(mKbag2Element) {
		delete mKbag2Element;
		mKbag2Element = NULL;
	}

	if(mEcidElement) {
		delete mEcidElement;
		mEcidElement = NULL;
	}

	if(mShshElement) {
		delete mShshElement;
		mShshElement = NULL;
	}

	if(mCertElement) {
		delete mCertElement;
		mCertElement = NULL;
	}
}

Image3File* Image3File::open(AbstractFile* file) {
	int size;
	int offset;
	Image3File* image;
	Image3Header* header;
	Image3ElementHeader* current;

	offset = 0;
	size = file->size();
	image = new Image3File();
	if (!image) {
		return NULL;
	}

	header = (Image3Header*) file->read(sizeof(Image3Header));
	if (header->signature != kImg3Container) {
		return NULL;
	}
	image->mHeader = header;
	offset += sizeof(Image3Header);

	current = NULL;
	while (offset < size) {
		current = (Image3ElementHeader*) file->read(sizeof(Image3ElementHeader));
		if (current == NULL)
			break;
		switch (current->signature) {
		case kTypeElement:
			image->mTypeElement = new Image3Element(current, file->read(
					current->full_size - sizeof(Image3ElementHeader)));
			if (image->mTypeElement == NULL) {
				return NULL;
			}
			break;

		case kDataElement:
			image->mDataElement = new Image3Element(current, file->read(
					current->full_size - sizeof(Image3ElementHeader)));
			if (image->mDataElement == NULL) {
				return NULL;
			}
			break;

		case kVersElement:
			image->mVersElement = new Image3Element(current, file->read(
					current->full_size - sizeof(Image3ElementHeader)));
			if (image->mVersElement == NULL) {
				return NULL;
			}
			break;

		case kSepoElement:
			image->mSepoElement = new Image3Element(current, file->read(
					current->full_size - sizeof(Image3ElementHeader)));
			if (image->mSepoElement == NULL) {
				return NULL;
			}
			break;

		case kBordElement:
			image->mBordElement = new Image3Element(current, file->read(
					current->full_size - sizeof(Image3ElementHeader)));
			if (image->mBordElement == NULL) {
				return NULL;
			}
			break;

		case kKbagElement:
			if (image->mKbag1Element == NULL) {
				image->mKbag1Element = new Image3Element(current, file->read(
						current->full_size - sizeof(Image3ElementHeader)));
				if (image->mKbag1Element == NULL) {
					return NULL;
				}

			} else {
				image->mKbag2Element = new Image3Element(current, file->read(
						current->full_size - sizeof(Image3ElementHeader)));
				if (image->mKbag2Element == NULL) {
					return NULL;
				}
			}
			break;

		case kEcidElement:
			image->mEcidElement = new Image3Element(current, file->read(
					current->full_size - sizeof(Image3ElementHeader)));
			if (image->mEcidElement == NULL) {
				return NULL;
			}
			break;

		case kShshElement:
			image->mShshElement = new Image3Element(current, file->read(
					current->full_size - sizeof(Image3ElementHeader)));
			if (image->mShshElement == NULL) {
				return NULL;
			}
			break;

		case kCertElement:
			image->mCertElement = new Image3Element(current, file->read(
					current->full_size - sizeof(Image3ElementHeader)));
			if (image->mCertElement == NULL) {
				return NULL;
			}
			break;

		default:

			return NULL;
		}
		offset += current->full_size - sizeof(Image3ElementHeader);
	}

	image->mFile = file;
	image->mSignature = header->signature;
	image->mDataSize = header->data_size;
	image->mFullSize = header->full_size;
	image->mShshOffset = header->shsh_offset;
	image->mImageType = header->image_type;
	return image;
}

AbstractFile* Image3File::decrypt(const char* key, const char* iv) {
	AES_KEY aeskey;

	if (iv) setIV(iv);
	else if(!mIV) return NULL;

	if (key) setKey(key);
	else if(!mKey) return NULL;

	Image3Element* data_element = getElement(kDataElement);
	if (!data_element)
		return NULL;

	if (mDecrypted) {
		delete[] mDecrypted;
		mDecrypted = NULL;
	}

	unsigned int data_size = data_element->getDataSize();
	unsigned char* data_in = data_element->getData();
	unsigned char* data_out = new unsigned char[data_size];
	if (!data_out) return NULL;
	mDecrypted = data_out;

	AES_set_decrypt_key(mKey, 256, &aeskey);
	AES_cbc_encrypt(data_in, data_out,
			data_size, &aeskey, mIV, AES_DECRYPT);

	mIsDecrypted = true;
	return MemoryFile::open(mDecrypted, data_size);
}

Image3File* Image3File::setIV(const char* iv) {
	int size = strlen(iv) / 2;
	if (mIV) {
		delete mIV;
		mIV = NULL;
	}
	mIV = new unsigned char[size];
	if (!mIV)
		return NULL;

	for (int i = 0; i < size; i++) {
		sscanf(&iv[i * 2], "%02x", (unsigned int*) &mIV[i]);
	}

	return this;
}
Image3File* Image3File::setKey(const char* key) {
	int size = strlen(key) / 2;
	if (mKey) {
		delete mKey;
		mKey = NULL;
	}
	mKey = new unsigned char[size];
	if (!mKey)
		return NULL;

	for (int i = 0; i < size; i++) {char*char*
		sscanf(&key[i * 2], "%02x", (unsigned int*) &mKey[i]);
	}

	return this;
}

Image3File* Image3File::setKeyAndIV(const char* key, const char* iv) {
	return setKey(key)->setIV(iv);
}

Image3Element* Image3File::getElement(Image3ElementType type) {
	switch (type) {
	case kTypeElement:
		return mTypeElement;
	case kDataElement:
		return mDataElement;
	case kVersElement:
		return mVersElement;
	case kSepoElement:
		return mSepoElement;
	case kBordElement:
		return mBordElement;
	case kKbagElement:
		return mKbag1Element;
	case kEcidElement:
		return mEcidElement;
	case kShshElement:
		return mShshElement;
	case kCertElement:
		return mCertElement;
	default:
		break;
	}
	return 0;
}

}
