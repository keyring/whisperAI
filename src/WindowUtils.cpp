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
  mi.fMask = MIIN_STATE;
  mi.fState = state;

  SetMenuItemInfo( GetMenu(hwnd), menuItem, false, &mi );
  DrawMenuBar(hwnd);
}

void CheckMenuItemAppropriatrly( HWND, hwnd, UINT menuItem, bool b ){

  if(b)
    ChangeMenuState( hwnd, menuItem, MFS_CHECKED );
  else
    ChangeMenuState( hwnd, menuItem, MFS_UNCHECKED );
}
