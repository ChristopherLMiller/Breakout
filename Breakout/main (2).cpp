//#include <Windows.h>
//#include <string>
//#include <sstream>
//#include "Config.h"
//#include "Logger.h"
//#include "appWindow.h"
//#include "comFunctions.h"
//#include "directx.h"

//using std::string;

// pre declare
//LPCWSTR CalculateFrameStats(GameTimer &timer);

// windows equivalant to main()
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
//{
	// create logger
//	Logger logger = Logger();
//	logger.info("Program execution beginning");

	// create the config object now so we can pass dimensions to window creation
	//Config appConfig = Config();
	
	// create the config file if it doesn't exist and populate default values
	//if (!appConfig.fileExists())
	//{
		//logger.info(appConfig.getFileName() + " created. Didn't exist.");
		//appConfig.createFile();
		//int tempWidth = 0;
		//int tempHeight = 0;
		//GetDesktopResolution(tempWidth, tempHeight);
		//appConfig.setInt("width", tempWidth);
		//appConfig.setInt("height", tempHeight);
		//appConfig.setBool("windowed", false);
		//appConfig.setInt("DirectX_Version", 11);	// TODO: default to highest supported version
		//appConfig.setInt("MSAA_Sample_Count", 4);
		//appConfig.setInt("bits_per_pixel", 32);
	//}

	// get resolution
	//int width = appConfig.getInt("width");
	//int height = appConfig.getInt("height");
	//bool fullscreen = appConfig.getBool("windowed");
	//int dxVersion = appConfig.getInt("DirectX_Version");
	//UINT sampleCount = appConfig.getInt("MSAA_Sample_Count");
	//int bitsPerPixel = appConfig.getInt("bits_per_pixel");
	//bool appRunning = true;


	//logger.info("width: " + std::to_string(width) + " Height: " + std::to_string(height) + " windowed: " + toString(fullscreen) + " Directx Version: " + std::to_string(dxVersion) + " bpp: " + std::to_string(bitsPerPixel));

	// create the appwindow instance
	//appWindow myApp = appWindow(hInstance, nShowCmd, width, height);

	//if (myApp.createAppWindow())
	//{
		// create the directx object at this point
		//DirectX dxObject = DirectX();

		/*if (dxObject.initialize(dxVersion, myApp.getWindowHandle(), fullscreen, sampleCount, bitsPerPixel, width, height))
		{
			// create a timer object
			GameTimer timer = GameTimer();
			timer.Reset();

			// enter the message loop
			MSG msg = {0};

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
					timer.Tick();

					if (appRunning)
					{
						myApp.setAppWindowText(CalculateFrameStats(timer));

						// process game stuff, IE animation physics
						float clearColor[4] = {(float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, 1.0f};
						dxObject.getImmediateContext()->ClearRenderTargetView(dxObject.getRenderTargetView(), clearColor);

						// clear depth buffer and stencil buffer
						dxObject.getImmediateContext()->ClearDepthStencilView(dxObject.getDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

						// present the back buffer
						dxObject.getSwapChain()->Present(0,0);
					}
					else 
					{
						// game is paused, let the app sleep tofree up resources
						Sleep(100);
					}
				}
			}
		}
		else
		{
			logger.logError("Failed to initialize DirectX, terminating");
		}
	}
	else
	{
		logger.logError("Failed to created window, terminating");
	}*/
	
	// create good indicator of where program execution ended in the logs
	//logger.info("Program Execution Terminating");
//	logger.info("------------------------------------------------------");
//	return 0;
//}

/*LPCWSTR CalculateFrameStats(GameTimer &timer)
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	float fps = (float)frameCnt;
	float mspf = 1000.0f / fps;

	std::wostringstream outs;
	outs.precision(6);
	outs << L"Breakout   FPS: " << fps << L"Frame Time: " << mspf << L"ms";

	frameCnt = 0;
	timeElapsed += 1.0f;

	return outs.str().c_str();
}*/
