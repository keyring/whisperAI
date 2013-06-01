/*****************************************************************************
 *
 *    main.cpp by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                  --code with Emacs :)
 ****************************************************************************/

#pragma warning ( disable:4786 )

#include <windows.h>
#include <time.h>

/*    Globals    */
const char *g_applicationName = "Path Finder";
const char *g_windowClassName = "MyClass";

/*    Constant    */
const int WINDOWWIDTH = 600;
const int WINDOWHEIGTH = 600;
const int CLIENTWIDTH = 500;
const int CLIENTHEIGHT = 500;
const int NUMCELLSX = 19;
const int NUMCELLSY = 19;

void RedrawDisplay( HWND hwnd ){

  InvaliddateRect(hwnd, NULL, TRUE);
  UpdateWindow(hwnd);
}

LRESULT CALLBACK WindowProc( HWND hwnd,
			     UINT msg,
			     WPARAM wParam,
			     LPARAM lParam ){

  static int cxClient, cyClient;

  static HDC hdcBackBuffer;
  static HBITMAP hBitmap = NULL;
  static HBITMAP hOldBitmap = NULL;

  static TCHAR filename[MAX_PATH], titlename[MAX_PATH];
  static RECT rectClientWindow;
  static int CurrentSearchButton = 0;

  switch(msg){

  case WM_CREATE:{
    srand((unsigned) time(NULL));
    hdcBackBuffer = CreateCompatibleDC(NULL);
    HDC hdc = GetDC(hwnd);

    hBitmap = CreateCompatibleBitmap( hdc,
				      cxClient,
				      cyClient);

    hOldBitmap = (HBITMAP)SelectObject( hdcBackBuffer, hBitmap );

    ReleaseDC(hwnd, hdc);
  }
    break;

  case WM_PAINT:{
    PAINTSTRUCT ps;
    BeginPaint(hwnd, &ps);
    BitBlt( hdcBackBuffer, 0, 0, cxClient, cyClient, NULL, NULL, NULL, WHITENESS );

    // start draw...
    // render...
    // stop draw...

    BitBlt( ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY );

    EndPaint(hwnd, &ps);
  }
    break;

  case WM_SIZE:{
    cxClient = LOWORD(lParam);
    cyClient = HIWORD(lParam);

    SelectObject(hdcBackBuffer, hOldBitmap);

    DeleteObject(hBitmap);

    HDC hdc = GetDC(hwnd);

    hBitmap = CreateCompatibleBitmap( hdc,
				      rectClientWindow.right,
				      rectClientWindow.bottom );

    ReleaseDC(hwnd, hdc);
    SelectObject(hdcBackBuffer, hBitmap);
  }
    break;

  case WM_DISTROY:{
    SelectObject(hdcBackBuffer, hOldBitmap);
    DeleteDC(hdcBackBuffer);
    DeleteObject(hBitmap);
    DeleteObject(hOldBitmap);

    PostQuitMessage(0);
  }
    break;
  } // end switch

  return DefWindowProc( hwnd, msg, wParam, lParam );		      
}

int WINAPI WinMain( HINSTANCE hInstance,
		    HINSTANCE hPreInstance,
		    LPSTR cmdLine,
		    int cmdShow ){

  HWND hWnd;
  WNDCLASSEX wc;

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(hInstance, MAKEINSTAANCE(IDI_ICON1));
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
  wc.lpszClassName = g_windowClassName;
  wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

  if( !RegisterClassEx(&wc) ){
    MessageBox( NULL, "Registration Failed!", "ERROR", 0 );
    return 0;
  }

  hWnd = CreateWindowEx( NULL,
			 g_windowClassName,
			 g_applicationName,
			 WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
			 GetSystem(SM_CXSCREEN)/2 - WINDOWWIDTH/2,
			 GetSystem(SM_CYSCREEN)/2 - WINDOWHEIGHT/2,
			 WINDOWWIDTH,
			 WINDOWHEIGHT,
			 NULL,
			 NULL,
			 hInstance,
			 NULL );

  if( !hWnd ){
    MessageBox( NULL, "CreateWindow Failed!", "ERROR", 0 );
  }

  // Create the graph...


  MSG msg;
  while(GetMessage( &msg, NULL, 0, 0 )){
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // delete the graph...

  UnregisterClass( g_windowClassName, wc.hInstance );

  return msg.wParam;
}
