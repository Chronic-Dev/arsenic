/**
  * GreenPois0n Arsenic - SHA1.h
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
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

#ifndef SHA1_H
#define SHA1_H

#include <cstring>
#include "AbstractFile.h"

namespace GP {

class SHA1 {
public:
	SHA1(unsigned char* hash = NULL);
	virtual ~SHA1();

	static SHA1* calaculate(AbstractFile* file);
	const unsigned char* getHash();

	bool equals(SHA1* sha) {
		if(!memcmp(mHash, sha->getHash(), 0x20)) {
			return true;
		} else {
			return false;
		}
	}

protected:
	unsigned char* mHash;

};

}

#endif /* SHA1_H */
