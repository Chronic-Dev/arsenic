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

#include <cstring>
#include "image3_element.h"

namespace GP {

	Image3Element::Image3Element(Image3ElementHeader* header, unsigned char* data) :
		_data(0), _header(0), _signature(0), _fullSize(0), _dataSize(0)   {
		_data = data;
		_header = header;
		_signature = header->signature;
		_fullSize = header->full_size;
		_dataSize =  header->data_size;
	}

	Image3Element::~Image3Element() {

	}
	
	unsigned char* Image3Element::getData() {
		return _data;
	}

	unsigned int Image3Element::getFullSize() {
		return _fullSize;
	}

	unsigned int Image3Element::getDataSize() {
		return _dataSize;
	}

	unsigned int Image3Element::getSignature() {
		return _signature;
	}

	Image3ElementType Image3Element::getType() {
		return _type;
	}

	Image3ElementHeader* Image3Element::getHeader() {
		return _header;
	}

}
