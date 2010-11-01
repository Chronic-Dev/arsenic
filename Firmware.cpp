/**
  * GreenPois0n Arsenic - Firmware.cpp
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

#include "Firmware.h"
#include "ZipFile.h"
#include "SHA1.h"

namespace GP {

Firmware::Firmware(AbstractFile* file) :
	mFile(file) {
}

Firmware::~Firmware() {
	if(mFile) {
		delete mFile;
		mFile = 0;
	}
}

Firmware* Firmware::openAbstractFile(AbstractFile* file) {
	return new Firmware(file);
}

SHA1* Firmware::getSha1() {
	return mHash;
}

}
