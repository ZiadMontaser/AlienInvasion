
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

#define FOREGROUND_WHITE FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN

string Green() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " EHU ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
}