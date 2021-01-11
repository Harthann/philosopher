/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:45:55 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/11 15:03:57 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	set_forks(t_philo *philo, pthread_mutex_t *mutex_table, int i)
{
	if (mutex_table && philo)
	{
		philo->mutex_right = mutex_table + i;
		philo->mutex_left = mutex_table;
		if (i + 1 != philo->status->philo_count)
			philo->mutex_left += (i + 1);
	}
}

void	create_philosopher(t_philo *philo, int number
							, char **av, t_status *status)
{
	struct timezone	tzp;

	philo->ttd = ft_atoi(av[2]);
	philo->tte = ft_atoi(av[3]);
	philo->tts = ft_atoi(av[4]);
	philo->number = number;
	philo->status = status;
	pthread_mutex_init(&philo->action, NULL);
	gettimeofday(&philo->timestamp, &tzp);
	philo->last_meal = philo->timestamp;
}

pthread_mutex_t	*init_mutex_table(int length)
{
	pthread_mutex_t	*mutex_table;
	int				i;

	mutex_table = malloc(sizeof(pthread_mutex_t) * length);
	if (!mutex_table)
		return (NULL);
	i = 0;
	while (i < length)
	{
		if (pthread_mutex_init(mutex_table + i, NULL))
			return (NULL);
		i++;
	}
	return (mutex_table);
}

t_status	*init_status(int count)
{
	t_status	*status;

	if (count <= 0)
		return (NULL);
	status = malloc(sizeof(t_status));
	if (!status)
		return (NULL);
	status->philo_count = count;
	status->simu_state = 0;
	status->started = 0;
	return (status);
}

t_philo	*init_philosopher(char **av, int ac)
{
	t_philo			*list;
	t_status		*status;
	pthread_mutex_t	*mutex_table;
	int				i;

	i = 0;
	mutex_table = init_mutex_table(ft_atoi(av[1]));
	list = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	status = init_status(ft_atoi(av[1]));
	g_printing = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(g_printing, NULL);
	while (list && i < status->philo_count)
	{
		if (ac == 6 && ft_atoi(av[5]) >= 0)
			(list + i)->count_meal = ft_atoi(av[5]);
		else if (ac == 6)
			(list + i)->count_meal = -2;
		else
			(list + i)->count_meal = -1;
		create_philosopher(list + i, i + 1, av, status);
		set_forks(list + i, mutex_table, i);
		i++;
	}
	return (list);
}
