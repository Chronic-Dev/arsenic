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

#include "hfs.h"

namespace GP {
	HFS::HFS(HFSVolume* volume) {
		_volume = volume;
	}
	
	HFS::~HFS() {
		if (_volume != NULL) {
			delete _volume;
		}
	}
	
	//
	// This will need to be rewrote since _volume is an instance of HFSVolume,
	// and the 'Volume' struct is private.
	//
	void HFS::ls(const char* path) {
		HFSPlusCatalogRecord* record;
		char* name;

		record = getRecordFromPath(path, _volume, &name, NULL);

		printf("%s: \n", name);
		if(record != NULL) {
			if(record->recordType == kHFSPlusFolderRecord)
				displayFolder(((HFSPlusCatalogFolder*)record)->folderID, _volume);  
			else
				displayFileLSLine(_volume, (HFSPlusCatalogFile*)record, name);
		} else {
			printf("No such file or directory\n");
		}

		printf("Total filesystem size: %d, free: %d\n", (_volume->volumeHeader->totalBlocks - _volume->volumeHeader->freeBlocks) * volume->volumeHeader->blockSize, volume->volumeHeader->freeBlocks * volume->volumeHeader->blockSize);

		free(record);
	}
}