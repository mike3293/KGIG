
// Lab_1.h: основной файл заголовка для приложения Lab_1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // основные символы


// CLab1App:
// Сведения о реализации этого класса: Lab_1.cpp
//

class CLab1App : public CWinApp
{
public:
	CLab1App() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLab1App theApp;
