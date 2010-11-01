/**
  * GreenPois0n Arsenic - Folder.h
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

#ifndef FOLDER_H
#define FOLDER_H

extern "C" {
	#include <dirent.h>
	#include <sys/types.h>
}

#include <map>

#include "File.h"
#include "String.h"
#include "AbstractFile.h"
#include "AbstractFolder.h"

namespace GP {

typedef std::map<String,AbstractFile*> FileMap;
typedef std::map<String,AbstractFolder*> FolderMap;
typedef std::map<String,AbstractFile*>::iterator FileIterator;
typedef std::map<String,AbstractFolder*>::iterator FolderIterator;

class Folder : public AbstractFolder {
public:
	Folder(DIR* dir, String& path);
	virtual ~Folder();

	static Folder* open(const String& path);
	virtual void close();

	Folder* openFolder(const String& path);
	File* openFile(const String& filename);

	FolderMap* getFolders() {
		return mFolderMap;
	}

	FileMap* getFiles() {
		return mFileMap;
	}

protected:
	DIR* mDir;
	String mPath;
	FileMap* mFileMap;
	FolderMap* mFolderMap;
};

}

#endif /* FOLDER_H */
