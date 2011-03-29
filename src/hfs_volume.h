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

#ifndef HFSVOLUME_H
#define HFSVOLUME_H

#include "common.h"
#include "hfs_common.h"

namespace GP {
	
	class HFSVolume {
	public:
		~HFSVolume();
		
		HFSVolume* open(io_func* io);
		void close();
		void update();
		
		HFSPlusVolumeHeader* readHeader(off_t offset);
		bool writeHeader(HFSPlusVolumeHeader* volumeHeaderToWrite, off_t offset);
		
		void flipForkData(HFSPlusForkData* forkData);
			
	private:
		HFSVolume(io_func* io);
		io_func* _io;
		Volume* _volume;
	};
}
#endif /* HFSVOLUME_H */