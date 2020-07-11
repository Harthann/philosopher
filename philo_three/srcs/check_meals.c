/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_meals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 08:45:04 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/11 08:49:53 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		check_meal_count(t_status status)
{
	int	i;

	i = 0;
	while (i < status.philo_count)
	{
		if (status.simu_state)
			return (0);
		i++;
	}
	return (1);
}
