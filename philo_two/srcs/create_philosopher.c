/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:45:55 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/08 11:35:50 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void				meal_set(int *meals, int value, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		meals[i] = value;
		i++;
	}
}

void				create_philosopher(t_philo *philo, int number,
										char **av, t_status *status)
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

t_status			*init_status(int count, t_philo *list, int ac, char *str)
{
	t_status *status;

	if ((!(status = malloc(sizeof(t_status)))))
		return (NULL);
	status->philo_count = count;
	status->list = list;
	status->simu_state = 0;
	if (!(status->count_meal = malloc(sizeof(int) * count)))
		return (NULL);
	if (ac == 6)
		meal_set(status->count_meal, ft_atoi(str), sizeof(int));
	else
		meal_set(status->count_meal, -1, count);
	if (!(status->last_meal = malloc(sizeof(struct timeval) * count)))
	{
		free(status);
		return (NULL);
	}
	return (status);
}

t_philo				*init_philosopher(char **av, int ac)
{
	t_philo			*list;
	t_status		*status;
	char			*fork_table;
	pthread_mutex_t	*mutex_table;
	int				i;

	i = 0;
	if (!(mutex_table = init_mutex_table(ft_atoi(av[1]), &fork_table)))
		return (NULL);
	if (!(list = malloc(sizeof(t_philo) * ft_atoi(av[1]))))
		return (NULL);
	if (!(status = init_status(ft_atoi(av[1]), list, ac, av[5])))
		return (NULL);
	while (i < status->philo_count)
	{
		(list + i)->mutex_right = mutex_table + i;
		(list + i)->fork_right = fork_table + i;
		(list + i)->mutex_left = mutex_table;
		(list + i)->fork_left = fork_table;
		(list + i)->mutex_left += i + 1 == ft_atoi(av[1]) ? 0 : i + 1;
		(list + i)->fork_left += i + 1 == ft_atoi(av[1]) ? 0 : i + 1;
		create_philosopher(list + i, i + 1, av, status);
		i++;
	}
	return (list);
}
