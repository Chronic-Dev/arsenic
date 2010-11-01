/**
  * GreenPois0n Arsenic - ZipFile.h
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

#ifndef ZIPFILE_H
#define ZIPFILE_H

extern "C" {
	#include <zip.h>
	#include <stdint.h>
	#include <plist/plist.h>
}

#include <cstdlib>

#include "String.h"
#include "AbstractFile.h"

#define BUFSIZE 0x100000

namespace GP {

class ZipFile : public AbstractFolder {
public:
	virtual ~ZipFile();

	AbstractFile* openFile(const String& filename);
	void close();

	int extract_to_file(String& ipsw, String& infile, String& outfile);
	int extract_to_memory(String& ipsw, String& infile, char** pbuffer, int* psize);
	int extract_build_manifest(String& ipsw, plist_t* buildmanifest);

protected:
	ZipFile(struct zip* zip, String& filename);

	struct zip* mFile;
	String* mFilename;


};

}

#endif /* ZIPFILE_H */
