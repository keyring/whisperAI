/*****************************************************************************
 *
 *    WindowUtils.cpp by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                  --code with Emacs :)
 ****************************************************************************/

#include "WindowUtils.h"


void ChangeMenuState( HWND hwnd, UINT menuItem, UINT state ){

  MENUITEMINFO mi;

  mi.cbSize = sizeof(MENUITEMINFO);
  mi.fMask = MIIM_STATE;
  mi.fState = state;

  SetMenuItemInfo( GetMenu(hwnd), menuItem, false, &mi );
  DrawMenuBar(hwnd);
}

void CheckMenuItemAppropriatrly( HWND hwnd, UINT menuItem, bool b ){

  if(b)
    ChangeMenuState( hwnd, menuItem, MFS_CHECKED );
  else
    ChangeMenuState( hwnd, menuItem, MFS_UNCHECKED );
}

//-----------------------------------------------------------------------------
//
//  The following 3 functions are taken from Petzold's book and enable the 
//  client to use the file dialog common control
//-----------------------------------------------------------------------------
void FileInitialize (HWND hwnd,
                     OPENFILENAME& ofn,
                     const std::string& defaultFileTypeDescription,
                     const std::string& defaultFileExtension)
{
  std::string filter = defaultFileTypeDescription + '\0' + "*." + defaultFileExtension + '\0' +
                       "All Files (*.*)" + '\0' + "*.*" + '\0' + '\0';
  
   static TCHAR szFilter[255];

   for (unsigned int i=0; i<filter.size(); ++i)
   {
     szFilter[i] = filter.at(i);
   }
     
     ofn.lStructSize       = sizeof (OPENFILENAME) ;
     ofn.hwndOwner         = hwnd ;
     ofn.hInstance         = NULL ;
     ofn.lpstrFilter       = szFilter ;
     ofn.lpstrCustomFilter = NULL ;
     ofn.nMaxCustFilter    = 0 ;
     ofn.nFilterIndex      = 0 ;
     ofn.lpstrFile         = NULL ;          // Set in Open and Close functions
     ofn.nMaxFile          = MAX_PATH ;
     ofn.lpstrFileTitle    = NULL ;          // Set in Open and Close functions
     ofn.nMaxFileTitle     = MAX_PATH ;
     ofn.lpstrInitialDir   = NULL ;
     ofn.lpstrTitle        = NULL ;
     ofn.Flags             = 0 ;             // Set in Open and Close functions
     ofn.nFileOffset       = 0 ;
     ofn.nFileExtension    = 0 ;
     ofn.lpstrDefExt       = defaultFileExtension.c_str() ;
     ofn.lCustData         = 0L ;
     ofn.lpfnHook          = NULL ;
     ofn.lpTemplateName    = NULL ;

}



BOOL FileOpenDlg (HWND               hwnd,
                  PTSTR              pstrFileName,
                  PTSTR              pstrTitleName,
                  const std::string& defaultFileTypeDescription,
                  const std::string& defaultFileExtension)
{
     OPENFILENAME ofn;

     FileInitialize(hwnd, ofn, defaultFileTypeDescription, defaultFileExtension);
  
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName ;
     ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;
     
     return GetOpenFileName (&ofn) ;
}

BOOL FileSaveDlg (HWND               hwnd,
                  PTSTR              pstrFileName,
                  PTSTR              pstrTitleName,
                  const std::string& defaultFileTypeDescription,
                  const std::string& defaultFileExtension)
{
     OPENFILENAME ofn; FileInitialize(hwnd, ofn, defaultFileTypeDescription, defaultFileExtension);

     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName ;
     ofn.Flags             = OFN_OVERWRITEPROMPT ;
     
     return GetSaveFileName (&ofn) ;
}
