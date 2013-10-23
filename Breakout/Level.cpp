#include "Level.h"

Level::Level() {
	// TODO: not sure how to handle this yet, if at all....
}

bool Level::load(std::string fileName) {
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(fileName.c_str()) != tinyxml2::XML_ERROR_FILE_NOT_FOUND) {
		const char* temp = doc.FirstChildElement("level")->FirstChildElement("levelName")->GetText();
		levelName = std::string(temp, 255);
		return true;
	}
	else {
		// document didn't load for whatever reason, warn and return
		Logger log = Logger();
		log.error("Unable to load file: " + fileName);
		return false;
	}



}
int Level::getNumBlocks() {
	return numBlocks;
}

string Level::getLevelName() {
	return levelName;
}