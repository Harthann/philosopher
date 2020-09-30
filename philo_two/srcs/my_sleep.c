/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:00:00 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/30 10:57:42 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	my_sleep(t_philo *philo)
{
	struct timeval	tp;
	struct timezone tzp;
	struct timeval	tmp;

	gettimeofday(&tp, &tzp);
	gettimeofday(&tmp, &tzp);
	while (is_alive(philo) && compare_time(tmp, tp) < philo->tts)
	{
		usleep(1000);
		gettimeofday(&tmp, &tzp);
	}
}
