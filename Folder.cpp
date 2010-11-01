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

extern "C" {
	#include <dirent.h>
	#include <sys/types.h>
}

#include <cstring>

#include "String.h"
#include "Folder.h"
#include "File.h"

namespace GP {

Folder::Folder(DIR* dir, String& path) :
	mDir(dir), mPath(path) {
	mFileMap = new FileMap();
	mFolderMap = new FolderMap();
	struct dirent* dp = NULL;
	while ((dp = readdir(dir))) {
		if (dp->d_type == DT_DIR) {
			if (!strcmp(dp->d_name, "..") || !strcmp(dp->d_name, ".")) {
				continue;
			}
			String name(dp->d_name);
			int new_size = name.length() + path.length() + 2;
			name.concat("/");
			name.concat(name);
			//char* path_name = new char[new_size];
			//snprintf(path_name, new_size, "%s/%s", path, name);
			//mFolderMap->operator[](name) = Folder::open(String(path_name));
		}
		if (dp->d_type == DT_REG) {
			//String name(dp->d_name);
			//int new_size = name.length() + path.length() + 2;
			//char* path_name = new char[new_size];
			//snprintf(path_name, new_size, "%s/%s", path, name);
			//mFileMap->operator[](name) = File::open(String(path_name));
		}
	}
}

Folder::~Folder() {
	if (mDir) {
		this->close();
	}
	if (mFolderMap) {
		delete mFolderMap;
		mFolderMap = NULL;
	}
	if(mFileMap) {
		delete mFileMap;
		mFileMap = NULL;
	}
}

Folder* Folder::open(const String& path) {
	DIR* dir = opendir(path.get());
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

Folder* Folder::openFolder(const String& path) {
	FolderIterator it = mFolderMap->find(path.get());
	if(it == mFolderMap->end()) {
		return NULL;
	}
	return (Folder*) it->second;
}

File* Folder::openFile(const String& filename) {
	FileIterator iter = mFileMap->begin();
	for(iter = mFileMap->begin(); iter != mFileMap->end(); ++iter) {
		if(filename.compare(iter->first)) {
			return iter->second;
		}
	}

	return 0;
}

}
