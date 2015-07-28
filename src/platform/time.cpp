#include <platform_definitions.h>

#ifdef WINDOWS_LOCAL
	#include <Windows.h>
#elif defined(LINUX_NATIVE)
	#include <unistd.h>
	#include <sys/time.h>	
#endif

int time_system::sleepInMillis(long milliseconds) {
#ifdef WINDOWS_LOCAL 
	Sleep(milliseconds);
	return 0;
#elif defined (LINUX_NATIVE)
	return usleep(milliseconds);
	
#endif
}

long time_system::currentTimeInMillis() {
#ifdef WINDOWS_LOCAL 
	 SYSTEMTIME st;
	 GetSystemTime(&st);

	 return ( st.wHour * 60 * 60 + st.wMinute * 60 + st.wSecond) * 1000 + st.wMilliseconds;
#elif defined (LINUX_NATIVE)
	timeval tv;
	gettimeofday(&tv, NULL);
	long millis = (int)(tv.tv_usec / 1000) + tv.tv_sec * 1000;
	return millis;
#endif
}