/**
* GreenPois0n Arsenic
* Copyright (C) 2010-2011 Chronic-Dev Team
* Copyright (C) 2010-2011 GreySyntax
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

#include "arsenic.h"
#include "common.h"
#include "abstract_file.h"
#include "hfs_plus.h"
#include "hfs_lib.h"

using namespace std;
using namespace GP;

char endianness;

int shutdown(const char* message, int code) {

	cout << "[X] " << message << endl;
	exit(code);
}

int main(int argc, char* argv[]) {

	cout << endl;
	cout << "GreenPois0n Arsenic (" << PACKAGE_STRING << ")" << endl;
	cout << "Copyright (C) 2010-2011 Chronic-Dev Team (" << PACKAGE_BUGREPORT << ")" << endl;
	cout << endl;

	cout << "This program is free software: you can redistribute it and/or modify" << endl;
	cout << "it under the terms of the GNU General Public License as published by" << endl;
	cout << "the Free Software Foundation, either version 3 of the License, or" << endl;
	cout << "(at your option) any later version." << endl;
	cout << endl;

	Arsenic arsenic = Arsenic::getInstance();

	int ret;

	if ((ret = arsenic.initialize(argc, argv)) != ARSENIC_INIT_OK && ret != ARSENIC_INIT_SHUTDOWN) {
		
		shutdown("Failed to initialize arsenic", -1);
	}
	
	io_func* io;
	Volume* volume;
	
	io = openFlatFile("rootfs2.dmg");
	TestByteOrder();
	
	if (io == NULL) {
		
		shutdown("Cannot open image", -1);
	}
	
	volume = openVolume(io);
	
	if (volume == NULL) {
		
		shutdown("Cannot open volume", -1);
	}
	
	//debugBTree(volume->catalogTree, TRUE);
	hfs_ls(volume, "/Applications");
	
	closeVolume(volume);
	CLOSE(io);
	return 0;
}
