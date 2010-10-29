/**
  * GreenPois0n Arsenic - Arsenic.h
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

#ifndef ARSENIC_H
#define ARSENIC_H

#include "Common.h"
#include "String.h"
#include "Folder.h"
#include "Firmware.h"

namespace GP {

class Arsenic {
public:
	Arsenic();
	virtual ~Arsenic();

	int initialize(int argc, char* argv[]);
	void shutdown();
	void usage();
	int run();

private:
	String* mIPSW;
	Folder* mBundles;
	Firmware* mFirmware;
};

}

#endif /* ARSENIC_H */
