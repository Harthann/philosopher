/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_ulock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/21 13:49:55 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		mutex_lock(pthread_mutex_t *mutex, char *state, t_philo *philo)
{
	int tmp;

	tmp = 1;
	while (*state && (tmp = is_alive(philo)) && !philo->status->simu_state)
		usleep(10);
	if (tmp == 0 || philo->status->simu_state)
		return (1);
	pthread_mutex_lock(mutex);
	*state = 1;
	return (0);
}

int		mutex_unlock(pthread_mutex_t *mutex, char *state)
{
	int tmp;

	tmp = pthread_mutex_unlock(mutex);
	*state = 0;
	return (tmp);
}
