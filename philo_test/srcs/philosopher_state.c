/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:46 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/12 11:57:47 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philosopher_loop(void *philosopher)
{
	t_philo	*philo;

	philo = philosopher;
	wait_start(*philo);
	if (philo->number % 2)
	{
		while (1)
		{
			philosopher_thinking(philo);
			philosopher_eating(philo);
			philosopher_sleeping(philo);
			// if (philosopher_thinking(philo))
				// break ;
			// if (philosopher_eating(philo))
				// break ;
			// if (philosopher_sleeping(philo))
				// break ;
		}
	}
	else
	{
		while (1)
		{
			philosopher_sleeping(philo);
			philosopher_thinking(philo);
			philosopher_eating(philo);
		// 	if (philosopher_sleeping(philo))
		// 		break ;
		// 	if (philosopher_thinking(philo))
		// 		break ;
		// 	if (philosopher_eating(philo))
		// 		break ;
		}
	}
	return (NULL);
}

int	philosopher_eating(t_philo *philo)
{
	struct timeval	start_t;

	gettimeofday(&start_t, NULL);
	philo->last_meal = start_t;
	print_state(philo->timestamp, philo->number, " is eating\n");
	// pthread_mutex_lock(&philo->action);
	my_sleep(philo->tte);
	// pthread_mutex_unlock(&philo->action);
	philo->count_meal--;
	if (philo->count_meal == 0)
		philo->status->simu_state += 1;
	pthread_mutex_unlock(philo->mutex_left);
	pthread_mutex_unlock(philo->mutex_right);
	// if (philo->status->simu_state == -1
	// 	|| philo->status->simu_state == philo->status->philo_count)
	// 	return (1);
	return (0);
}

int	philosopher_sleeping(t_philo *philo)
{
	print_state(philo->timestamp, philo->number, " is sleeping\n");
	my_sleep(philo->tts);
	// if (philo->status->simu_state == -1
	// 	|| philo->status->simu_state == philo->status->philo_count)
	// 	return (1);
	return (0);
}

int	philosopher_thinking(t_philo *philo)
{
	print_state(philo->timestamp, philo->number, " is thinking\n");
	// if (take_a_fork(philo))
	// 	return (1);
	take_a_fork(philo);
	// if (philo->status->simu_state == -1
	// 	|| philo->status->simu_state == philo->status->philo_count)
	// 	return (1);
	return (0);
}
