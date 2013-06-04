/****************************************************************************
 *
 *    Wpgdi.cpp by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *
 *    DESC: Whisper Packaging GDI. A singleton class to help alleviate the 
 *          tedium of using the GDI.Call each method using the #define for 
 *          wpgdi-> .
 ***************************************************************************/

#include "Wpgdi.h"

Wpgdi *Wpgdi::Instance(){
  // this class is a singleton
  static Wpgdi instance;
  return &instance;
}

Wpgdi::Wpgdi(){

  m_blackPen = CreatePen( PS_SOLID, 1, COLORS[BLACK] );
  m_whitePen = CreatePen( PS_
