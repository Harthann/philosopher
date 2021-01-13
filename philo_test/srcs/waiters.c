/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/13 08:53:59 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	my_sleep(long time)
{
	struct timeval	tp;
	struct timezone	tzp;
	struct timeval	tmp;

	gettimeofday(&tp, &tzp);
	tmp = tp;
	while (compare_time(tmp, tp) < time)
	{
		usleep(1000);
		gettimeofday(&tmp, &tzp);
	}
}

void	wait_start(t_philo philo)
{
	pthread_mutex_lock(&g_start);
	pthread_mutex_unlock(&g_start);
	(void)philo;
	// while (!philo.status->started)
	// 	usleep(1000);
}
