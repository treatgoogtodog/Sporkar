#pragma once

#include <vector>
#include <queue>
#include "Object.h"

struct mapSQ {
	int sizeW, sizeH;
	std::vector<std::vector<bool>> MAP;
};

class MappingManager {
public:
	MappingManager();
	~MappingManager();

};