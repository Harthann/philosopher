/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 08:45:04 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/06 10:15:07 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int 	check_priority(int number, t_philo philo, char c)
{
	struct timezone tzp;
	struct timeval	start_t;
	long			last_meal_one;
	long			last_meal_two;

	gettimeofday(&start_t, &tzp);
	last_meal_one = compare_time(start_t, philo.status->last_meal[number]);
	// print_state(999, number, " error check\n", 0);
	if ((number + 1) % 2 == 1)
		return (1);
	if (c == 'r')
	{
		if (number == 0)
			number = philo.status->philo_count;
			last_meal_two = compare_time(start_t, philo.status->last_meal[number - 1]);
		if (last_meal_one > last_meal_two ||
			compare_time(philo.status->list[number - 1].think_tmst, philo.think_tmst) > 0)
			return (1);
	}
	else
	{
		if (number == philo.status->philo_count)
			number = -1;
		last_meal_two = compare_time(start_t, philo.status->last_meal[number + 1]);
		if (last_meal_one >= last_meal_two ||
			compare_time(philo.status->list[number + 1].think_tmst, philo.think_tmst) > 0)
			return (1);
	}
	return (0);
}