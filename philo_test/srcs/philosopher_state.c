/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/15 09:01:32 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"


void	*philosopher_nurse(void *philosopher)
{
	t_philo			*philo;
	long			time;
	struct timeval	start_t;

	philo = (t_philo*)philosopher;
	while (1)
	{
		pthread_mutex_lock(&philo->action);
		gettimeofday(&start_t, NULL);
		time = compare_time(start_t, philo->last_meal);
		if (time > philo->ttd)
		{
			print_state(philo->timestamp, philo->number, " died\n");
			pthread_mutex_lock(g_printing);
			philo->status->simu_state = -1;
			break ;
		}
		pthread_mutex_unlock(&philo->action);
		usleep(philo->ttd);
	}
	return (0);
}

void	*philosopher_loop(void *philosopher)
{
	t_philo	*philo;

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

	pthread_mutex_lock(philo->mutex_left);

	print_state(philo->timestamp, philo->number, " has taken a fork \n");

	pthread_mutex_lock(philo->mutex_right);

	print_state(philo->timestamp, philo->number, " has taken a fork \n");
	
	print_state(philo->timestamp, philo->number, " is eating\n");

	gettimeofday(&philo->last_meal, NULL);
	my_sleep(philo->tte);
	philo->count_meal--;
	if (philo->count_meal == 0)
		philo->status->simu_state += 1;
	pthread_mutex_unlock(philo->mutex_right);
	pthread_mutex_unlock(philo->mutex_left);

	print_state(philo->timestamp, philo->number, " is sleeping\n");

	my_sleep(philo->tts);
}
