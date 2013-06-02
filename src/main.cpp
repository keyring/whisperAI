/*****************************************************************************
 *
 *    main.cpp by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                  --code with Emacs :)
 ****************************************************************************/

#pragma warning ( disable:4786 )

#include <windows.h>
#include <time.h>

#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

#include "Constants.h"
#include "PathFinder.h"
#include "resource.h"

#define UM_TOOLBAR_HAS_BEEN_CREATED (WM_USER + 33)

/*    Globals    */
const char *g_applicationName = "Path Finder";
const char *g_windowClassName = "MyClass";

PathFinder *g_pathFinder;

HWND g_hwndToolbar;

void RedrawDisplay( HWND hwnd ){

  InvalidateRect(hwnd, NULL, TRUE);
  UpdateWindow(hwnd);
}

void ResizeToCorrectClientArea( HWND hwnd, int toolbarHeight, RECT clientArea ){

  AdjustWindowRectEx( &clientArea,
		      WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
		      true,
		      NULL );

  SetWindowPos( hwnd,
		NULL,
		0, 0,
		clientArea.right,
		clientArea.bottom + toolbarHeight, 
		SWP_NOMOVE | SWP_NOZORDER );
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
  static int currentSearchButton = 0;

  static int ToolBarHeight;

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

    g_pathFinder = new PathFinder();

    CheckMenuItemAppropriately( hwnd, IDM_VIEW_TILES, g_pathFinder->IsShowTilesOn());
    CheckMenuItemAppropriately( hwnd, IDM_VIEW_GRAPH, g_pathFinder->IsShowGraphOn());
  }
    break;

  case WM_KEYUP:{
    switch(wParam){
    case VK_ESCAPE:
      SendMessage( hwnd, WM_DESTROY, NULL, NULL );
      break;
    case 'G':
      g_pathFinder->ToggleShowGraph();
      break;
    case 'T':
      g_pathFinder->ToggleShowTiles();
      break;
    } // switch

    //    RedrawWindowRect( hwnd, false, rectClientWindow ); 
  }
    break;

  case WM_LBUTTONDOWN:{
    g_pathFinder->PaintTerrain(MAKEPOINTS(lParam));
    // RedrawWindowRect( hwnd, false, rectClientWindow );
  }
    break;

  case WM_MOUSEMOVE:{
    switch(wParam){
    case MK_LBUTTON:{
      g_pathFinder->PaintTerrain(MAKEPOINTS(lParam));
      // RedrawWindowRect( hwnd, false, rectClientWindow );
    }
      break;
    }
  }
    break;

  case UM_TOOLBAR_HAS_BEEN_CREATED:{
    RECT rectToolbar;
    GetWindowRect( g_hwndToolbar, &rectToolbar);
    ToolBarHeight = abs(rectToolbar.bottom - rectToolbar.top);

    rectClientWindow.left = 0;
    rectClientWindow.right = CLIENTWIDTH;
    rectClientWindow.top = 0;
    rectClientWindow.bottom = CLIENTHEIGHT + INFOWINDOWHEIGHT;

    ResizeToCorrectClientArea( hwnd, ToolBarHeight, rectClientWindow );

    SendMessage( g_hwndToolbar, WM_SIZE, wParam, lParam );

    GetClientRect( hwnd, &rectClientWindow );
    rectClientWindow.bottom = CLIENTHEIGHT - ToolBarHeight - 1;

    hdcBackBuffer = CreateCompatibleDC(NULL);

    HDC hdc = GetDC(hwnd);

    hBitmap = CreateCompatibleBitmap( hdc,
				      rectClientWindow.right,
				      rectClientWindow.bottom );
    hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

    ReleaseDC(hwnd, hdc);
  }
    break;

  case WM_COMMAND:{
    switch(wParam){
    case ID_BUTTON_STOP:
      g_pathFinder->ChangeBrush( PathFinder::TARGET );      break;
    case ID_BUTTON_START:
      g_pathFinder->ChangeBrush( PathFinder::SOURCE );      break;
    case ID_BUTTON_OBSTACLE:
      g_pathFinder->ChangeBrush( PathFinder::OBSTACLE );    break;
    case ID_BUTTON_WATER:
      g_pathFinder->ChangeBrush( PathFinder::WATER );       break;
    case ID_BUTTON_MUD:
      g_pathFinder->ChangeBrush( PathFinder::MUD );         break;
    case ID_BUTTON_NORMAL:
      g_pathFinder->ChangeBrush( PathFinder::NORMAL );      break;
    case ID_BUTTON_DFS:
      g_pathFinder->CreatePathDFS();
      currentSearchButton = ID_BUTTON_DFS;    break;
    case ID_BUTTON_BFS:
      g_pathFinder->CreatePathBFS();
      currentSearchButton = ID_BUTTON_BFS;    break;
    case ID_BUTTON_DIJKSTRA:
      g_pathFinder->CreatePathDijkstra();
      currentSearchButton = ID_BUTTON_DIJKSTRA; break;
    case ID_BUTTON_ASTAR:
      g_pathFinder->CreatePathAStar();
      currentSearchButton = ID_BUTTON_ASTAR;  break;

    case ID_MENU_LOAD:
      // FileOpenDlg( hwnd, filename, titlename, "PathFinder Files (*.map)", "map" );
      if(strlen(titlename) > 0)
	g_pathFinder->Load(titlename);

      // SendMessage( g_hwndToolbar, TB_CHECKBUTTON, (WPARAM)currentSearchButton, (LPARAM)false );
      break;
    case ID_MENU_SAVEAS:
      // FileSaveDlg( hwnd, filename, titlename, "PathFinder Files (*.map)", "map" );
      if(strlen(titlename) > 0)
	g_pathFinder->Save(titlename);
      break;

    case ID_MENU_NEW:
      g_pathFinder->CreateGraph( NUMCELLSX, NUMCELLSY );
      // SendMessage( g_hwndToolbar, TB_CHECKBUTTON, (WPARAM)currentSearchButton, (LPARAM)false );
      break;

    case IDM_VIEW_GRAPH:
      if(GetMenuState(GetMenu(hwnd), IDM_VIEW_GRAPH, MFS_CHECKED) && MF_CHECKED){
	ChangeMenuState( hwnd, IDM_VIEW_GRAPH, MFS_UNCHEKED );
	g_pathFinder->SwitchGraphOff();
      }
      else{
	ChangeMenuState( hwnd, IDM_VIEW_GRAPH, MFS_CHECKED );
	g_pathFinder->SwitchGraphOn();
      }
      break;
    case IDM_VIEW_TILES:
      if(GetMenuState(GetMenu(hwnd), IDM_VIEW_TILES, MFS_CHECKED) && MF_CHECKED){
	ChangeMenuState( hwnd, IDM_VIEW_TILES, MFS_UNCHECKED );
	g_pathFinder->SwitchTilesOff();
      }
      else{
	ChangeMenuState( hwnd, IDM_VIEW_TILES, MFS_CHECKED );
	g_pathFinder->SwitchTilesOn();
      }
      break;
    } // switch

    // RedrawWindowRect( hwnd, false, rectClientWindow );
  }


  


  case WM_PAINT:{
    PAINTSTRUCT ps;
    BeginPaint(hwnd, &ps);
    BitBlt( hdcBackBuffer, 0, 0, cxClient, cyClient, NULL, NULL, NULL, WHITENESS );

    // start draw...
    g_pathFinder->Render();
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

  g_pathFinder->CreateGraph( NUMCELLSX, NUMCELLSY );

  MSG msg;
  while(GetMessage( &msg, NULL, 0, 0 )){
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  delete g_pathFinder;

  UnregisterClass( g_windowClassName, wc.hInstance );

  return msg.wParam;
}
