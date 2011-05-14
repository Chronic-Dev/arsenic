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

#ifndef ARSENIC_IO_DMG_
#define ARSENIC_IO_MEMORYFILE_

#include "../core/common.h"

extern "C" {
	#include <xpwn-hfs-1.0/common.h>
	#include <xpwn-hfs-1.0/abstractfile.h>
	#include <xpwn-hfs-1.0/dmg.h>
	#include <xpwn-hfs-1.0/filevault.h>
}

namespace Arsenic {
	namespace IO {
		
		class DMG {
		public:
			// Destructor
			~DMG();
			
			// Create a DMG
			static DMG* open(const char* source, const char* dest);
			static DMG* open(const char* source, const char* dest, int partition);
			static DMG* open(const char* source, const char* dest, const char* key);
			static DMG* open(const char* source, const char* dest, const char* key, int partition);
			
			// DMG operations
			void extract();
			void build();
			void build(int size);
			void resources();
			void toISO();
			void toDMG();
			
		private:
			// Constructor
			DMG(AbstractFile* in, AbstractFile* out, const char* key, int partition);
			
			int mPartition;
			const char* mKey;
			char mEndianness;
			AbstractFile* mIn;
			AbstractFile* mOut;
		};
	}
}
#endif /* ARSENIC_IO_DMG_ */