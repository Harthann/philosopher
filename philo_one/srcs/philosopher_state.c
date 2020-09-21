/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/21 16:37:00 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		is_alive(t_philo *philo)
{
	long			tmp;
	long			time;
	struct timeval	tp;
	struct timezone tzp;

	if (philo->state == 3)
		return (0);
	gettimeofday(&tp, &tzp);
	tmp = compare_time(tp, philo->last_meal);
	time = compare_time(tp, philo->timestamp);
	if (tmp >= philo->ttd)
	{
		philo->status->simu_state = 1;
		print_state(time, philo->number, " died\n");
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
	// struct timeval	tp;
	struct timezone tzp;

	philo->state = 1;
	gettimeofday(&start_t, &tzp);
	philo->last_meal = start_t;
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is eating\n");
	time = 0;
	// while (is_alive(philo) && time < philo->tte && !philo->status->simu_state)
	// {
	// 	gettimeofday(&tp, &tzp);
	// 	time = compare_time(tp, start_t);
	// }
	if (philo->tte > philo->ttd)
		usleep(philo->ttd * 1000);
	else
		usleep(philo->tte * 1000);
	if (philo->count_meal > 0)
		philo->count_meal--;
	if (philo->count_meal == 0)
		return (1);
	return (0);
}

int		philosopher_sleeping(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	philo->state = 2;
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is sleeping\n");
	time = 0;
	if (philo->tts > philo->ttd)
		usleep(philo->ttd * 1000);
	else
		usleep(philo->tts * 1000);
	return (0);
}

int		philosopher_thinking(t_philo *philo)
{
	long			time;
	struct timezone tzp;
	struct timeval	start_t;

	philo->state = 0;
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is thinking\n");
	take_a_fork(philo);
	return (0);
}
