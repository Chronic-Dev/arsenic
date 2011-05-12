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

#include "memoryfile.h"

using namespace std;
using namespace Arsenic::IO;

namespace Arsenic {
	namespace IO {
		
		void partial_zip_callback(ZipInfo* info, CDFile* file, size_t progress) {

			int percentDone = progress * 100/file->compressedSize;
			LOG4CXX_INFO(logger, "Getting: " << percentDone);
		}
		
		// Constructor
		MemoryFile::MemoryFile(const char* file, unsigned char* data) {
			mFile = file;
			mData = data;
		}
		
		// Destructor
		MemoryFile::~MemoryFile() {
			if (mData) {
				free(mData);
			}
			if (mFile) {
				delete mFile;
			}
		}
		
		// Create a MemoryFile
		MemoryFile* MemoryFile::open(const char* filename, const char* flags) {
			FILE* file = fopen(filename, flags);
			
			if (file == NULL) {
				LOG4CXX_ERROR(logger, "Failed to open file: " << filename);
				return NULL;
			}
			
			fseek(file, 0, SEEK_END);
			unsigned int length = ftell(file);
			fseek(file, 0, SEEK_SET);
			
			char* data = (char*)calloc(length, sizeof(char));
			fclose(file);
			
			if (data == NULL) {
				LOG4CXX_ERROR(logger, "Failed to allocate memory");
				return NULL;
			}
			
			fread(data, 1, length, file);
			fclose(file);
			
			return (new MemoryFile(filename, (unsigned char*)data));
		}
		
		MemoryFile* MemoryFile::openPartial(const char* container, const char* filename) {
			int length = strlen(container);
			char fname[length+7];
			
			// Just to be sure
			bzero(fname, length+7);
			
			// Somebody forgot to specify the protocol, presume they want the file protocol
			if (strstr(container, "http://") == NULL && strstr(container, "file://") == NULL) {
				strcpy(fname, "file://");
			}
			
			strcat(fname, container);
			ZipInfo* info = PartialZipInit(fname);
			
			if (info == NULL) {
				LOG4CXX_ERROR(logger, "Failed to open url: " << fname);
				return NULL;
			}
			
			PartialZipSetProgressCallback(info, partial_zip_callback);
			CDFile* file = PartialZipFindFile(info, filename);
			
			if (!file) {
				LOG4CXX_ERROR(logger, "Failed to find file: " << filename << " in the stream");
				return NULL;
			}
			
			unsigned char* data = PartialZipGetFile(info, file);
			int dataLength = file->size;
			
			data = (unsigned char*)realloc(data, dataLength+1);
			data[dataLength] = '\0';
			
			return new MemoryFile(filename, data);
		}
		
		// Read file
		unsigned char* MemoryFile::read(int length) {
			
			// Yo Dawg, your reading a file in a file in a file
			if (length > strlen((const char*)mData)) {
				return NULL;
			}
			
			char* buffer = (char*)calloc(length, sizeof(char));
			
			if (buffer == NULL) {
				LOG4CXX_ERROR(logger, "Failed to allocate memory");
				return NULL;
			}
			
			memcpy(buffer, mData, length);
			
			return (unsigned char*)buffer;
		}
		
		unsigned char* MemoryFile::readAll() {
			return mData;
		}
	}
}