/**
  * GreenPois0n Arsenic - Data.h
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

#ifndef DATA_H
#define DATA_H

#include "Node.h"

namespace GP {

class Data: public Node {
public:
	Data(unsigned char* data, unsigned int size);
	virtual ~Data();

	unsigned char* uchar() {
		return (unsigned char*) mData;
	}

	unsigned int size() {
		return mSize;
	}

protected:
	unsigned int mSize;
	unsigned char* mData;
};

}

#endif /* DATA_H */
