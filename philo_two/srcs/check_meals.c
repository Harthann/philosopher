/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_meals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 08:45:04 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/08 11:35:38 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		check_meal_count(t_status status)
{
	int	i;

	i = 0;
	while (i < status.philo_count)
	{
		if (status.count_meal[i])
			return (0);
		i++;
	}
	return (1);
}
