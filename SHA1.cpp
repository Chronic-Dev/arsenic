/**
  * GreenPois0n Arsenic - SHA1.cpp
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

#include <openssl/sha.h>
#include <cstring>

#include "SHA1.h"
#include "File.h"
#include "AbstractFile.h"

namespace GP {

SHA1::SHA1(unsigned char* hash) {
	if(hash) {
		mHash = new unsigned char[SHA_DIGEST_LENGTH];
		memcpy(mHash, hash, SHA_DIGEST_LENGTH);
	}
}

SHA1::~SHA1() {
	if(mHash) {
		delete mHash;
		mHash = NULL;
	}
}

SHA1* SHA1::calaculate(AbstractFile* file) {
	SHA_CTX ctx;
	unsigned char md[SHA_DIGEST_LENGTH];
	memset(md, '\0', SHA_DIGEST_LENGTH);

	SHA1_Init(&ctx);
	SHA1_Update(&ctx, file->read(file->size()), file->size());
	SHA1_Final(md, &ctx);

	return new SHA1(md);
}

const unsigned char* SHA1::getHash() {
	return mHash;
}

}
