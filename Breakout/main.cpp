#include <Windows.h>
#include <vector>

#include "Block.h"
#include "Logger.h"
#include "Level.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Logger log = Logger();
	log.info("Program execution beginning");
	log.info("Creating a level");

	Level level = Level("level1.txt");
	log.info("Level Name: " + level.getLevelName());
	log.info("Number of blocks: " + std::to_string(level.getNumBlocks()));
	log.info("Program execution terminated");
	log.info("----------------------------");
}