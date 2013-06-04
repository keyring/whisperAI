/****************************************************************************
 *
 *    Wpgdi.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *
 *    DESC: Whisper Packaging GDI. A singleton class to help alleviate the 
 *          tedium of using the GDI.Call each method using the #define for 
 *          wpgdi-> .
 ***************************************************************************/

#ifndef __WPGDI_H__
#define __WPGDI_H__

#include <windows.h>
#include <string>
#include <vector>
#include <cassert>

#include "Vector2d.h"

#define wpgdi Wpgdi::Instance();

const int NUMCOLORS = 15;
const COLORREF COLORS[NUMCOLORS] = {
  RGB( 255, 0, 0 ),
  RGB( 0, 0, 255 ),
  RGB( 0, 255, 0 ),
  RGB( 0, 0, 0 ),
  RGB(255,200,200),
  RGB(200,200,200),
  RGB( 255,255,0 ),
  RGB( 255,170,0 ),
  RGB( 255,0,170 ),
  RGB( 133,99,0 ),
  RGB(255,255,255),
  RGB( 0,100,0 ),
  RGB( 0,255,255 ),
  RGB(200,200,200),
  RGB(255,230,230)
};


class Wpgdi{

 public:
  int GetNumPenColors() const { return NUMCOLORS; }

  enum{
    RED, BLUE, GREEN, BLACK, PINK, GREY, YELLOW, ORANGE, PURPLE,BROWN,
    WHITE, DARK_GREEN, LIGHT_BLUE, LIGHT_GREY, LIGHT_PINK, HOLLOW
  };

 private:

  HPEN m_oldPen;

  HPEN m_blackPen, m_whitePen, m_redPen, m_greenPen, m_bluePen, m_greyPen,
    m_pinkPen, m_orangePen, m_yellowPen, m_purplePen, m_brownPen,
    m_darkGreenPen, m_lightBluePen, m_lightGreyPen, m_lightPinkPen,
    m_thickBlackPen, m_thickWhitePen, m_thickRedPen, m_thickGreenPen,
    m_thickBluePen;

  HBRUSH m_oldBrush;

  HBRUSH m_redBrush, m_greenBrush, m_blueBrush, m_greyBrush, m_brownBrush,
    m_yellowBrush, m_orangeBrush, m_lightBlueBrush, m_darkGreenBrush;

  HDC m_hdc;

  Wpgdi();
  Wpgdi( const Wpgdi& );
  Wpgdi& operator=(const Wpgdi&);

 public:

  ~Wpgdi();
  static Wpgdi *Instance();

  void BlackPen(){if(m_hdc){SelectObject(m_hdc, m_blackPen);}};
  void WhitePen(){if(m_hdc){SelectObject(m_hdc, m_WhitePen);}}
  void RedPen()  {if(m_hdc){SelectObject(m_hdc, m_RedPen);}}
  void GreenPen(){if(m_hdc){SelectObject(m_hdc, m_GreenPen);}}
  void BluePen() {if(m_hdc){SelectObject(m_hdc, m_BluePen);}}
  void GreyPen() {if(m_hdc){SelectObject(m_hdc, m_GreyPen);}}
  void PinkPen() {if(m_hdc){SelectObject(m_hdc, m_PinkPen);}}
  void YellowPen() {if(m_hdc){SelectObject(m_hdc, m_YellowPen);}}
  void OrangePen() {if(m_hdc){SelectObject(m_hdc, m_OrangePen);}}
  void PurplePen() {if(m_hdc){SelectObject(m_hdc, m_PurplePen);}}
  void BrownPen() {if(m_hdc){SelectObject(m_hdc, m_BrownPen);}}
  
  void DarkGreenPen() {if(m_hdc){SelectObject(m_hdc, m_DarkGreenPen);}}
  void LightBluePen() {if(m_hdc){SelectObject(m_hdc, m_LightBluePen);}}
  void LightGreyPen() {if(m_hdc){SelectObject(m_hdc, m_LightGreyPen);}}
  void LightPinkPen() {if(m_hdc){SelectObject(m_hdc, m_LightPinkPen);}}

  void ThickBlackPen(){if(m_hdc){SelectObject(m_hdc, m_ThickBlackPen);}}
  void ThickWhitePen(){if(m_hdc){SelectObject(m_hdc, m_ThickWhitePen);}}
  void ThickRedPen()  {if(m_hdc){SelectObject(m_hdc, m_ThickRedPen);}}
  void ThickGreenPen(){if(m_hdc){SelectObject(m_hdc, m_ThickGreenPen);}}
  void ThickBluePen() {if(m_hdc){SelectObject(m_hdc, m_ThickBluePen);}}

  void BlackBrush(){if(m_hdc)SelectObject(m_hdc, GetStockObject(BLACK_BRUSH));}
  void WhiteBrush(){if(m_hdc)SelectObject(m_hdc, GetStockObject(WHITE_BRUSH));} 
  void HollowBrush(){if(m_hdc)SelectObject(m_hdc, GetStockObject(HOLLOW_BRUSH));}
  void GreenBrush(){if(m_hdc)SelectObject(m_hdc, m_GreenBrush);}
  void RedBrush()  {if(m_hdc)SelectObject(m_hdc, m_RedBrush);}
  void BlueBrush()  {if(m_hdc)SelectObject(m_hdc, m_BlueBrush);}
  void GreyBrush()  {if(m_hdc)SelectObject(m_hdc, m_GreyBrush);}
  void BrownBrush() {if(m_hdc)SelectObject(m_hdc, m_BrownBrush);}
  void YellowBrush() {if(m_hdc)SelectObject(m_hdc, m_YellowBrush);}
  void LightBlueBrush() {if(m_hdc)SelectObject(m_hdc, m_LightBlueBrush);}
  void DarkGreenBrush() {if(m_hdc)SelectObject(m_hdc, m_DarkGreenBrush);}
  void OrangeBrush() {if(m_hdc)SelectObject(m_hdc, m_OrangeBrush);}

  void StartDrawing( HDC hdc ){
    /* ALWAYS call this before drawing */
    assert(m_hdc == NULL);
    m_hdc = hdc;

    m_oldPen = (HPEN)SelectObject(hdc, m_blackPen);
    SelectObject(hdc, m_oldPen);

    m_oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    SelectObject(hdc, m_oldBrush);
  }

  void StopDrawing( HDC hdc ){
    /* ALWAYS call this after drawing */
    assert(hdc ==NULL);

    SelectObject(hdc, m_oldPen);
    SelectObject(hdc, m_oldBrush);

    m_hdc = NULL;
  }

#endif	/* __WPGDI_H__ */
