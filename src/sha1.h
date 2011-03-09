/**
* GreenPois0n Arsenic
* Copyright (C) 2010 Chronic-Dev Team
* Copyright (C) 2010 GreySyntax
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

#ifndef SHA1_H_
#define SHA1_H_

#include "common.h"
#include "memoryfile.h"

namespace GP {

	class SHA1 {

	public:
        static SHA1* calculate(MemoryFile* file);
        unsigned char* getHash();
        bool equals(SHA1* compare);
        
	private:
		unsigned char* _hash;
        
        SHA1(const char* hash);
        ~SHA1();
	};
}
#endif /* SHA1_H_ */
