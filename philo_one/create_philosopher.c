/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:45:55 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/06 08:53:03 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	create_philosopher(t_philo *philo, int number, char **av, t_status *status)
{
	struct timezone tzp;

	philo->ttd = ft_atoi(av[2]);
	philo->tte = ft_atoi(av[3]);
	philo->tts = ft_atoi(av[4]);
	philo->number = number;
	philo->state = 4;
	philo->status = status;
	gettimeofday(&philo->timestamp, &tzp);
	philo->status->last_meal[number - 1] = philo->timestamp;
}

pthread_mutex_t		*init_mutex_table(int length, char **fork_table)
{
	pthread_mutex_t	*mutex_table;
	int				i;

	if (!(mutex_table = malloc(sizeof(pthread_mutex_t) * length)))
		return (NULL);
	if (!(*fork_table = malloc(sizeof(char) * length)))
		return (NULL);
	memset(*fork_table, 0, length);
	i = 0;
	while (i < length)
	{
		if (pthread_mutex_init(mutex_table + i, NULL))
			return (NULL);
		i++;
	}
	return (mutex_table);
}