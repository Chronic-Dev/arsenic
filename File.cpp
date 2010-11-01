/**
  * GreenPois0n Arsenic - File.cpp
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

#include <string>
#include <cstdio>

#include "File.h"
#include "String.h"

namespace GP {

File::File() :
	mFile(0), mFilename(0) {

}

File* File::open(String& filename) {
	FILE* fd = fopen(filename.get(), "r+b");
	if (!fd) {
		return NULL;
	}

	File* file = new File();
	file->mFile = fd;
	file->mFilename = String(filename);
	return file;
}

File* File::create(String& filename) {
	FILE* fd = fopen(filename.get(), "w+b");
	if (!fd) {
		return NULL;
	}

	File* file = new File();
	file->mFile = fd;
	file->mFilename = filename;
	return file;
}

File::~File() {
	if (mFile) {
		fclose(mFile);
		mFile = NULL;
	}
}

unsigned char* File::read(unsigned int size) {
	unsigned char* buffer = new unsigned char[size];
	if(!buffer) {
		return NULL;
	}

	if(fread(buffer, 1, size, mFile) != size) {
		return NULL;
	}

	return buffer;
}

unsigned int File::write(unsigned char* buffer, unsigned int size) {
	if(!mFile) return -1;

	if(fwrite(buffer, 1, size, mFile) != size) {
		return -1;
	}

	return size;
}

unsigned int File::size() {
	if(mSize) return mSize;

	long cur = ftell(mFile);
	fseek(mFile, 0, SEEK_END);
	long length = ftell(mFile);
	fseek(mFile, cur, SEEK_SET);

	return (unsigned int) length;
}

void File::close() {
	if(mFile) {
		fclose(mFile);
		mFile = NULL;
	}
}

}
