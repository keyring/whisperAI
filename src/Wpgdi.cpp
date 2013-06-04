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
  m_whitePen = CreatePen( PS_SOLID, 1, COLORS[WHITE] );
  m_redPen = CreatePen( PS_SOLID, 1, COLORS[RED] );
  m_greenPen = CreatePen( PS_SOLID, 1, COLORS[GREEN] );
  m_bluePen = CreatePen( PS_SOLID, 1, COLORS[BLUE] );
  m_greyPen = CreatePen( PS_SOLID, 1, COLORS[GREY] );
  m_pinkPen = CreatePen( PS_SOLID, 1, COLORS[PINK] );
  m_yellowPen = CreatePen( PS_SOLID, 1, COLORS[YELLOW] );
  m_orangePen = CreatePen( PS_SOLID, 1, COLORS[ORANGE] );
  m_purplePen = CreatePen( PS_SOLID, 1, COLORS[PURPLE] );
  m_brownPen = CreatePen( PS_SOLID, 1, COLORS[BROWN] );
  m_darkGreenPen = CreatePen( PS_SOLID, 1, COLORS[DARK_GREEN] );
  m_ligthBluePen = CreatePen( PS_SOLID, 1, COLORS[LIGHT_BLUE] );
  m_lightGreyPen = CreatePen( PS_SOLID, 1, COLORS[LIGHT_GREY] );
  m_lightPinkPen = CreatePen( PS_SOLID, 1, COLORS[LIGHT_PINK] );
  m_thickBlackPen = CreatePen( PS_SOLID, 1, COLORS[BLACK] );
  m_thickWhitePen = CreatePen( PS_SOLID, 1, COLORS[WHITE] );
  m_thickRedPen = CreatePen( PS_SOLID, 1, COLORS[RED] );
  m_thickGreenPen = CreatePen( PS_SOLID, 1, COLORS[GREEN] );
  m_thickBluePen = CreatePen( PS_SOLID, 1, COLORS[BLUE] );

  m_greenBrush = CreateSolidBrush(COLORS[GREEN]);
  m_redBrush = CreateSolidBrush(COLORS[RED]);
  m_blueBrush = CreateSolidBrush(COLORS[BLUE]);
  m_greyBrush = CreateSolidBrush(COLORS[GREY]);
  m_brownBrush = CreateSolidBrush(COLORS[BROWN]);
  m_yellowBrush = CreateSolidBrush(COLORS[YELLOW]);
  m_lightBlueBrush = CreateSolidBrush(RGB(0,255,255));
  m_darkGreenBrush = CreateSolidBrush(COLORS[DARK_GREEN]);
  m_orangeBrush = CreateSolidBrush(COLORS[ORANGE]);

  m_hdc = NULL;
}

Wpgdi::~Wpgdi(){

  DeleteObject(m_blackPen);
  DeleteObject(m_whitePen);
  DeleteObject(m_redPen);
  DeleteObject(m_greenPen);
  DeleteObject(m_bluePen);
  DeleteObject(m_greyPen);
  DeleteObject(m_pinkPen);
  DeleteObject(m_orangePen);
  DeleteObject(m_yellowPen);
  DeleteObject(m_purplePen);
  DeleteObject(m_brownPen);
  DeleteObject(m_oldPen);

  DeleteObject(m_darkGreenPen);
  DeleteObject(m_ligthBluePen);
  DeleteObject(m_lightGreyPen);
  DeleteObject(m_lightPinkPen);

  DeleteObject(m_thickBlackPen);
  DeleteObject(m_thickWhitePen);
  DeleteObject(m_thickRedPen);
  DeleteObject(m_thickGreenPen);
  DeleteObject(m_thickBluePen);

  DeleteObject(m_greenBrush);
  DeleteObject(m_redBrush);
  DeleteObject(m_blueBrush);
  DeleteObject(m_oldBrush);
  DeleteObject(m_greyBrush);
  DeleteObject(m_brownBrush);
  DeleteObject(m_lightBlueBrush);
  DeleteObject(m_yellowBrush);
  DeleteObject(m_darkGreenBrush);
  DeleteObject(m_orangeBrush);
}
