/**
 * GreenPois0n Arsenic
 * Copyright (C) 2010 Chronic-Dev Team
 * Copyright (C) 2010 GreySyntax
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

using namespace std;
using namespace GP;

int shutdown(const char* message, int code) {
	
	cout << "[X] " << message << endl;
	exit(code);
}

int main(int argc, char* argv[]) {
    
	cout << endl;
	cout << "GreenPois0n Arsenic" << endl;
	cout << "Copyright (C) 2010 Chronic-Dev Team" << endl;
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
    
    if (! arsenic.hasBundle()) {
        
        shutdown("Bundle not found", -1);
    }
    
    cout << "We haz bundle!" << endl;
    
	return 0;
}
