/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/08 11:36:27 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		is_alive(t_philo *philo)
{
	long			tmp;
	long			time;
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
	struct timeval	tp;
	struct timezone tzp;

	gettimeofday(&start_t, &tzp);
	philo->status->last_meal[philo->number - 1] = start_t;
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is eating\n");
	time = 0;
	while (is_alive(philo) && time < philo->tte && !philo->status->simu_state)
	{
		gettimeofday(&tp, &tzp);
		time = compare_time(tp, start_t);
	}
	if (philo->status->count_meal[philo->number - 1] > 0)
		philo->status->count_meal[philo->number - 1]--;
	if (check_meal_count(*philo->status))
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
	print_state(time, philo->number, " is sleeping\n");
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
	struct timezone tzp;
	struct timeval	start_t;

	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is thinking\n");
	take_a_fork(philo);
	return (0);
}
