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

using namespace std;

namespace GP {

	Arsenic* Arsenic::_instance;
	bool Arsenic::_instanceFlag = false;

	static struct option longOpts[] = {
		{ "help",     0,	NULL, 'h' },
		{ "version",  0,	NULL, 'v' },
		{ "ipsw",     1,	NULL, 'i' },
		{  NULL,      0,	NULL,  0  }
	};


	Arsenic::~Arsenic() {

		if (_productBuild != NULL) {
			free(_productBuild);
		}
		
		if (_productType != NULL) {
			free(_productType);
		}
	}

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
			return ARSENIC_INIT_SHUTDOWN;
		}

		int shutdown = ARSENIC_INIT_SHUTDOWN;

		//Bundle* test = new Bundle(NULL, NULL, "./bundles/map.plist");

		while ((opt = getopt_long(argc, argv, "hvi:", longOpts, &optIndex)) > 0) {

			switch (opt) {
				case 'h':
				usage();
				shutdown = ARSENIC_INIT_SHUTDOWN;
				break;

				case 'i':
				_ipswName = optarg;
				_ipsw = PList::fromPartial(_ipswName, "Restore.plist");

				if (_ipsw == NULL) {

					cout << "[X] Failed to open ipsw (aborting)" << endl;
					shutdown = ARSENIC_INIT_ERROR;
					break;
				}
				
				shutdown = ARSENIC_INIT_OK;
				break;
				
				case 'v':
				cout << "version: " << VERSION << endl;
				break;
				
				default:
				usage();
				shutdown = ARSENIC_INIT_SHUTDOWN;
				break;
			}
		}
		
		if (shutdown != ARSENIC_INIT_OK) {
			
			if (!(shutdown == ARSENIC_INIT_SHUTDOWN)) {
				
				// Something went wrong
				cout << "[!!] Theres no point crying over every mistake. You have to keep on trying untill you run out of cake" << endl;
			}
			
			return shutdown;
		}
		
		if (_ipsw != NULL) {

			_ipsw->getStringValue("ProductType", &_productType);
			_ipsw->getStringValue("ProductBuildVersion", &_productBuild);
			
			if (Bundle::exists(_productType, _productBuild)) {

				cout << "[!!] Found bundle for " << _productType << " with build " << _productBuild << endl;
				_bundle = new Bundle(_productType, _productBuild, _ipsw);

				//TODO: Start partch operations..
			} else {

				cout << "[X] Failed to locate bundle for " << _productType << " with build " << _productBuild << endl;
				return ARSENIC_INIT_ERROR;
			}
		}

		return shutdown;
	}

	void Arsenic::usage() {

		cout << "Usage: arsenic [OPTIONS] IPSW" << endl;
		cout << "Create and restore a custom firmware to an iDevice (iPhone/iPod Touch/iPad/AppleTV)." << endl;
		cout << "  -h, --help\t\tprints usage information" << endl;
		cout << "  -v, --version\t\tprints version information" << endl;
		cout << "  -i, --ipsw [filename]\tthe ipsw to work from" << endl;
		cout << endl;
	}
}
