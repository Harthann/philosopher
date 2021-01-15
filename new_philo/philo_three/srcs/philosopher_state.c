/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/15 12:45:09 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*philosopher_nurse(void *philosopher)
{
	t_philo			*philo;
	long			time;
	struct timeval	start_t;
	struct timezone	tzp;
	int				i;

	philo = (t_philo*)philosopher;
	i = 0;
	while (philo->status->simu_state != -1)
	{
		gettimeofday(&start_t, &tzp);
		time = compare_time(start_t, philo->last_meal);
		if (time > philo->ttd)
		{
			print_state(philo->timestamp, philo->number, " died\n");
			sem_wait(g_semaprint);
			philo->status->simu_state = -1;
			while (i++ < philo->status->philo_count)
				sem_post(philo->status->finished_meal);
			exit(0);
		}
		usleep(philo->ttd);
	}
	return (0);
}

int	philosopher_loop(void *philosopher)
{
	t_philo			*philo;
	pthread_t		vitals;

	philo = philosopher;
	pthread_create(&vitals, NULL, philosopher_nurse, philosopher);
	while (1)
		actions(philo);
	return (0);
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
		sem_post(philo->status->finished_meal);
	sem_post(philo->status->semafork);
	sem_post(philo->status->semafork);

	print_state(philo->timestamp, philo->number, " is sleeping\n");

	my_sleep(philo->tts);
}

// int	philosopher_eating(t_philo *philo)
// {
// 	long			time;
// 	struct timeval	start_t;
// 	struct timeval	tmp;
// 	struct timezone	tzp;

// 	gettimeofday(&start_t, &tzp);
// 	philo->last_meal = start_t;
// 	time = compare_time(start_t, philo->timestamp);
// 	print_state(time, philo->number, " is eating\n");
// 	tmp = start_t;
// 	while (compare_time(tmp, start_t) < philo->tte)
// 	{
// 		usleep(1000);
// 		gettimeofday(&tmp, &tzp);
// 	}
// 	philo->count_meal--;
// 	if (philo->count_meal == 0)
// 		sem_post(philo->status->finished_meal);
// 	sem_post(philo->status->semafork);
// 	sem_post(philo->status->semafork);
// 	if (philo->status->simu_state == -1)
// 		return (1);
// 	return (philosopher_sleeping(philo));
// }

// int	philosopher_sleeping(t_philo *philo)
// {
// 	long			time;
// 	struct timeval	start_t;
// 	struct timeval	tmp;
// 	struct timezone	tzp;

// 	gettimeofday(&start_t, &tzp);
// 	time = compare_time(start_t, philo->timestamp);
// 	print_state(time, philo->number, " is sleeping\n");
// 	tmp = start_t;
// 	while (compare_time(tmp, start_t) < philo->tts)
// 	{
// 		usleep(1000);
// 		gettimeofday(&tmp, &tzp);
// 	}
// 	return (philosopher_thinking(philo));
// }

// int	philosopher_thinking(t_philo *philo)
// {
// 	long			time;
// 	struct timezone	tzp;
// 	struct timeval	start_t;

// 	gettimeofday(&start_t, &tzp);
// 	time = compare_time(start_t, philo->timestamp);
// 	print_state(time, philo->number, " is thinking\n");
// 	if (take_a_fork(philo))
// 		return (1);
// 	return (philosopher_eating(philo));
// }
