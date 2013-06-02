/*****************************************************************************
 *
 *    WindowUtils.cpp by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                  --code with Emacs :)
 ****************************************************************************/

#include "WindowUtils.h"

void CheckMenuItemAppropriatrly( HWND, hwnd, UINT menuItem, bool b ){

  if(b)
    ChangeMenuState( hwnd, menuItem, MFS_CHECKED );
  else
    ChangeMenuState( hwnd, menuItem, MFS_UNCHECKED );
}
