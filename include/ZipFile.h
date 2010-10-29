/**
  * GreenPois0n Arsenic - ZipFile.h
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

#ifndef ZIPFILE_H
#define ZIPFILE_H

#include <cstdlib>
#include <zip.h>
#include <stdint.h>
#include <plist/plist.h>
#include "AbstractFile.h"

#define BUFSIZE 0x100000

namespace GP {

class ZipFile {
public:
	ZipFile(struct zip* zip, const char* filename) :
		mFile(zip), mFilename(filename) {

	}
	virtual ~ZipFile();

	static ZipFile* open(const char* filename) {
		int err = 0;
		struct zip* zip = zip_open(filename, 0, &err);
		if (zip == NULL) {
			return NULL;
		}

		return new ZipFile(zip, filename);
	}

	int extract_to_file(const char* ipsw, const char* infile,
			const char* outfile) {

		int zindex = zip_name_locate(mFile, infile, 0);
		if (zindex < 0) {
			return -1;
		}

		struct zip_stat zstat;
		zip_stat_init(&zstat);
		if (zip_stat_index(mFile, zindex, 0, &zstat) != 0) {
			return -1;
		}

		char* buffer = (char*) malloc(BUFSIZE);
		if (buffer == NULL) {
			return -1;
		}

		struct zip_file* zfile = zip_fopen_index(mFile, zindex, 0);
		if (zfile == NULL) {
			return -1;
		}

		FILE* fd = fopen(outfile, "wb");
		if (fd == NULL) {
			zip_fclose(zfile);
			return -1;
		}

		int i = 0;
		int size = 0;
		int bytes = 0;
		int count = 0;
		double progress = 0;
		for (i = zstat.size; i > 0; i -= count) {
			if (i < BUFSIZE)
				size = i;
			else
				size = BUFSIZE;
			count = zip_fread(zfile, buffer, size);
			if (count < 0) {
				zip_fclose(zfile);
				free(buffer);
				return -1;
			}
			fwrite(buffer, 1, count, fd);

			bytes += size;
			progress = ((double) bytes / (double) zstat.size) * 100.0;
			//print_progress_bar(progress);
		}

		fclose(fd);
		zip_fclose(zfile);
		//close(archive);
		free(buffer);
		return 0;
	}

	int extract_to_memory(const char* ipsw, const char* infile, char** pbuffer,
			int* psize) {
		int zindex = zip_name_locate(mFile, infile, 0);
		if (zindex < 0) {
			return -1;
		}

		struct zip_stat zstat;
		zip_stat_init(&zstat);
		if (zip_stat_index(mFile, zindex, 0, &zstat) != 0) {
			return -1;
		}

		struct zip_file* zfile = zip_fopen_index(mFile, zindex, 0);
		if (zfile == NULL) {
			return -1;
		}

		int size = zstat.size;
		char* buffer = (char*) malloc(size);
		if (buffer == NULL) {
			zip_fclose(zfile);
			return -1;
		}

		if (zip_fread(zfile, buffer, size) != size) {
			zip_fclose(zfile);
			free(buffer);
			return -1;
		}

		zip_fclose(zfile);
		//close(archive);

		*pbuffer = buffer;
		*psize = size;
		return 0;
	}

	int extract_build_manifest(const char* ipsw, plist_t* buildmanifest) {
		int size = 0;
		char* data = NULL;

		/* older devices don't require personalized firmwares and use a BuildManifesto.plist */
		if (extract_to_memory(ipsw, "BuildManifesto.plist", &data, &size)
				== 0) {
			plist_from_xml(data, size, buildmanifest);
			return 0;
		}

		data = NULL;
		size = 0;

		/* whereas newer devices do not require personalized firmwares and use a BuildManifest.plist */
		if (extract_to_memory(ipsw, "BuildManifest.plist", &data, &size)
				== 0) {
			plist_from_xml(data, size, buildmanifest);
			return 0;
		}

		return -1;
	}

	void close() {
		if (mFile != NULL) {
			zip_unchange_all(mFile);
			zip_close(mFile);
		}
	}

protected:
	struct zip* mFile;
	const char* mFilename;

};

}

#endif /* ZIPFILE_H */
