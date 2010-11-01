/**
  * GreenPois0n Arsenic - String.h
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

#ifndef STRING_H
#define STRING_H

#include "Node.h"

namespace GP {

class String: public Node {
public:
	String(const char* data);
	String(String& data);
	virtual ~String();

	const char* get();
	void set(const char* data);

	int length();
	bool compare(const char* what);
	bool compare(const String& what);

	void concat(const char* what);
	void concat(String& what);

protected:
	char* mData;
	unsigned int mLength;
};

}

#endif /* STRING_H */
