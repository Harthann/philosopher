/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/11 14:12:35 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long	get_time()
{
	struct timeval	tp;
	long			ret;

	gettimeofday(&tp, NULL);
	return(tp.tv_sec * 1000 + tp.tv_usec * 1000);

}

void	my_sleep(long time)
{
	// struct timeval	tp;
	// struct timezone	tzp;
	// struct timeval	tmp;

	// gettimeofday(&tp, &tzp);
	// tmp = tp;
	// while (compare_time(tmp, tp) < time)
	// {
	// 	usleep(50);
	// 	gettimeofday(&tmp, &tzp);
	// }
	long start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= time)
			break ;
		usleep(50);
	}
}

void	wait_start(t_philo philo)
{
	while (!philo.status->started)
		usleep(1000);
}
