/**
  * GreenPois0n Arsenic - File.h
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

#ifndef FILE_H
#define FILE_H

#include <string>
#include <cstdio>

#include "String.h"
#include "AbstractFile.h"

namespace GP {

class File: public AbstractFile {
public:
	virtual ~File();
	static File* open(String& filename);
	static File* create(String& filename);

	virtual void close();
	virtual unsigned int size();
	virtual unsigned char* read(unsigned int size);
	virtual unsigned int write(unsigned char* buffer, unsigned int size);

private:
	File();

protected:
	int mSize;
	FILE* mFile;
	String mFilename;
};

}

#endif /* FILE_H */
