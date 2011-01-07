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

#ifndef ARSENIC_H_
#define ARSENIC_H_

#define ARSENIC_INIT_OK 1
#define ARSENIC_INIT_BAD_ARGS 2
#define ARSENIC_INIT_ERROR 3
#define ARSENIC_INIT_SHUTDOWN 4

extern "C" {
#include <getopt.h>
}

#include "common.h"

namespace GP {
    
	class Arsenic {
        
	private:
		static Arsenic* _instance;
		static bool _instanceFlag;
        
        //	Arsenic();
        //	~Arsenic();
        //	Arsenic& operator= (const Arsenic&);
        
	public:
		static Arsenic &getInstance();
		int initialize(int argc, char* argv[]);
		void usage();
        
	};
    
}

#endif /* ARSENIC_H_ */
