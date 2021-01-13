/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/13 13:46:01 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	actions(t_philo *philo);

void	*philosopher_loop(void *philosopher)
{
	t_philo	*philo;

	philo = philosopher;
	if (!(philo->number % 2))
		usleep(50);
	// pthread_mutex_lock(&philo->action);
	// wait_start(*philo);
	// gettimeofday(&tp, NULL);
	// print_state(tp, philo->number, "STARTED\n");
	while (1)
		actions(philo);
	return (NULL);
}

void	actions(t_philo *philo)
{
	// pthread_mutex_unlock(&philo->action); // unlock/lock to activate death check
	// pthread_mutex_lock(&philo->action);
	print_state(philo->timestamp, philo->number, " is thinking\n");

	take_a_fork(philo);

	// pthread_mutex_unlock(&philo->action); // unlock/lock to activate death check
	// pthread_mutex_lock(&philo->action);
	print_state(philo->timestamp, philo->number, " is eating\n");

	gettimeofday(&philo->last_meal, NULL);
	my_sleep(philo->tte);
	philo->count_meal--;
	if (philo->count_meal == 0)
		philo->status->simu_state += 1;
	pthread_mutex_unlock(philo->mutex_left);
	pthread_mutex_unlock(philo->mutex_right);

	// pthread_mutex_unlock(&philo->action); // unlock/lock to activate death check
	// pthread_mutex_lock(&philo->action);
	print_state(philo->timestamp, philo->number, " is sleeping\n");

	my_sleep(philo->tts);
}
