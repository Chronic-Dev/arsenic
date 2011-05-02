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

#include "hfs_volume.h"

using namespace std;

namespace GP {
	
	HFSVolume::HFSVolume(io_func* io) {
		
		if ((_io == io) == NULL) {
			
			return NULL;
		}
		
		Volume* volume;
		io_func* file;

		volume = (Volume*) malloc(sizeof(Volume));
		volume->image = io;
		volume->extentsTree = NULL;

		volume->volumeHeader = readHeader(1024);
		
		if(volume->volumeHeader == NULL) {
			
			free(volume);
			return NULL;
		}

		file = openRawFile(kHFSExtentsFileID, &volume->volumeHeader->extentsFile, NULL, volume);
		
		if(file == NULL) {
			
			free(volume->volumeHeader);
			free(volume);
			return NULL;
		}

		volume->extentsTree = openExtentsTree(file);
		
		if(volume->extentsTree == NULL) {
			
			free(volume->volumeHeader);
			free(volume);
			return NULL;
		}

		file = openRawFile(kHFSCatalogFileID, &volume->volumeHeader->catalogFile, NULL, volume);
		
		if(file == NULL) {
			
			closeBTree(volume->extentsTree);
			free(volume->volumeHeader);
			free(volume);
			return NULL;
		}

		volume->catalogTree = openCatalogTree(file);
		
		if(volume->catalogTree == NULL) {
			
			closeBTree(volume->extentsTree);
			free(volume->volumeHeader);
			free(volume);
			return NULL;
		}

		volume->allocationFile = openRawFile(kHFSAllocationFileID, &volume->volumeHeader->allocationFile, NULL, volume);
		
		if(volume->allocationFile == NULL) {
			
			closeBTree(volume->catalogTree);
			closeBTree(volume->extentsTree);
			free(volume->volumeHeader);
			free(volume);
			return NULL;
		}

		volume->attrTree = NULL;
		file = openRawFile(kHFSAttributesFileID, &volume->volumeHeader->attributesFile, NULL, volume);
		
		if(file != NULL) {
			
			volume->attrTree = openAttributesTree(file);
			
			if(!volume->attrTree) {
				
				CLOSE(file);
			}
		}

		volume->metadataDir = getMetadataDirectoryID(volume);
		_volume = volume;
		_io = io;
	}
	
	HFSVolume::~HFSVolume() {
		
		if (_volume != NULL) {
			
			close();
			free(_volume);
		}
		
		if (_io != NULL) {
			
			free(_io);
		}
	}
	
	HFSVolume* HFSVolume::open(io_func* io) {
		
		return (new HFSVolume(io));
	}
	
	void HFSVolume::close() {
		
		if(_volume->attrTree) {
			
			closeBTree(_volume->attrTree);
		}

		CLOSE(_volume->allocationFile);
		closeBTree(_volume->catalogTree);
		closeBTree(_volume->extentsTree);
		free(_volume->volumeHeader);
		free(_volume);
	}
	
	void HFSVolume::update() {
		
		ASSERT(writeVolumeHeader(volume->image, volume->volumeHeader, ((off_t)volume->volumeHeader->totalBlocks * (off_t)volume->volumeHeader->blockSize) - 1024), "HFSVolume::writeHeader");
		return writeHeader(volume->image, volume->volumeHeader, 1024);
	}
	
