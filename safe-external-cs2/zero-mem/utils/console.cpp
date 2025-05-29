#include <pch.h>
#include "console.h"

namespace Console
{
	void SetConsoleTextColor(WORD color)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

	void CreateConsoleWindow(const char* title, int width, int height)
	{
		AllocConsole();
		FILE* file;
		freopen_s(&file, "CONOUT$", "w", stdout);  // Redirect stdout
		freopen_s(&file, "CONIN$", "r", stdin);   // Redirect stdin
		//freopen_s(&file, "CONERR$", "w", stderr); // Redirect stderr


		SetConsoleTitle(title);

		HWND consoleWindow = GetConsoleWindow();
		if (consoleWindow != NULL)
		{
			MoveWindow(consoleWindow, 100, 100, width, height, TRUE);
		}
	}

	void DestroyConsoleWindow()
	{
		HWND consoleWindow = GetConsoleWindow(); // Get the console window handle
		if (consoleWindow != NULL)
		{
			FreeConsole(); // Detach the console from the current process
			PostMessage(consoleWindow, WM_CLOSE, 0, 0); // Send a close message to the console window
		}
	}

	void CreateLogNotification(const std::string& LogsName, const std::string& logFileName) {
		std::time_t currentTime = std::time(nullptr);
		std::tm localTime;
		localtime_s(&localTime, &currentTime);

		std::cout
			<< " [INFO] "
			<< LogsName
			<< " Logs have been created at: "
			<< logFileName
			<< " ("
			<< std::put_time(&localTime, "%Y-%m-%d %H:%M:%S")
			<< ")"
			<< '\n';
		std::cout << '\n';
	}
}