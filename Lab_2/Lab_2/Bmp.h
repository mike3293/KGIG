#pragma once
#include <Windows.h>

int ShowBitMap(HWND hWnd, HANDLE hBit, int x, int y);
int ClientToBmp(HWND hwnd, RECT r, char* name);