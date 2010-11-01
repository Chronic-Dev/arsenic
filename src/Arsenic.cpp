/**
  * GreenPois0n Arsenic - Arsenic.cpp
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
	#include <getopt.h>
}

#include <iostream>

#include "PList.h"
#include "Device.h"
#include "Arsenic.h"
#include "Firmware.h"

namespace GP {

Arsenic::Arsenic() : mIPSW("") {
}

Arsenic::~Arsenic() {
}

static struct option longopts[] = {
	{ "help",    no_argument,       NULL, 'h' },
	{  NULL,     0,                 NULL,  0  }
};

/*
 * print program arguments and options
 */
void Arsenic::usage() {
	std::cout << "Usage: arsenic [OPTIONS] IPSW" << std::endl;
	std::cout << "Create and restore custom firmwares file to an iPhone/iPod Touch." << std::endl;
	std::cout << "  -h, --help\t\tprints usage information" << std::endl;
	std::cout << std::endl;
}

/*
 * parse command line arguments and set up variables need in run
 */
int Arsenic::initialize(int argc, char* argv[]) {
	int opt = 0;
	int optindex = 0;

	while ((opt = getopt_long(argc, argv, "h", longopts, &optindex)) > 0) {
		switch (opt) {
		case 'h':
			usage();
			return 0;

		default:
			return -1;
		}
	}

	if ((argc-optind) == 1) {
		argc -= optind;
		argv += optind;

		mIPSW.set(argv[0]);

	} else {
		return -1;
	}

	return 0;
}

/*
 * clean up anything that was done in initialize()
 */
void Arsenic::shutdown() {
	if(mBundles) {
		delete mBundles;
		mBundles = NULL;
	}

	if(mFirmware) {
		delete mFirmware;
		mFirmware = NULL;
	}
}

/*
 * create the custom firmware
 */
int Arsenic::run() {
	// make sure we've been initialize correctly
	if(mIPSW.compare("")) {
		std::cerr << "No IPSW has been set" << std::endl;
		return -1;
	}

	std::cout << "Opening IPSW" << std::endl;
	mFirmware = Firmware::openAbstractFile(ZipFile::openFile(mIPSW));
	if(mFirmware == NULL) {
		std::cerr << "Unable to find IPSW" << std::endl;
		return -1;
	}

	std::cout << "Detecting device" << std::endl;
	mDevice = Device::open();
	if(mDevice == NULL) {
		std::cerr << "Unable to open device" << std::endl;
		return -1;
	}

	std::cout << "Searching for bundle" << std::endl;
	mBundles = Folder::open(String("Bundles"));
	if(mBundles == NULL) {
		std::cerr << "Unable to find bundles" << std::endl;
		return -1;
	}

	FolderIterator it;
	FolderMap* mBundleMap = mBundles->getFolders();
	for(it = mBundleMap->begin(); it != mBundleMap->end(); ++it) {
		Folder* folder = (Folder*) it->second;
		File* infoFile = folder->openFile(String("Info.plist"));
		PList* infoPlist = PList::open(infoFile);
		String* bundleSha1 = (String*) infoPlist->findNode(String("SHA1"));
	}

	// find necessary firmwarebundle
	// parse firmwarebundle
	// unzip ipsw
	// parse buildmanifest
	// send tss request
	// patch firmware files
	// patch ramdisk
	// patch filesystem
	// restore firmware to device
	return 0;
}

}
