/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 10:04:34 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/07 11:06:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	check_validity(t_philo *list)
{
	int	i;

	i = 0;
	if (!list || !list->status || list->ttd < 0
		|| list->tte < 0 || list->tts < 0)
		return (1);
	if (list->count_meal == -2)
		return (1);
	while (i < list->status->philo_count)
	{
		if (!(list + i)->mutex_right || !(list + i)->mutex_left)
			return (1);
		i++;
	}
	return (0);
}
