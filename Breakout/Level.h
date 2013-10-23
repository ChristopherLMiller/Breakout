#ifndef __LEVEL_H
#define __LEVEL_H

#include "Block.h"
#include "Config.h"
#include "tinyxml2.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using std::vector;
using std::string;

class Level {
private:
	vector<Block> blocks;
	int numBlocks;
	string levelName;

public:
	// constructors
	Level();

	bool load(std::string filename);
	int getNumBlocks();
	string getLevelName();
};

#endif