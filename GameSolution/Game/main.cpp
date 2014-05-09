#include "Engine.h"
#include "Core.h"
#include "Startup.h"
#include "Debug\DebugMemory.h"
//#include "Logger\Logger.h"
#include "Profiling\Profiler.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	//int *a = new int[500];
	//a[0] = 5;
	//a[-1] = 0;

	//ASSERT(false);

	profiler.initialize("profiles.csv");

	//LOG(Info, "Initializing Setup instance");
	InitializeInstance();

	Core::Init("Window", screenWidth, screenHeight);

	Core::RegisterDrawFn(DrawFunction);
	Core::RegisterUpdateFn(UpdateFunction);

	//LOG(Info, "Game started");
	Core::GameLoop();

	//LOG(Info, "Deleting everything");
	instance.DeleteAll();
	//LOG(Info, "Game ended");
	//END_LOG;
	profiler.shutdown();
}

