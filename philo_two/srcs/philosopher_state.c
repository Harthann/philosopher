/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/11 10:27:56 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*philosopher_loop(void *philosopher)
{
	t_philo			*philo;

	philo = philosopher;
	wait_start(*philo);
	if (philo->number % 2)
		philosopher_thinking(philo);
	else
		philosopher_sleeping(philo);
	if (!philo->count_meal)
		philo->status->simu_state += 1;
	return (NULL);
}

int	philosopher_eating(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timeval	tmp;
	struct timezone	tzp;

	gettimeofday(&start_t, &tzp);
	philo->last_meal = start_t;
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is eating\n");
	tmp = start_t;
	while (compare_time(tmp, start_t) < philo->tte)
	{
		usleep(1000);
		gettimeofday(&tmp, &tzp);
	}
	philo->count_meal--;
	if (philo->count_meal == 0)
		philo->status->simu_state += 1;
	sem_post(philo->status->semafork);
	sem_post(philo->status->semafork);
	if (philo->status->simu_state == -1)
		return (1);
	return (philosopher_sleeping(philo));
}

int	philosopher_sleeping(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timeval	tmp;
	struct timezone	tzp;

	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is sleeping\n");
	tmp = start_t;
	while (compare_time(tmp, start_t) < philo->tts)
	{
		usleep(1000);
		gettimeofday(&tmp, &tzp);
	}
	return (philosopher_thinking(philo));
}

int	philosopher_thinking(t_philo *philo)
{
	long			time;
	struct timezone	tzp;
	struct timeval	start_t;

	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " is thinking\n");
	if (take_a_fork(philo))
		return (1);
	return (philosopher_eating(philo));
}
