
// ChildView.cpp: реализация класса CChildView
//

#include "pch.h"
#include "framework.h"
#include "Lab_2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN() //(нажатие левой клавиши мыши)
	ON_WM_LBUTTONUP() //(освобождение левой кнопки мыши)
END_MESSAGE_MAP()



// Обработчики сообщений CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // контекст устройства для рисования
	
	// TODO: Добавьте код обработки сообщений
	
	// Не вызывайте CWnd::OnPaint() для сообщений рисования
}

void CChildView::OnLButtonDown(UINT flags, CPoint point) //метод нажатия левой клавиши мыши
{
	theApp.From = point;
}

void CChildView::OnLButtonUp(UINT flags, CPoint point) //метод освобождения левой кнопки мыши
{
	theApp.To = point;
	if (theApp.isSavingArea)
	{
		theApp.SaveArea();
		theApp.isSavingArea = false;
		theApp.From.x = 50;
		theApp.From.y = 50;
		theApp.To.x = 50;
		theApp.To.y = 50;
	}

}