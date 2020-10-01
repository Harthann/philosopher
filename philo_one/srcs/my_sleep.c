/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/01 10:10:35 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	my_sleep(t_philo *philo, long time)
{
	struct timeval	tp;
	struct timezone tzp;
	struct timeval	tmp;

	gettimeofday(&tp, &tzp);
	gettimeofday(&tmp, &tzp);
	while (is_alive(philo) && compare_time(tmp, tp) < time)
	{
		usleep(1000);
		gettimeofday(&tmp, &tzp);
	}
}
