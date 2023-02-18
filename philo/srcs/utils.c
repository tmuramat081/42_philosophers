#include "philosophers.h"

long	gettime_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		exit(1);
	return ((long)(tv.tv_sec * 1000) + (long)(tv.tv_usec / 1000));
}

