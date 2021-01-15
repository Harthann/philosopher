/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 10:15:40 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/15 08:34:22 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long	compare_time(struct timeval	tp, struct timeval start_t)
{
	tp.tv_sec -= start_t.tv_sec;
	tp.tv_usec -= start_t.tv_usec;
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}
