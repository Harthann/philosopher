/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/28 11:21:11 by nieyraud         ###   ########.fr       */
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
	if (tmp >= philo->ttd)
	{
		philo->status->simu_state = -1;
		time = compare_time(tp, philo->timestamp);
		print_state(time, philo->number, " died\n");
		philo->state = 3;
		return (0);
	}
	return (1);
}

int		philosopher_eating(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	if (!is_alive(philo))
		return (1);
	// philo->state = 1;
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	philo->last_meal = start_t;
	print_state(time, philo->number, " is eating\n");
	usleep(philo->tte * 1000);
	if (philo->count_meal > 0)
		philo->count_meal--;
	pthread_mutex_unlock(philo->mutex_left);
	pthread_mutex_unlock(philo->mutex_right);
	if (!philo->count_meal)
		return (1);
	return (philosopher_sleeping(philo));
}

int		philosopher_sleeping(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	if (!is_alive(philo))
		return (1);
	// philo->state = 2;
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is sleeping\n");
	time = compare_time(start_t, philo->last_meal);
	if (philo->ttd - time < philo->tts)
	{
		usleep(time * 1000);
		return (is_alive(philo));
	}
	else
		usleep(philo->tts * 1000);
	return (philosopher_thinking(philo));
}

int		philosopher_thinking(t_philo *philo)
{
	long			time;
	struct timezone tzp;
	struct timeval	start_t;

	if (!is_alive(philo))
		return (1);
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is thinking\n");
	philo->state = 0;
	take_a_fork(philo);
	return (philosopher_eating(philo));
}
