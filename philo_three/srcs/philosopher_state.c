/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/02 12:06:22 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	struct timeval	tmp;
	struct timezone tzp;

	gettimeofday(&start_t, &tzp);
	philo->last_meal = start_t;
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is eating\n");
	gettimeofday(&tmp, &tzp);
	while (compare_time(tmp, start_t) < philo->tte)
	{
		usleep(1000);
		gettimeofday(&tmp, &tzp);
	}
	if (philo->count_meal > 0)
		philo->count_meal--;
	sem_post(philo->status->semafork);
	sem_post(philo->status->semafork);
	if (!philo->count_meal)
		return (0);
	if (!is_alive(philo))
		return (-1);
	return (philosopher_sleeping(philo));
}

int		philosopher_sleeping(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timeval	tmp;
	struct timezone tzp;

	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is sleeping\n");
	gettimeofday(&tmp, &tzp);
	while (compare_time(tmp, start_t) < philo->tts)
	{
		usleep(1000);
		gettimeofday(&tmp, &tzp);
	}
	if (!is_alive(philo))
		return (-1);
	return (philosopher_thinking(philo));
}

int		philosopher_thinking(t_philo *philo)
{
	long			time;
	struct timezone tzp;
	struct timeval	start_t;

	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is thinking\n");
	philo->state = 0;
	take_a_fork(philo);
	if (!is_alive(philo))
		return (-1);
	return (philosopher_eating(philo));
}
