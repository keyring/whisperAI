/*****************************************************************************
 *
 *    WindowUtils.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                  --code with Emacs :)
 ****************************************************************************/

#ifndef __WINDOWUTILS_H__
#define __WINDOWUTILS_H__

#include <windows.h>
#include <string>

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

void CheckMenuState( HWND hwnd, UINT menuItem, UINT state );
void CheckMenuItemAppropriately( HWND hwnd, UINT menuItem, bool b );

inline void RedrawWindowRect( HWND hwnd, bool redrawBackground, RECT &redrawArea ){
  
  InvalidateRect( hwnd, &redrawArea, redrawBackground );
  UpdateWindow(hwnd);
}

#endif	/* __WINDOWUTILS_H__ */
