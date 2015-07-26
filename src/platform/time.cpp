#include <platform_definitions.h>

#ifdef WINDOWS_LOCAL
	#include <Windows.h>
#elif defined(LINUX_NATIVE)
	#include <unistd.h>
	#include <sys/time.h>	
#endif

int usleep(long milliseconds) {
#ifdef WINDOWS_LOCAL 
	Sleep(milliseconds);
	return 0;
#elif defined (LINUX_NATIVE)
	return usleep(microseconds * 1000);
	
#endif
}

long currentTimeInMillis() {
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