/**
  * GreenPois0n Arsenic - Node.h
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

#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>
#include <cstring>

namespace GP {

typedef enum {
	kDictionaryNode,
	kArrayNode,
	kStringNode,
	kDataNode,
	kIntegerNode,
	kBooleanNode,
	kDateNode,
	kRealNode
} NodeType;


class Node {
public:
	Node(const NodeType type) :
		mType(type) {
	}
	virtual ~Node() {
	}

	typedef std::map<std::string,Node*> NodeMap;
	typedef std::map<std::string,Node*>::iterator Iterator;

	Node* findNode(const char* key) {
		NodeMap::iterator it;
		for (it = mNodes->begin(); it != mNodes->end(); ++it) {
			std::string cur = it->first;

			if (!strcmp(cur.c_str(), key)) {
				return it->second;
			}

			Node* node = it->second->findNode(key);
			if(node) {
				return node;
			}
		}
		return NULL;
	}

	NodeType getType() {
		return mType;
	}
	void setType(const NodeType type) {
		mType = type;
	}

protected:
	NodeType mType;
	NodeMap* mNodes;
};

}

#endif /* NODE_H */
