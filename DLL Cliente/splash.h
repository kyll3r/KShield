#ifdef _WIN32

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <wchar.h>
#include <ole2.h>
#include <iostream>
#include <map>

#pragma comment(lib, "winmm.lib")

using namespace std;

namespace dbsoft
{
class CSplashWindow
{
public:
   CSplashWindow( HINSTANCE hInst, std::basic_string<TCHAR> strBmp ):m_hInstance(hInst),m_hWnd(NULL),m_hBitMap(NULL),m_hThread(NULL), \
    m_strBmpFile( strBmp )
   {
   }

   ~CSplashWindow()
   {
    Stop();
   }

   inline bool Show()
   {
    TCHAR szClassName[MAX_PATH];
    _stprintf( szClassName, _T("SplashScreenClass%d"), (int)this );
    m_strClassName = szClassName;

    WNDCLASS wc;
    wc.style       = 0;
    wc.lpfnWndProc = (WNDPROC) SplashScreenWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance   = m_hInstance;
    wc.hIcon       = LoadIcon((HINSTANCE) NULL, IDI_APPLICATION);
    wc.hCursor     = LoadCursor((HINSTANCE) NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;

    if(!RegisterClass(&wc))
    {
     return 0;
    }

    m_hBitMap = (HBITMAP) LoadImage( m_hInstance, m_strBmpFile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if( m_hBitMap == NULL )
    {
     return false;
    }

    m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SplashScreenWorkThread, this, 0, NULL);

    return true;
   }

   inline void Stop()
   {
    if(m_hThread)
    {
     if(m_hWnd)
     {
      PostMessage(m_hWnd, WM_DESTROY, 0, 0);
     }

     WaitForSingleObject(m_hThread, INFINITE);

     unRegisterWindow( this );

     CloseHandle(m_hThread);
     m_hThread = NULL;
     m_hWnd = NULL;
    }
   }

   inline HINSTANCE         GetIns() const
   {
    return m_hInstance;
   }

   inline HBITMAP           GetBitmap() const
   {
    return m_hBitMap;
   }

   inline HWND              GetWnd() const
   {
    return m_hWnd;
   }

   inline void              SetWnd( HWND hWnd )
   {
    m_hWnd = hWnd;
   }

   inline std::basic_string<TCHAR> GetClassName() const
   {
    return m_strClassName;
   }

private:
   HINSTANCE                 m_hInstance;
   HWND                      m_hWnd;
   HANDLE                    m_hThread;
   std::basic_string<TCHAR> m_strBmpFile;
   std::basic_string<TCHAR> m_strClassName;
   HBITMAP                   m_hBitMap;


   static inline std::map<HWND, CSplashWindow*>& StaticMapContainer()
   {
    static std::map<HWND,CSplashWindow*> container;

    return container;
   }

   inline static void registerWindow( CSplashWindow* hWnd )
   {
    if( hWnd != NULL )
    {
     StaticMapContainer()[ hWnd->GetWnd() ] = hWnd;
    }  
   }

   inline static void unRegisterWindow( CSplashWindow* hWnd )
   {
    if( hWnd != NULL )
    {
     StaticMapContainer().erase( hWnd->GetWnd() );
    }
   }


   static DWORD WINAPI SplashScreenWorkThread( LPVOID lpParam )
   {
    CSplashWindow* Win = (CSplashWindow*)lpParam;

    if( Win == NULL || Win->GetIns() == NULL || Win->GetBitmap() == NULL )
    {
     MessageBox( NULL, _T("Error, Can't Create SplashWindow"), _T("Error"), 0 );
     return 0;
    }  

    BITMAP bm;
    GetObject( Win->GetBitmap(), sizeof(bm), &bm);
    INT ScreenPosX = (GetSystemMetrics(SM_CXSCREEN) - bm.bmWidth) / 2;
    INT ScreenPosY = (GetSystemMetrics(SM_CYSCREEN) - bm.bmHeight) / 2;

    HWND hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, Win->GetClassName().c_str(), TEXT("SplashWindow"), WS_BORDER|WS_POPUP,
     ScreenPosX, ScreenPosY, bm.bmWidth, bm.bmHeight, (HWND) NULL, (HMENU) NULL, Win->GetIns(), (LPVOID) NULL);

    Win->SetWnd( hWnd );

    registerWindow( Win );

    if (hWnd)
    {
     ShowWindow(hWnd, SW_SHOW);
     UpdateWindow(hWnd);

     MSG message;
     while (GetMessage(&message, NULL, 0, 0))
     {
      TranslateMessage(&message);
      DispatchMessage(&message);
     }
    }

    return 0;
   }

   static LRESULT CALLBACK SplashScreenWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
    HDC hdc;
    PAINTSTRUCT ps;

    switch( message )
    {
    case WM_PAINT:
     hdc = BeginPaint(hWnd, &ps);

     {
      try
      {
       CSplashWindow* hWindows = StaticMapContainer()[hWnd];

       if( hWindows )
       {
        DrawState(hdc, DSS_NORMAL, NULL, (LPARAM)hWindows->GetBitmap(), 0, 0, 0, 0, 0, DST_BITMAP);
       }     
      }
      catch(...)
      {
      }    
     }

     EndPaint(hWnd, &ps);
     break;
    case WM_DESTROY:
     PostQuitMessage(0);
     break;
    default:
     return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
   }
};
}

//waiting after run aplication
void Wait(int seconds)
{
  clock_t endwait;
  endwait = clock () + seconds;
  while (clock() < endwait) {}
}




int Splash()
{
    
    
    
HINSTANCE hInstance = GetModuleHandle(NULL);

dbsoft::CSplashWindow splash( hInstance, _T("img/splash.bmp") );

splash.Show();

Wait(2500);

//::Sleep( 3000 );



splash.Stop();

return 0;
}

#endif
