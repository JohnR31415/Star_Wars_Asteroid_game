#ifndef CORE_H
#define CORE_H

#ifdef CORE_EXPORTS
#define CORE_SHARED __declspec( dllexport )
#else
#define CORE_SHARED __declspec( dllimport )
#endif


#include "window.h"
#include "input.h"
#include "graphics.h"

namespace Core
{
class Graphics;

typedef bool UpdateFn( float dt );
typedef void DrawFn( Graphics& graphics );

CORE_SHARED void Init( char* name, unsigned width, unsigned height, unsigned targetFPS = 60 );
CORE_SHARED void Shutdown();
CORE_SHARED void RegisterUpdateFn( UpdateFn* _update );
CORE_SHARED void RegisterDrawFn( DrawFn* _draw );
CORE_SHARED void GameLoop();

}

#endif // CORE_H