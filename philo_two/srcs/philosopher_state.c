/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/30 10:31:42 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		is_alive(t_philo *philo)
{
	long			tmp;
	long			time;
	struct timeval	tp;
	struct timezone tzp;

	if (philo->state == 3 || philo->status->simu_state == -1)
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
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	philo->last_meal = start_t;
	print_state(time, philo->number, " is eating\n");
	my_sleep(philo);
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
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is sleeping\n");
	my_sleep(philo);
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
