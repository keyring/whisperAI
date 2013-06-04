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
  void WhitePen(){if(m_hdc){SelectObject(m_hdc, m_whitePen);}}
  void RedPen()  {if(m_hdc){SelectObject(m_hdc, m_redPen);}}
  void GreenPen(){if(m_hdc){SelectObject(m_hdc, m_greenPen);}}
  void BluePen() {if(m_hdc){SelectObject(m_hdc, m_bluePen);}}
  void GreyPen() {if(m_hdc){SelectObject(m_hdc, m_greyPen);}}
  void PinkPen() {if(m_hdc){SelectObject(m_hdc, m_pinkPen);}}
  void YellowPen() {if(m_hdc){SelectObject(m_hdc, m_yellowPen);}}
  void OrangePen() {if(m_hdc){SelectObject(m_hdc, m_orangePen);}}
  void PurplePen() {if(m_hdc){SelectObject(m_hdc, m_purplePen);}}
  void BrownPen() {if(m_hdc){SelectObject(m_hdc, m_brownPen);}}
  
  void DarkGreenPen() {if(m_hdc){SelectObject(m_hdc, m_darkGreenPen);}}
  void LightBluePen() {if(m_hdc){SelectObject(m_hdc, m_lightBluePen);}}
  void LightGreyPen() {if(m_hdc){SelectObject(m_hdc, m_lightGreyPen);}}
  void LightPinkPen() {if(m_hdc){SelectObject(m_hdc, m_lightPinkPen);}}

  void ThickBlackPen(){if(m_hdc){SelectObject(m_hdc, m_thickBlackPen);}}
  void ThickWhitePen(){if(m_hdc){SelectObject(m_hdc, m_thickWhitePen);}}
  void ThickRedPen()  {if(m_hdc){SelectObject(m_hdc, m_thickRedPen);}}
  void ThickGreenPen(){if(m_hdc){SelectObject(m_hdc, m_thickGreenPen);}}
  void ThickBluePen() {if(m_hdc){SelectObject(m_hdc, m_thickBluePen);}}

  void BlackBrush(){if(m_hdc)SelectObject(m_hdc, GetStockObject(BLACK_BRUSH));}
  void WhiteBrush(){if(m_hdc)SelectObject(m_hdc, GetStockObject(WHITE_BRUSH));} 
  void HollowBrush(){if(m_hdc)SelectObject(m_hdc, GetStockObject(HOLLOW_BRUSH));}
  void GreenBrush(){if(m_hdc)SelectObject(m_hdc, m_greenBrush);}
  void RedBrush()  {if(m_hdc)SelectObject(m_hdc, m_redBrush);}
  void BlueBrush()  {if(m_hdc)SelectObject(m_hdc, m_blueBrush);}
  void GreyBrush()  {if(m_hdc)SelectObject(m_hdc, m_greyBrush);}
  void BrownBrush() {if(m_hdc)SelectObject(m_hdc, m_brownBrush);}
  void YellowBrush() {if(m_hdc)SelectObject(m_hdc, m_yellowBrush);}
  void LightBlueBrush() {if(m_hdc)SelectObject(m_hdc, m_lightBlueBrush);}
  void DarkGreenBrush() {if(m_hdc)SelectObject(m_hdc, m_darkGreenBrush);}
  void OrangeBrush() {if(m_hdc)SelectObject(m_hdc, m_orangeBrush);}

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

  void SetPenColor( int color ){

    assert(color < NUMCOLORS);
    switch(color){
    case BLACK: BlackPen(); return;
    case WHITE: WhitePen(); return;
    case RED: RedPen(); return;
    case GREEN: GreenPen(); return;
    case BLUE: BluePen(); return;
    case PINK: PinkPen(); return;
    case GREY: GreyPen(); return;
    case YELLOW: YellowPen(); return;
    case ORANGE: OrangePen(); return;
    case PURPLE: PurplePen(); return;
    case BROWN: BrownPen(); return;
    case LIGHT_BLUE: LightBluePen(); return;
    case LIGHT_GREY: LightGreyPen(); return;
    case LIGHT_PINK: LightPinkPen(); return;
    }
  }





};

#endif	/* __WPGDI_H__ */
