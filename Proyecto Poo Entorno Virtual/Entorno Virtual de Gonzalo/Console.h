#pragma once
#include "Singleton.h"
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <iostream>
using namespace std;
class Console {
public:
	static FILE* fp;
	Console() {
		AllocConsole();
		
		freopen_s(&fp, "CONOUT$", "w", stdout);
		cout << "INITIALIZE" << std::endl;
	}
	~Console() {
		if (fp)
			delete fp;
	}

	static void Print(string data) {
		AllocConsole();
		freopen_s(&fp, "CONOUT$", "w", stdout);
		//cout << data << std::endl;
	}
};