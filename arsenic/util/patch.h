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

#ifndef ARSENIC_UTIL_PATCH_H_
#define ARSENIC_UTIL_PATCH_H_

#include "../core/common.h"
#include "../io/memoryfile.h"

using namespace Arsenic::IO;

namespace Arsenic {
	namespace Util {
		class Patch {
			public:
				static uint32_t find(MemoryFile* file, unsigned char* data, int size);
				static bool apply(MemoryFile* file, uint32_t offset, unsigned char* data);
			//private:	
		};
	}
}

#endif /* ARSENIC_UTIL_PATCH_H_ */