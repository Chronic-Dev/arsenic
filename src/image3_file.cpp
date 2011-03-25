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

#include <openssl/aes.h>

#include "image3_file.h"
#include "image3_element.h"
#include "memory_file.h"

namespace GP {

Image3File::Image3File() :
	_IV(0), _key(0), _original(0), _file(0), _header(0), _decrypted(0),
			_typeElement(0), _dataElement(0), _versElement(0), _sepoElement(0),
			_bordElement(0), _kbag1Element(0), _kbag2Element(0),
			_ecidElement(0), _shshElement(0), _certElement(0) {
	_isDecrypted = false;
}

Image3File::~Image3File() {
	if (_decrypted) {
		delete[] _decrypted;
		_decrypted = NULL;
	}

	if(_IV) {
		delete[] _IV;
		_IV = NULL;
	}

	if(_key) {
		delete[] _key;
		_key = NULL;
	}

	if(_original) {
		delete _original;
		_original = NULL;
	}

	if(_file) {
		delete _file;
		_file = NULL;
	}

	if(_header) {
		delete _header;
		_header = NULL;
	}

	if(_decrypted) {
		delete _decrypted;
		_decrypted = NULL;
	}

	if(_typeElement) {
		delete _typeElement;
		_typeElement = NULL;
	}

	if(_dataElement) {
		delete _dataElement;
		_dataElement = NULL;
	}

	if(_versElement) {
		delete _versElement;
		_versElement = NULL;
	}

	if(_sepoElement) {
		delete _sepoElement;
		_sepoElement = NULL;
	}

	if(_bordElement) {
		delete _bordElement;
		_bordElement = NULL;
	}

	if(_kbag1Element) {
		delete _kbag1Element;
		_kbag1Element = NULL;
	}

	if(_kbag2Element) {
		delete _kbag2Element;
		_kbag2Element = NULL;
	}

	if(_ecidElement) {
		delete _ecidElement;
		_ecidElement = NULL;
	}

	if(_shshElement) {
		delete _shshElement;
		_shshElement = NULL;
	}

	if(_certElement) {
		delete _certElement;
		_certElement = NULL;
	}
}

Image3File* Image3File::open(MemoryFile* file) {
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

	header = (Image3Header*) file->getData(sizeof(Image3Header));
	if (header->signature != kImg3Container) {
		return NULL;
	}
	image->_header = header;
	offset += sizeof(Image3Header);

	current = NULL;
	while (offset < size) {
		current = (Image3ElementHeader*) file->getData(sizeof(Image3ElementHeader));
		if (current == NULL)
			break;
		switch (current->signature) {
		case kTypeElement:
			image->_typeElement = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
			if (image->_typeElement == NULL) {
				return NULL;
			}
			break;

		case kDataElement:
			image->_dataElement = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
			if (image->_dataElement == NULL) {
				return NULL;
			}
			break;

		case kVersElement:
			image->_versElement = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
			if (image->_versElement == NULL) {
				return NULL;
			}
			break;

		case kSepoElement:
			image->_sepoElement = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
			if (image->_sepoElement == NULL) {
				return NULL;
			}
			break;

		case kBordElement:
			image->_bordElement = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
			if (image->_bordElement == NULL) {
				return NULL;
			}
			break;

		case kKbagElement:
			if (image->_kbag1Element == NULL) {
				image->_kbag1Element = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
				if (image->_kbag1Element == NULL) {
					return NULL;
				}

			} else {
				image->_kbag2Element = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
				if (image->_kbag2Element == NULL) {
					return NULL;
				}
			}
			break;

		case kEcidElement:
			image->_ecidElement = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
			if (image->_ecidElement == NULL) {
				return NULL;
			}
			break;

		case kShshElement:
			image->_shshElement = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
			if (image->_shshElement == NULL) {
				return NULL;
			}
			break;

		case kCertElement:
			image->_certElement = new Image3Element(current, file->getData(current->full_size - sizeof(Image3ElementHeader)));
			if (image->_certElement == NULL) {
				return NULL;
			}
			break;

		default:

			return NULL;
		}
		offset += current->full_size - sizeof(Image3ElementHeader);
	}

	image->_file = file;
	image->_signature = header->signature;
	image->_dataSize = header->data_size;
	image->_fullSize = header->full_size;
	image->_shshOffset = header->shsh_offset;
	image->_imageType = header->image_type;
	return image;
}

MemoryFile* Image3File::decrypt(const char* key, const char* iv) {
	AES_KEY aeskey;

	if (iv) setIV(iv);
	else if(!_IV) return NULL;

	if (key) setKey(key);
	else if(!_key) return NULL;

	Image3Element* data_element = getElement(kDataElement);
	if (!data_element)
		return NULL;

	if (_decrypted) {
		delete[] _decrypted;
		_decrypted = NULL;
	}

	unsigned int data_size = data_element->getDataSize();
	unsigned char* data_in = data_element->getData();
	unsigned char* data_out = new unsigned char[data_size];
	if (!data_out) return NULL;
	_decrypted = data_out;

	AES_set_decrypt_key(_key, 256, &aeskey);
	AES_cbc_encrypt(data_in, data_out,
			data_size, &aeskey, _IV, AES_DECRYPT);

	_isDecrypted = true;
	return (new MemoryFile(_file->getName(), (unsigned char*)_decrypted));
}

Image3File* Image3File::setIV(const char* iv) {
	int size = strlen(iv) / 2;
	if (_IV) {
		delete _IV;
		_IV = NULL;
	}
	_IV = new unsigned char[size];
	if (!_IV)
		return NULL;

	for (int i = 0; i < size; i++) {
		sscanf(&iv[i * 2], "%02x", (unsigned int*) &_IV[i]);
	}

	return this;
}
Image3File* Image3File::setKey(const char* key) {
	int size = strlen(key) / 2;
	if (_key) {
		delete _key;
		_key = NULL;
	}
	_key = new unsigned char[size];
	if (!_key)
		return NULL;

	for (int i = 0; i < size; i++) {
		sscanf(&key[i * 2], "%02x", (unsigned int*) &_key[i]);
	}

	return this;
}

Image3File* Image3File::setKeyAndIV(const char* key, const char* iv) {
	return setKey(key)->setIV(iv);
}

Image3Element* Image3File::getElement(Image3ElementType type) {
	switch (type) {
	case kTypeElement:
		return _typeElement;
	case kDataElement:
		return _dataElement;
	case kVersElement:
		return _versElement;
	case kSepoElement:
		return _sepoElement;
	case kBordElement:
		return _bordElement;
	case kKbagElement:
		return _kbag1Element;
	case kEcidElement:
		return _ecidElement;
	case kShshElement:
		return _shshElement;
	case kCertElement:
		return _certElement;
	default:
		break;
	}
	return 0;
}

}
