/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 10:04:34 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/11 09:19:11 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	check_validity(t_philo *list)
{
	int	i;

	i = 0;
	if (!g_printing)
		return (1);
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
