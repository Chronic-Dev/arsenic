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

#include "dmg.h"

using namespace std;
using namespace Arsenic::IO;

namespace Arsenic {
	namespace IO {
		
		// Constructor
		DMG::DMG(AbstractFile** in, AbstractFile** out, const char* key, int partition) {
			mIn = *in;
			mKey = key;
			mOut = *out;
			mPartition = partition;
			
			short int word = 0x0001;
			char* byte = (char *) &word;
			mEndianness = byte[0] ? IS_LITTLE_ENDIAN : IS_BIG_ENDIAN;
		}
		
		// Destructor
		DMG::~DMG() {
			if (mIn) {
				free(mIn);
			}
			if (mOut) {
				free(mOut);
			}
			if (mKey) {
				delete mKey;
			}
		}
		
		// Create a DMG
		DMG* DMG::open(const char* source, const char* dest) {
			return open(source, dest, NULL, -1);
		}
		
		DMG* DMG::open(const char* source, const char* dest, int partition) {
			return open(source, dest, NULL, partition);
		}
		
		DMG* DMG::open(const char* source, const char* dest, const char* key) {
			return open(source, dest, key, -1);
		}
		
		DMG* DMG::open(const char* source, const char* dest, const char* key, int partition) {
			AbstractFile* in, out;
			bool hasKey = false;
			
			in = createAbstractFileFromFile(fopen(source, "rb"));
			
			if (in == NULL) {
				LOG4CXX_ERROR(logger, "Failed to open file: " << source);
				return NULL;
			}
			
			out = createAbstractFileFromFile(fopen(dest, "wb"));
			
			if (out == NULL) {
				in->close(in);
				LOG4CXX_ERROR(logger, "Failed to open file: " << dest);
				return NULL;
			}
			
			// Encrypted using filevault
			if (key != NULL) {
				hasKey = true;
				in = createAbstractFileFromFileVault(in, key);
			}
			
			return (new DMG(*in, *out, key, partition));
		}
		
		// DMG operations
		void DMG::extract() {
			extractDmg(mIn, mOut, mPartition);
		}
		
		void DMG::build() {
			build(SECTOR_SIZE);
		}
		
		void DMG::build(int size) {
			buildDmg(mIn, mOut, size);
		}
		
		void DMG::resources() {
			outResources(mIn, mOut);
		}
		
		void DMG::toISO() {
			convertToISO(mIn, mOut);
		}
		
		void DMG::toDMG() {
			convertToDMG(mIn, mOut);
		}
	}
}