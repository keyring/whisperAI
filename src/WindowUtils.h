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

void ChangeMenuState( HWND hwnd, UINT menuItem, UINT state );
void CheckMenuItemAppropriately( HWND hwnd, UINT menuItem, bool b );

inline void RedrawWindowRect( HWND hwnd, bool redrawBackground, RECT &redrawArea ){
  
  InvalidateRect( hwnd, &redrawArea, redrawBackground );
  UpdateWindow(hwnd);
}

/* three handy functions from Mr Petzold. They open a common dialog box to
grab a filename */
void FileInitialize (HWND hwnd,
                     OPENFILENAME& ofn,
                     const std::string& defaultFileTypeDescription,
                     const std::string& defaultFileExtension);

BOOL FileOpenDlg (HWND               hwnd,
                  PTSTR              pstrFileName,
                  PTSTR              pstrTitleName,
                  const std::string& defaultFileTypeDescription,
                  const std::string& defaultFileExtension);

BOOL FileSaveDlg (HWND hwnd,
                  PTSTR pstrFileName,
                  PTSTR pstrTitleName,
                  const std::string& defaultFileTypeDescription,
                  const std::string& defaultFileExtension);

#endif	/* __WINDOWUTILS_H__ */
