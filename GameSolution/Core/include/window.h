#ifndef _WINDOW_H_
#define _WINDOW_H_

#ifndef UNICODE
#define UNICODE
#endif 

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Core
{
typedef HWND Window;

Window InitWindow(HINSTANCE hInstance, char* name, int width, int height);

}
#endif _WINDOW_H_