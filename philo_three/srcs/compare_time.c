/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 10:15:40 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/08 11:35:43 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long	compare_time(struct timeval	tp, struct timeval start_t)
{
	long time;

	time = tp.tv_sec * 1000;
	time += tp.tv_usec / 1000;
	time -= start_t.tv_sec * 1000;
	time -= start_t.tv_usec / 1000;
	return (time);
}
