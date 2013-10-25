// standard libraries
#include <Windows.h>
#include <vector>

// classes for the game
#include "Logger.h"
#include "Level.h"
#include "comFunctions.h"
#include "appWindow.h"

// Windows equivalant to main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// create the logger
	Logger log = Logger();
	log.info("Program execution beginning");

	// create the config object now
	Config appConfig = Config();

	if (!appConfig.fileExists()) {
		if (appConfig.createFile()) {
			log.info(appConfig.getFileName() + " created.");
			int tempWidth = 0, tempHeight = 0;
			GetDesktopResolution(tempWidth, tempHeight);
			appConfig.setInt("width", tempWidth);
			appConfig.setInt("height", tempHeight);
		}
		else {
			log.error("Unable to create the config file. Exiting");
			return 1;
		}
	}

	// get values from the config file
	int width = appConfig.getInt("width");
	int height = appConfig.getInt("height");

	// log values, more for debugging
	log.info("width: " + std::to_string(width) + " Height: " + std::to_string(height));

	// create the app window instance
	appWindow myApp = appWindow(hInstance, nCmdShow, width, height);

	if (myApp.createAppWindow()) {
		// TODO: DX

		// test code for now
		Level level = Level();
		if (level.load("Assets/Levels/level1.xml")) {
			log.info("Level name: " + level.getLevelName());
		}
	}
	else {
		log.error("Failed to create window, terminating");
	}

	// create visual way to tell program execution has ended in log file
	log.info("Program execution terminating");
	log.info("-----------------------------");
	return 0;
}