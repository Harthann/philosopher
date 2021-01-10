/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/07 11:06:06 by user42           ###   ########.fr       */
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
	while (!philo.status->started)
		usleep(1000);
}
