/**
  * GreenPois0n Arsenic - PList.h
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

#ifndef PLIST_H
#define PLIST_H

#include "AbstractFile.h"
#include "Dictionary.h"
#include "Node.h"

namespace GP {

class PList {
public:
	virtual ~PList();

	static PList* open(AbstractFile* file);
	Node* findNode(const char* key);

private:
	PList();

protected:
	Dictionary* mRoot;
	AbstractFile* mFile;
	unsigned int mSize;
	unsigned char* mData;
};

}

#endif /* PLIST_H */
