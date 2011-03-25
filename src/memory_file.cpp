/**
* GreenPois0n Arsenic
* Copyright (C) 2010-2011 Chronic-Dev Team
* Copyright (C) 2010-2011 GreySyntax
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

#include "memory_file.h"

using namespace std;

void callback(ZipInfo* info, CDFile* file, size_t progress) {
	
	int percentDone = progress * 100/file->compressedSize;
	cout << "[!!] Getting: " << percentDone << endl;
}

namespace GP {

	MemoryFile::MemoryFile(const char* filename, unsigned char* data) {
		
		_fileName = filename;
		_data = data;
	}

	MemoryFile::~MemoryFile() {
		
		if (_fileName != NULL) {
			delete _fileName;
		}

		if (_data != NULL) {
			free(_data);
		}
	}

	MemoryFile* MemoryFile::openFile(const char* filename) {
		
		FILE* file = fopen(filename, "r");

		if (file == NULL) {

			cout << "Failed to open file (" << filename << ")." << endl;
			return NULL;
		}

		fseek(file, 0, SEEK_END);
		unsigned int len = ftell(file);
		fseek(file, 0, SEEK_SET);
		fclose(file);

		return MemoryFile::openFile(filename, len);
	}
	
	MemoryFile* MemoryFile::openFile(const char* filename, unsigned int chunk) {
		
		FILE* file = fopen(filename, "r");

		if (file == NULL) {

			cout << "Failed to open file (" << filename << ")." << endl;
			return NULL;
		}

		fseek(file, 0, SEEK_END);
		unsigned int len = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		if (chunk > len) {
			cout << "Failed to read data, specified chunk (" << chunk << ") was to large." << endl;
			return NULL;
		}

		char* data = (char*)malloc(chunk);
		bzero(data, chunk);

		if (data == NULL) {

			cout << "Failed to allocate memory." << endl;
			return NULL;
		}

		fread(data, 1, chunk, file);
		fclose(file);

		return (new MemoryFile(filename, (unsigned char*)data));
	}
	
	int MemoryFile::size() {
		return sizeof(_data);
	}
	
	unsigned char* MemoryFile::getData() {
		
		return &*_data;
	}
	
	unsigned char* MemoryFile::getData(int chunk) {
		
		unsigned char* buffer = (unsigned char*)malloc(chunk);
		bzero(buffer, chunk);
		
		if (buffer == NULL) {
			
			cout << "Failed to allocate memory." << endl;
			return NULL;
		}
		
		memcpy(buffer, _data, chunk);
		return buffer;
	}

	bool MemoryFile::writeFile(const char* filename) {
		
		FILE* file = fopen(filename, "w");

		if (file == NULL) {

			cout << "Failed to open file (" << filename << ")." << endl;
			return false;
		}

		fwrite(_data, 1, sizeof(_data), file);
		fclose(file);

		return true;
	}

	MemoryFile* MemoryFile::fromPartial(const char* container, const char* filename) {

		cout << "[*] Extracting file using partial-zip" << endl;
		int len = strlen(container);

		char fname[len+7]; //account for file:// if it's missing
		bzero(fname, len+7); // zeroize memory

		//Somebody forgot file:// or http://
		if (strstr(container, "http://") == NULL && strstr(container, "file://") == NULL) {
			
			strcpy(fname, "file://");
		}

		strcat(fname, container);

		ZipInfo* info = PartialZipInit(fname);

		if (info == NULL) {
			
			cout << "[X] Failed to open url: " << fname << " (aborting)" << endl;
			return NULL;
		}

		PartialZipSetProgressCallback(info, callback);
		CDFile* file = PartialZipFindFile(info, filename);

		if (!file) {
			
			cout << "[X] Failed to find file (" << filename << ") in stream (aborting)" << endl;
			return NULL;
		}

		unsigned char* buffer = PartialZipGetFile(info, file);
		int bufferLen = file->size;

		buffer = (unsigned char*)realloc(buffer, bufferLen+1);
		buffer[bufferLen] = '\0';

		return (new MemoryFile(filename, (unsigned char*)buffer));
	}
	
	const char* MemoryFile::getName() {
		
		return _fileName;
	}
}
