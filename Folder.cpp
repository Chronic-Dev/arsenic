/**
  * GreenPois0n Arsenic - Folder.cpp
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

#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include "Folder.h"
#include "File.h"

namespace GP {

Folder::Folder(DIR* dir, String* path) :
	mDir(dir), mPath(path) {
	mFileMap = new FileMap();
	mFolderMap = new FolderMap();
	struct dirent* dp = NULL;
	while ((dp = readdir(dir))) {
		if (dp->d_type == DT_DIR) {
			if (!strcmp(dp->d_name, "..") || !strcmp(dp->d_name, ".")) {
				continue;
			}
			const char* name = strdup(dp->d_name);
			int new_size = strlen(name) + strlen(path) + 2;
			char* path_name = new char[new_size];
			snprintf(path_name, new_size, "%s/%s", path, name);
			mFolderMap->operator[](name) = Folder::open(path_name);
		}
		if (dp->d_type == DT_REG) {
			const char* name = strdup(dp->d_name);
			int new_size = strlen(name) + strlen(path) + 2;
			char* path_name = new char[new_size];
			snprintf(path_name, new_size, "%s/%s", path, name);
			mFileMap->operator[](name) = File::open(path_name);
		}
	}
}

Folder::~Folder() {
	if (mDir)
		this->close();
	if (mFolderMap)
		delete mFolderMap;
	if(mFileMap)
		delete mFileMap;
}

Folder* Folder::open(String* path) {
	DIR* dir = opendir(path);
	if (dir == 0) {
		return 0;
	}
	Folder* folder = new Folder(dir, path);
	return folder;
}

void Folder::close() {
	if (mDir) {
		closedir(mDir);
		mDir = 0;
	}
}

Folder* Folder::openFolder(String* path) {
	FolderIterator it = mFolderMap->find(path);
	if(it == mFolderMap->end()) {
		return NULL;
	}
	return (Folder*) it->second;
}

AbstractFile* Folder::openFile(String* filename) {
	FileIterator iter = mFileMap->begin();
	for(iter = mFileMap->begin(); iter != mFileMap->end(); ++iter) {
		const char* filename2 = (const char*) iter->first;
		if(!strcmp(filename, filename2)) {
			return iter->second;
		}
	}

	return 0;
}

}
