
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

#define FOREGROUND_WHITE FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN

void setcursor(bool visible, DWORD size = 1) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if (size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursor);
}
void gotoXY(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(handle, pos);
}

void setcolor(WORD color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
