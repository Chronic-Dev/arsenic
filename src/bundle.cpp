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

#include "bundle.h"

using namespace std;

namespace GP {

	Bundle::Bundle(const char* productType, const char* productBuild, const char* bundleMap) {

		//Create the bundle map
		_plist = new PList(bundleMap);
		_build = productBuild;
		_type = productType;
	}

	Bundle::~Bundle() {
		
		delete _plist;
		delete _build;
		delete _type;
	}

	bool Bundle::exists(const char* productType, const char* productBuild) {

		char bundle[200];
		bzero(bundle, sizeof(bundle)); //Fixes issues with some linux builds

		bool exists = false;
		DIR *dir = NULL;

		strcpy(bundle, "./bundles/");
		strcat(bundle, productType);
		strcat(bundle, "/");
		strcat(bundle, productBuild);
		strcat(bundle, ".bundle");

		if ((dir = opendir(bundle)) != NULL) {

			exists = true;
			(void)closedir(dir);
		}

		return exists;
	}
}
