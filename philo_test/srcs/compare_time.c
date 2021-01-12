/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 10:15:40 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/08 08:49:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long	compare_time(struct timeval	tp, struct timeval start_t)
{
	long	time;

	time = tp.tv_sec * 1000;
	time += tp.tv_usec / 1000;
	time -= start_t.tv_sec * 1000;
	time -= start_t.tv_usec / 1000;
	return (time);
}
