#ifndef PRECISION_TIMER_H_
#define PRECISION_TIMER_H_

#include <stdio.h>
#include <windows.h>

class precisiontimer
{
	LARGE_INTEGER lFreq, lStart;
public:
	FILE *fpLog;
	precisiontimer(FILE *fp) : fpLog(fp) { QueryPerformanceFrequency(&lFreq); }
	void Start() { QueryPerformanceCounter(&lStart); }
	void LogTime(const char *message)
	{
		LARGE_INTEGER lEnd;
		QueryPerformanceCounter(&lEnd);
		double v = double(lEnd.QuadPart - lStart.QuadPart) / double(lFreq.QuadPart);
		fprintf(fpLog, "%8.3f - %s\n", v, message);
		Flush();
		QueryPerformanceCounter(&lStart);
	}
	void Flush()
	{
		fflush(fpLog);
	}
};

#endif // PRECISION_TIMER_H_