/**
* GreenPois0n Arsenic
* Copyright (C) 2010-2011 Chronic-Dev Team
* Copyright (C) 2010 Joshua Hill
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

#include "patch.h"

namespace Arsenic {
	namespace Util {
		
		unsigned char* Patch::find(MemoryFile* file, int length, unsigned char* data, int size) {
			if (!file) {
				LOG4CXX_ERROR(logger, "MemoryFile was null (wtf?)");
				return NULL;
			}
			
			unsigned char* dat = file->readAll();
			
			for (int i = 0; i < length; i++) {
				if (!memcmp(&dat[i], data, size)) {
					LOG4CXX_INFO(logger, "Found patch address" << &dat[i]);
					return &dat[i];
				}
			}
			
			return NULL;
		}
	}
}