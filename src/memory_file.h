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

#ifndef MEMORYFILE_H_
#define MEMORYFILE_H_

#include "common.h"

extern "C" {
	#include <partial/partial.h>
}

namespace GP {

	class MemoryFile {
	public:
		MemoryFile(const char* filename, unsigned char* data);
		~MemoryFile();
		
		// Manipulate
		static MemoryFile* openFile(const char* filename);
		static MemoryFile* openFile(const char* filename, unsigned int chunk);
		static MemoryFile* fromPartial(const char* container, const char* filename);
		int size();
		unsigned char* getData();
		unsigned char* getData(int chunk);
		bool writeFile(const char* filename);
		const char* getName();
		
	private:
		unsigned char* _data;
		const char* _fileName;
		
	};
}

#endif /* MEMORYFILE_H_ */
