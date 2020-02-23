#pragma once
#include <Windows.h>

int ShowBitMap(HWND hWnd, HANDLE hBit, int x, int y);
int ClientRectToBmp(HWND hwnd, char* name, RECT r);