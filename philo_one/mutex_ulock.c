/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_ulock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/06 10:10:27 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		mutex_lock(pthread_mutex_t *mutex, char *state, t_philo *philo)
{
	int tmp;

	tmp = 1;
	while (*state && (tmp = is_alive(philo)) && !philo->status->simu_state)
		usleep(50);
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
	if (tmp != EPERM)
		*state = 0;
	return (tmp);
}