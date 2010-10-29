/**
  * GreenPois0n Arsenic - MemoryFile.cpp
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

#include "Common.h"
#include "MemoryFile.h"

namespace GP {

MemoryFile::MemoryFile() :
	mSize(0), mData(0), mOffset(0) {
}

MemoryFile::~MemoryFile() {
	if(mData) {
		delete mData;
		mData = NULL;
	}
	mSize = 0;
	mOffset = 0;
}

MemoryFile* MemoryFile::open(unsigned char* buffer, unsigned int size) {
	MemoryFile* file = new MemoryFile();
	file->mData = buffer;
	file->mSize = size;
	return file;
}

void MemoryFile::close() {
	if(mData) {
		delete mData;
		mData = NULL;
	}
}

unsigned int MemoryFile::size() {
	return mSize;
}

unsigned char* MemoryFile::read(unsigned int size) {
	unsigned char* segment = NULL;
	if (mSize >= mOffset + size) {
		segment = new unsigned char[size];
		if (!segment)
			return NULL;
		memcpy(segment, &mData[mOffset], size);
		mOffset += size;
	}
	return segment;
}

unsigned int MemoryFile::write(unsigned char* buffer, unsigned int size) {
	unsigned char* segment = NULL;
	if(mOffset + size > mSize) {
		segment = new unsigned char[mOffset + size];
		memcpy(segment, mData, mOffset);
		delete mData;
		mData = segment;
	}

	segment = &mData[mOffset];
	memcpy(segment, buffer, size);
	return size;
}

}
