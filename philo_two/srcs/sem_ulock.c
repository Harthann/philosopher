/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_ulock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/08 12:21:12 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		sem_lock(sem_t *semafork, char *state, t_philo *philo)
{
	int tmp;

	tmp = 1;

	while (*state && (tmp = is_alive(philo)) && !philo->status->simu_state)
		usleep(50);
	if (tmp == 0 || philo->status->simu_state)
		return (1);
	sem_wait(semafork);
	state = 0;
	return (0);
}

int		sem_unlock(sem_t *semafork, char *state)
{
	int tmp;

	tmp = 0;
	sem_post(semafork);
	state = 0;
	return (tmp);
}
