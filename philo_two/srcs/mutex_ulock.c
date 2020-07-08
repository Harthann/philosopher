/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_ulock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/08 11:35:16 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		mutex_lock(sem_t *sem_fork, char *state, t_philo *philo)
{
	int tmp;

	tmp = 1;
	while (*state && (tmp = is_alive(philo)) && !philo->status->simu_state)
		usleep(50);
	if (tmp == 0 || philo->status->simu_state)
		return (1);
	*state = 1;
	return (0);
}

int		mutex_unlock(sem_t *sem_fork, char *state)
{
	int tmp;

	*state = 0;
	return (tmp);
}
