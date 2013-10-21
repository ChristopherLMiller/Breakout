#include "Level.h"

Level::Level() {
	// TODO: not sure how to handle this yet, if at all....
}

Level::Level(std::string filename) {
	Config config = Config(filename);

	// get the name of the level as well as how many blocks there are
	levelName = config.getString("levelName");
	numBlocks = config.getInt("numberOfBlocks");

	// at this point lets loop and create block objects to add to the vector
	for (int i = 0; i < numBlocks; i++) {
		string input = config.getString("block" + std::to_string(i));

		// parse out the string to get the x, y, width, and height
		
	}
}

int Level::getNumBlocks() {
	return numBlocks;
}

string Level::getLevelName() {
	return levelName;
}