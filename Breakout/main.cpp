// standard libraries
#include <Windows.h>
#include <vector>
#include <String>

// classes for the game
#include "Logger.h"
#include "Level.h"
#include "comFunctions.h"
#include "appWindow.h"
#include "BaseRenderer.h"
#include "DX9Renderer.h"
#include "DX11Renderer.h"


// Globals
BaseRenderer *renderMethod;
int width, height, msaaSamples, bitsPixel, renderer, nCmdShow;
string windowMode;
bool fullscreen, appRunning;
HINSTANCE hInstance;

void launchGame(Logger log);

// Windows equivalant to main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	hInstance = hInstance;
	nCmdShow = nCmdShow;

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
			appConfig.setString("window_mode", "fullscreen");
			appConfig.setInt("msaa_sample_count", 4);
			appConfig.setInt("bits_per_pixel", 32);
			appConfig.setInt("directx_version", 11);
		}
		else {
			log.error("Unable to create the config file. Exiting");
			return 1;
		}
	}

	// get values from the config file
	width = appConfig.getInt("width");
	height = appConfig.getInt("height");
	windowMode = appConfig.getString("window_mode");

	if (windowMode == "fullscreen")
		fullscreen = true;

	msaaSamples = appConfig.getInt("msaa_sample_count");
	bitsPixel = appConfig.getInt("bits_per_pixel");
	renderer = appConfig.getInt("directx_version");
	appRunning = true;

	switch (renderer) {
	case 9:
		renderMethod = new DX9Renderer();
		launchGame(log);
		break;
	case 10:
		log.error("Renderer not implemented yet: " + std::to_string(renderer));
		break;
	case 11:
		renderMethod = new DX11Renderer();
		launchGame(log);
		break;
	default:
		log.error("Renderer method not found: " + std::to_string(renderer));
		break;
	}

	

	// create visual way to tell program execution has ended in log file
	log.info("Program execution terminating");
	log.info("-----------------------------");
	return 0;
}

void launchGame(Logger log) {
	// log values, more for debugging
	log.info("width: " + std::to_string(width) + " Height: " + std::to_string(height) + " Window Mode: " + windowMode);

	// create the window
	appWindow myApp = appWindow(hInstance, nCmdShow, width, height, windowMode);

	if (myApp.createAppWindow()) {
		// Create the directX object
		renderMethod->intialize(myApp.getWindowHandle(), fullscreen, msaaSamples, bitsPixel, width, height);

		// enter the message loop
		log.info("Entering game loop");
		MSG msg = { 0 };

		while (msg.message != WM_QUIT)
		{
			// If there are window messages then process them
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{

				if (appRunning)
				{
					// game code here
					float clearColor[4] = { (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, 1.0f };
					renderMethod->clearBackBuffer(clearColor);
					renderMethod->clearDepthStencil(1.0f);

					renderMethod->present();
				}
				else
				{
					// game is paused, let the app sleep to free up resources
					Sleep(100);
				}
			}
		}
		log.info("Exiting game loop");

	}
	else {
		log.error("Failed to create window, terminating");
	}
}