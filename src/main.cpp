/**
  * GreenPois0n Arsenic - main.cpp
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

#include "Arsenic.h"

using namespace GP;

int main(int argc, char* argv[]) {
	int ret = 0;
	Arsenic arsenic;
	if(!arsenic.initialize(argc, argv)) {
		ret = arsenic.run();
	} else {
		arsenic.usage();
	}
	arsenic.shutdown();
	return ret;
}

