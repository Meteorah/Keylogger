#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <new.h>
#include <WindowsX.h>
#include <wchar.h>
#include "basewin.h"

void Log(std::string str) {
	std::ofstream outfile;
	outfile.open("file.txt", std::ios::app);
	outfile << str;
	outfile.close();
}