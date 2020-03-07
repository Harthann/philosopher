#include "philo_two.h"

long	compare_time(struct timeval	tp, struct timeval start_t)
{
	long time;

	time = tp.tv_sec * 1000;
	time += tp.tv_usec / 1000;
	time -= start_t.tv_sec * 1000;
	time -= start_t.tv_usec / 1000;
	return (time);
}