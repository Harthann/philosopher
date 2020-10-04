/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/04 13:46:04 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	my_sleep(long time)
{
	struct timeval	tp;
	struct timezone tzp;
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
		;
}
