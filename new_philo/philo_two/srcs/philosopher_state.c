/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/15 12:11:45 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*philosopher_nurse(void *philosopher)
{
	t_philo			*philo;
	long			time;
	struct timeval	start_t;
	struct timezone	tzp;

	philo = (t_philo*)philosopher;
	gettimeofday(&philo->timestamp, NULL);
	while (philo->status->simu_state != -1
		&& philo->status->simu_state != philo->status->philo_count)
	{
		gettimeofday(&start_t, &tzp);
		time = compare_time(start_t, philo->last_meal);
		if (time > philo->ttd)
		{
			print_state(philo->timestamp, philo->number, " died\n");
			philo->status->simu_state = -1;
		}
		usleep(philo->ttd);
	}
	return (0);
}

void	*philosopher_loop(void *philosopher)
{
	t_philo			*philo;

	philo = philosopher;
	if (!(philo->number % 2))
		usleep(50);
	while (1)
		actions(philo);
	return (NULL);
}

void	actions(t_philo *philo)
{
	print_state(philo->timestamp, philo->number, " is thinking\n");

	sem_wait(philo->status->semafork);

	print_state(philo->timestamp, philo->number, " has taken a fork \n");

	sem_wait(philo->status->semafork);

	print_state(philo->timestamp, philo->number, " has taken a fork \n");
	
	print_state(philo->timestamp, philo->number, " is eating\n");

	gettimeofday(&philo->last_meal, NULL);
	my_sleep(philo->tte);
	philo->count_meal--;
	if (philo->count_meal == 0)
		philo->status->simu_state += 1;
	sem_post(philo->status->semafork);
	sem_post(philo->status->semafork);

	print_state(philo->timestamp, philo->number, " is sleeping\n");

	my_sleep(philo->tts);
}
