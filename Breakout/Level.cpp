#include "Level.h"

Level::Level() {
	m_log = Logger();
}

bool Level::load(std::string fileName) {
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(fileName.c_str()) != tinyxml2::XML_ERROR_FILE_NOT_FOUND) {
		if (!NULL && doc.FirstChildElement("level")) {
			if (!NULL && doc.FirstChildElement("level")->FirstChildElement("levelName")) {
				m_levelName = toString(doc.FirstChildElement("level")->FirstChildElement("levelName")->GetText());
				return true;
			}
			else {
				m_log.error("Unable to find element 'levelName' in file: " + fileName);
				return false;
			}
		}
		else {
			m_log.error("Unable to find element 'level' in file:  " + fileName);
			return false;
		}
	}
	else {
		m_log.error("Unable to load file: " + fileName);
		return false;
	}



}
int Level::getNumBlocks() {
	return m_numBlocks;
}

string Level::getLevelName() {
	return m_levelName;
}