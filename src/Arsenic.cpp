/**
 * GreenPois0n Arsenic
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

#include "arsenic.h"

using namespace std;

namespace GP {
	Arsenic* Arsenic::_instance;
	bool Arsenic::_instanceFlag = false;
	
	static struct option longOpts[] = {
		{ "help",    no_argument,       NULL, 'h' },
		{  NULL,     0,                 NULL,  0  }
	};
	
	Arsenic &Arsenic::getInstance() {
		if(! _instanceFlag) {

			_instanceFlag = true;
			_instance = new Arsenic();
		}

		return *_instance;
	}

	int Arsenic::initialize(int argc, char* argv[]) {

		int opt, optIndex;

		if (! (argc >= 2)) {
			usage();
			return ARSENIC_INIT_BAD_ARGS;
		}

		bool shutdown;

		while ((opt = getopt_long(argc, argv, "h", longOpts, &optIndex)) > 0) {

			switch (opt) {
				case 'h':
					usage();
					shutdown = true;
					break;

				default:
					cout << "fail" << endl;
					shutdown = true;
					break;
			}
		}

		if (shutdown)
			return ARSENIC_INIT_SHUTDOWN;

		return ARSENIC_INIT_OK;
	}

	void Arsenic::usage() {

		cout << "Usage: arsenic [OPTIONS] IPSW" << endl;
		cout << "Create and restore custom firmwares file to an iPhone/iPod Touch." << endl;
		cout << "  -h, --help\t\tprints usage information" << endl;
		cout << endl;
	}
}
