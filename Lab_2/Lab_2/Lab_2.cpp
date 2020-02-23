
// Lab_2.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Lab_2.h"
#include "MainFrm.h"
#include "Bmp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab2App

BEGIN_MESSAGE_MAP(CLab2App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CLab2App::OnAppAbout)
	ON_COMMAND(LOAD_BMP, &CLab2App::LoadImageBMP)
	ON_COMMAND(SAVE_BMP, &CLab2App::InitAreaSaving)
END_MESSAGE_MAP()


void CLab2App::LoadImageBMP() //ф-ция загрузки изображения с диска в оперативную память
{
	CFileDialog fileDialog(true, NULL, L"");	//объект класса выбора файла
	fileDialog.m_ofn.lpstrFilter = (LPCTSTR)"images (.bmp)\0*.bmp\0\0";
	int result = fileDialog.DoModal();	//запустить диалоговое окно
	if (result == IDOK)	//если файл выбран
	{
		AfxMessageBox(fileDialog.GetPathName()); // показать полный путь
		CWnd *cwnd = AfxGetMainWnd();
		hwnd = cwnd->GetSafeHwnd();
		//чтение из файла изображения с расширением .ВМР 
		hBit = (HBITMAP)LoadImage(NULL/*NULL - картинка выводится из файла*/, fileDialog.GetPathName().GetBuffer()/*имя файла или идентификатор ресурса*/,
			IMAGE_BITMAP/*задаётся тип изображения*/, 0, 0/*размеры изображения, 0 т.к. эта информация имеется в заголовке ВМР-файла*/,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION)/*сочетание флагов. LR_LOADFROMFILE - изображение вводится из файла.*/
			/*LR_CREATEDIBSECTION - создаётся аппаратно-независимое растровое изображение*/;
		ShowBitMap(hwnd, hBit, From.x, From.y);
	}
}


void CLab2App::InitAreaSaving()
{
	isSavingArea = true;
}

void CLab2App::SaveArea() //сохранения области изображения
{
	CFileDialog fileDialog(FALSE, NULL, L"area.bmp");	//объект класса выбора файла
	fileDialog.m_ofn.lpstrFilter = (LPCTSTR)"images (.bmp)\0*.bmp\0\0";
	int result = fileDialog.DoModal();	//запустить диалоговое окно
	if (result == IDOK)	//если файл выбран
	{
		CWnd *cwnd = AfxGetMainWnd();
		HWND hwnd = cwnd->GetSafeHwnd();
		RECT r; //r – область в  окне, которая сохраняется в файле
		int x, y;
		if (To.x - From.x < 0 && To.y - From.y < 0)
		{
			x = From.x;
			From.x = To.x;
			To.x = x;
			y = From.y;
			From.y = To.y;
			To.y = y;
		}
		r.left = From.x;
		r.right = To.x;
		r.top = From.y;
		r.bottom = To.y;

		if (ClientRectToBmp(hwnd, LPSTR(fileDialog.GetPathName().GetBuffer()), r) == 0)
			AfxMessageBox(L"Saved");
		else
			AfxMessageBox(L"Error");

	}
}


// Создание CLab2App

CLab2App::CLab2App() noexcept
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Если приложение построено с поддержкой среды Common Language Runtime (/clr):
	//     1) Этот дополнительный параметр требуется для правильной поддержки работы диспетчера перезагрузки.
	//   2) В своем проекте для сборки необходимо добавить ссылку на System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif
	From.x = From.y = 50;
	To.x = To.y = 50;

	// TODO: замените ниже строку идентификатора приложения строкой уникального идентификатора; рекомендуемый
	// формат для строки: ИмяКомпании.ИмяПродукта.СубПродукт.СведенияОВерсии
	SetAppID(_T("Lab2.AppID.NoVersion"));

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}

// Единственный объект CLab2App

CLab2App theApp;


// Инициализация CLab2App

BOOL CLab2App::InitInstance()
{
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Инициализация библиотек OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));


	// Чтобы создать главное окно, этот код создает новый объект окна
	// рамки, а затем задает его как объект основного окна приложения
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// создайте и загрузите рамку с его ресурсами
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);


	// Разрешить использование расширенных символов в горячих клавишах меню
	CMFCToolBar::m_bExtCharTranslation = TRUE;




	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CLab2App::ExitInstance()
{
	//TODO: обработайте дополнительные ресурсы, которые могли быть добавлены
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Обработчики сообщений CLab2App


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void CLab2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Обработчики сообщений CLab2App
