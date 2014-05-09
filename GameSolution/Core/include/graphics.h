#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Core.h"
#include "window.h"

namespace Core
{

typedef DWORD RGB;

class CORE_SHARED Graphics
{
public:
	enum TEXTBKGMODE { Transparent, Opaque };
	static Graphics* Init( Window wnd, int width, int height );

	void BeginDrawing();
	void EndDrawing();
	// this function expects an array of floats[4*count]
	// organized in x,y order [ x1, y1, x2, y2, ... etc. ]
	void DrawLines( int count, float* lines );
	void DrawLine( float x1, float y1, float x2, float y2 );
	// expects floats[ 2 * (count + 1) ]
	void DrawLineStrip( int count, float* lines );
	void DrawString( int x, int y, const char* string );

	// this sets the color for subsequent draw commands
	void SetColor( RGB color );
	void SetBackgroundColor( RGB color );
	void SetTextBackgroundMode( TEXTBKGMODE );

	void Flip();

private:
	Graphics( Window wnd, int width, int height );
	int width;
	int height;
	RGB currentColor;
	RGB backgroundColor;
	Window wnd;
	HDC winDC;
	HDC memDC;
	HPEN oldPen;
	HPEN currentPen;
	HBRUSH oldBrush;
	HBRUSH currentBrush;
	HBITMAP oldBitmap;
	HBITMAP currentBitmap;
	HFONT oldFont;
	HFONT currentFont;
};

}

#endif // _GRAPHICS_H_