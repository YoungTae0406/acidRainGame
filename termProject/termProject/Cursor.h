#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>

class Cursor {
public:
	static void hideCursor() {
		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.bVisible = FALSE;
		cursorInfo.dwSize = 1;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}
	static void gotoxy(int x, int y) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
};