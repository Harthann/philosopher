#include "philo_one.h"

int		is_alive(t_philo *philo)
{
	long tmp;
	long time;
	struct timeval	tp;
	struct timezone tzp;

	if (philo->state == 3)
		return (0);
	gettimeofday(&tp, &tzp);
	tmp = compare_time(tp, philo->status->last_meal[philo->number - 1]);
	time = compare_time(tp, philo->timestamp);
	if (tmp >= philo->ttd)
	{
		philo->status->simu_state = 1;
		print_state(time, philo->number, " died\n", 0);
		if (philo->state == 1)
		{
			pthread_mutex_unlock(philo->mutex_right);
			pthread_mutex_unlock(philo->mutex_left);
		}
		philo->state = 3;
		return (0);
	}
	return (1);
}

int		philosopher_eating(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timeval	tp;
	struct timezone tzp;

	gettimeofday(&start_t, &tzp);
	philo->status->last_meal[philo->number - 1] = start_t;
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is eating\n", 0);
	time = 0;
	while (is_alive(philo) && time < philo->tte && philo->status->simu_state == 0)
	{
		gettimeofday(&tp, &tzp);
		time = compare_time(tp, start_t);
	}
	philo->status->count_meal < 0 ? 0 : philo->status->count_meal--;
	if (philo->status->count_meal == 0)
		philo->status->simu_state = 1;
	return (0);
}

int		philosopher_sleeping(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timeval	tp;
	struct timezone tzp;

	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is sleeping\n", 0);
	time = 0;
	while (is_alive(philo) && time < philo->tts && !philo->status->simu_state)
	{
		gettimeofday(&tp, &tzp);
		time = compare_time(tp, start_t);
	}
	return (0);
}

int		philosopher_thinking(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	gettimeofday(&philo->think_tmst, &tzp);
	time = compare_time(philo->think_tmst, philo->timestamp);
	print_state(time, philo->number, " is thinking\n", 0);
	while (!check_priority(philo->number - 1, *philo, 'r') && !philo->status->simu_state && is_alive(philo))
	{
		gettimeofday(&start_t, &tzp);
		time = compare_time(start_t, philo->think_tmst);
	}
	take_a_fork(philo, 'r');
	if (!is_alive(philo) && philo->status->simu_state == 1)
	{
		mutex_unlock(philo->mutex_right, philo->fork_right);
		return (1);
	}
	while (!check_priority(philo->number - 1, *philo, 'l') && !philo->status->simu_state && is_alive(philo))
	{
		gettimeofday(&start_t, &tzp);
		time = compare_time(start_t, philo->think_tmst);
	}
	take_a_fork(philo, 'l');
	return (0);
}