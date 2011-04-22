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

#include "common.h"
#include "plist.h"

extern "C" {
	#include <dirent.h>
}

namespace GP {

	class Bundle {

	public:
		Bundle(const char* productType, const char* productBuild, PList* bundleMap);
		~Bundle();

		static bool exists(const char* productType, const char* productBuild);

	private:
		const char* _type;
		const char* _build;
		PList* _plist;
	};
}
