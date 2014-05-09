#ifndef LOGGER
#define LOGGER

#pragma warning(disable:4127)

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using std::vector;
using std::string;

enum Severity { Info, Warning, Error, Severe };

#define LOG( severity, message) Logger::Log( severity, message, __LINE__, __FILE__ )
#define END_LOG Logger::shutDown();
#define ASSERT(expr, ...) do{ if(!(expr)){LOG(Severe, #expr##" "##__VA_ARGS__); END_LOG; exit(1);}}while(0);//do{if(!(expr)){Logger::Log(Error, (#expr##" "##__VA_ARGS__))}}while(0);

#pragma warning ( disable : 4100)

class Logger
{
public:
#if LOG_ON
	Logger(void);
	~Logger(void);
	static void StringReplace(string& str, const string& from, const string& to);
	static string Sanitize(string str);
	static void Log( Severity severity, const char* message, int logLine, const char * logFile);
	static void shutDown();
#else
	Logger(void){}
	~Logger(void){}
	static void StringReplace(string& str, const string& from, const string& to){}
	static string Sanitize(string str){}
	/*static void Log( Severity severity, const char* message, const char * logFile, int logLine){}*/
	static void Log( Severity severity, const char* message, int logLine, const char * logFile){}
	static void shutDown(){}
#endif

private:
#if LOG_ON
	static vector <string> logList;
	static vector <Severity> severityList;
	static void WriteFile();
#endif
};

#pragma warning ( default : 4100)

#endif