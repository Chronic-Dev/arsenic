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

/**
 * HFS based on parts of "xpwn", released under the GPLv3.
 * Modifications will be made available upon request.
 */

#include "common.h"
#include "hfs_volume.h"
#include "memory_file.h"

namespace GP {
	class HFS {
	public:
		HFS();
		~HFS();
		void writeToFile(HFSPlusCatalogFile* file, MemoryFile* output);
		void writeToHFSFile(HFSPlusCatalogFile* file, MemoryFile* input, HFSVolume* volume);
		void fetchFile(const char* inFileName, MemoryFile* output);
		int addFile(MemoryFile* inFile, const char* outFileName);
		void grow(uint64_t newSize);
		void removeAllInFolder(HFSCatalogNodeID folderID, const char* parentName);
		void addAllInFolder(HFSCatalogNodeID folderID, const char* parentName);
		void addAll(const char* dirToMerge, const char* dest);
		void extractFolder(HFSCatalogNodeID folderID);
		int copyToVolume(HFSVolume* target, const char* from, const char* to);
		void untar(MemoryFile* file);
		void ls(const char* path);
	private:
		HFSVolume* _volume;
	};
};