	HFSPlusVolumeHeader* HFSVolume::readHeader(off_t offset) {
		
		HFSPlusVolumeHeader* volumeHeader;

		volumeHeader = (HFSPlusVolumeHeader*) malloc(sizeof(HFSPlusVolumeHeader));

		if(!(READ(_io, offset, sizeof(HFSPlusVolumeHeader), volumeHeader))) {
			
			return NULL;
		}

		FLIPENDIAN(volumeHeader->signature);
		FLIPENDIAN(volumeHeader->version);
		FLIPENDIAN(volumeHeader->attributes);
		FLIPENDIAN(volumeHeader->lastMountedVersion);
		FLIPENDIAN(volumeHeader->journalInfoBlock);
		FLIPENDIAN(volumeHeader->createDate);
		FLIPENDIAN(volumeHeader->modifyDate);
		FLIPENDIAN(volumeHeader->backupDate);
		FLIPENDIAN(volumeHeader->checkedDate);
		FLIPENDIAN(volumeHeader->fileCount);
		FLIPENDIAN(volumeHeader->folderCount);
		FLIPENDIAN(volumeHeader->blockSize);
		FLIPENDIAN(volumeHeader->totalBlocks);
		FLIPENDIAN(volumeHeader->freeBlocks);
		FLIPENDIAN(volumeHeader->nextAllocation);
		FLIPENDIAN(volumeHeader->rsrcClumpSize);
		FLIPENDIAN(volumeHeader->dataClumpSize);
		FLIPENDIAN(volumeHeader->nextCatalogID);
		FLIPENDIAN(volumeHeader->writeCount);
		FLIPENDIAN(volumeHeader->encodingsBitmap);


		flipForkData(&volumeHeader->allocationFile);
		flipForkData(&volumeHeader->extentsFile);
		flipForkData(&volumeHeader->catalogFile);
		flipForkData(&volumeHeader->attributesFile);
		flipForkData(&volumeHeader->startupFile);

		return volumeHeader;
	}
	
	bool HFSVolume::writeHeader(HFSPlusVolumeHeader* volumeHeaderToWrite, off_t offset) {
		HFSPlusVolumeHeader* volumeHeader;

		volumeHeader = (HFSPlusVolumeHeader*) malloc(sizeof(HFSPlusVolumeHeader));
		memcpy(volumeHeader, volumeHeaderToWrite, sizeof(HFSPlusVolumeHeader));

		FLIPENDIAN(volumeHeader->signature);
		FLIPENDIAN(volumeHeader->version);
		FLIPENDIAN(volumeHeader->attributes);
		FLIPENDIAN(volumeHeader->lastMountedVersion);
		FLIPENDIAN(volumeHeader->journalInfoBlock);
		FLIPENDIAN(volumeHeader->createDate);
		FLIPENDIAN(volumeHeader->modifyDate);
		FLIPENDIAN(volumeHeader->backupDate);
		FLIPENDIAN(volumeHeader->checkedDate);
		FLIPENDIAN(volumeHeader->fileCount);
		FLIPENDIAN(volumeHeader->folderCount);
		FLIPENDIAN(volumeHeader->blockSize);
		FLIPENDIAN(volumeHeader->totalBlocks);
		FLIPENDIAN(volumeHeader->freeBlocks);
		FLIPENDIAN(volumeHeader->nextAllocation);
		FLIPENDIAN(volumeHeader->rsrcClumpSize);
		FLIPENDIAN(volumeHeader->dataClumpSize);
		FLIPENDIAN(volumeHeader->nextCatalogID);
		FLIPENDIAN(volumeHeader->writeCount);
		FLIPENDIAN(volumeHeader->encodingsBitmap);


		flipForkData(&volumeHeader->allocationFile);
		flipForkData(&volumeHeader->extentsFile);
		flipForkData(&volumeHeader->catalogFile);
		flipForkData(&volumeHeader->attributesFile);
		flipForkData(&volumeHeader->startupFile);

		if(!(WRITE(_io, offset, sizeof(HFSPlusVolumeHeader), volumeHeader))) {
			
			return false;
		}

		free(volumeHeader);
		
		return true;
	}
	
	void HFSVolume::flipForkData(HFSPlusForkData* forkData) {
		
		FLIPENDIAN(forkData->logicalSize);
		FLIPENDIAN(forkData->clumpSize);
		FLIPENDIAN(forkData->totalBlocks);
		flipExtentRecord(&forkData->extents);
	}
}