/**
  * GreenPois0n Arsenic - Image3Element.cpp
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

#include <cstring>
#include "Image3Element.h"

namespace GP {

Image3Element::Image3Element(Image3ElementHeader* header, unsigned char* data) :
	mData(0), mHeader(0), mSignature(0), mFullSize(0), mDataSize(0)   {
	mData = data;
	mHeader = header;
	mSignature = mHeader->signature;
	mFullSize = mHeader->full_size;
	mDataSize =  mHeader->data_size;
}

Image3Element::~Image3Element() {

}

}
