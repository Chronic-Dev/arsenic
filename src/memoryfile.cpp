/**
 * GreenPois0n Arsenic
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

#include "MemoryFile.h"

using namespace std;
	
namespace GP {
	
	MemoryFile::MemoryFile(const char* filename, unsigned char* data) {
	
		_fileName = filename;
		_data = data;
	}
	
	MemoryFile* MemoryFile::openFile(const char* filename) {
		
		FILE* file = fopen(filename, 'r');
		
		if (file == NULL) {
			
			cout << "Failed to open file (" << filename << ")." << endl;
			return NULL;
		}
		
		fseek(file, 0, SEEK_END);
		unsigned int len = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		char* data = malloc(len);
		
		if (data == NULL) {
			
			cout << "Failed to allocate memory." << endl;
			return NULL;
		}
		
		fread(data, 1, len, file);
		fclose(file);
		
		return (new MemoryFile(filename, (const char*)data));
	}
	
	unsigned char &MemoryFile::getData() {
		
		return *_data;
	}
	
	bool MemoryFile::writeFile(const char* filename) {
		
		FILE* file = fopen(filename, 'w');
		
		if (file == NULL) {
			
			cout << "Failed to open file (" << filename << ")." << endl;
			return false;
		}
		
		fwrite(_data, 1, sizeof(_data), file);
		fclose(file);
		
		return true;
	}
}