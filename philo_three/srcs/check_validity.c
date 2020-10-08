/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 10:04:34 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/05 11:06:56 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		check_validity(t_philo *list)
{
	int i;

	i = 0;
	if (!list || !list->status || list->ttd < 0
		|| list->tte < 0 || list->tts < 0)
		return (1);
	if (list->count_meal == -2
		|| g_semafork == SEM_FAILED
		|| g_semaprint == SEM_FAILED)
		return (1);
	return (0);
}
