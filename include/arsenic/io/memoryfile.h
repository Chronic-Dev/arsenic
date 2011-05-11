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

#ifndef ARSENIC_IO_MEMORYFILE_
#define ARSENIC_IO_MEMORYFILE_
namespace Arsenic {
	namespace IO {
		#define ARSENIC_IO_MEMORYFILE_READ "r"
		#define ARSENIC_IO_MEMORYFILE_WRITE "w"
		#define ARSENIC_IO_MEMORYFILE_READ_WRITE "r+"
		#define ARSENIC_IO_MEMORYFILE_READ_WRITE_DESTROY "w+"
		#define ARSENIC_IO_MEMORYFILE_APPEND "a"
		#define ARSENIC_IO_MEMORYFILE_APPEND_CONT "a+"
		
		class MemoryFile {
		public:
			// Destructor
			~MemoryFile();
			
			// Create a MemoryFile
			static MemoryFile* open(const char* filename, int flags);
			static MemoryFile* openPartial(const char* container, const char* filename);
			
			// Read file
			unsigned char* read(int length);
			unsigned char* readAll();
			
			// File operations
			bool write(unsigned char* data);
			void toFile(const char* file);
			bool save();
			bool save(int flags);
			int size();
			
		private:
			// Constructor
			MemoryFile(const char* file, unsigned char* data);
			
			const char* mFile;
			const char* mData;
		};
	}
}
#endif /* ARSENIC_IO_MEMORYFILE_ */