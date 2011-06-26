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

#include "plist.h"

namespace Arsenic {
	namespace Util {

		// Constructor
		PList::PList(MemoryFile* file) {
			mFile = file;

			if (!mFile) {
				LOG4CXX_WARN(logger, "MemoryFile was null (wtf?)");
				return;
			}

			// Binary PList?
			if (memcmp((char*)file->readAll(), "bplist00", 8) == 0) {
				char* out = NULL;

				uint32_t size = 0;

				plist_from_bin((char*)file->readAll(), file->size(), &mPList);
				plist_to_xml(mNode, &out, &size);

				file->write((unsigned char*)out);
				free(out);
			}

			if (mPList != NULL) {
				plist_free(mPList);
			}

			plist_from_xml((char*)file->readAll(), file->size(), &mPList);
			
			mType = plist_get_node_type(mPList);
			mNode = Node::fromPlist(mPList, NULL);
		}

		// Destructor
		PList::~PList() {
			if (mNode) {
				delete mNode;
			}
			
			if (mPList) {
				plist_free(mPList);
				mPList = NULL;
			}

			if (mFile) {
				delete mFile;
			}
		}

		// PList operations
		Node* PList::getNode() {
			return mNode;
		}
	}
}