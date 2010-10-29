/**
  * GreenPois0n Arsenic - RootNode.h
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

#ifndef ROOTNODE_H
#define ROOTNODE_H

#include <map>
#include "Node.h"

namespace GP {


class RootNode: public Node {
public:
	RootNode(const NodeType type);
	virtual ~RootNode();

	Node* getNode(const char* key);

protected:
	NodeMap* mNodes;
	unsigned int depth;
};

}

#endif /* ROOTNODE_H */
