/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:45:55 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/11 11:30:11 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	create_philosopher(t_philo *philo, int number, char **av
						, t_status *status)
{
	struct timezone	tzp;

	philo->ttd = ft_atoi(av[2]);
	philo->tte = ft_atoi(av[3]);
	philo->tts = ft_atoi(av[4]);
	philo->number = number;
	philo->status = status;
	gettimeofday(&philo->timestamp, &tzp);
	philo->last_meal = philo->timestamp;
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
	sem_unlink("/my_semafork");
	status->semafork = sem_open("/my_semafork", O_CREAT, 0644, count);
	return (status);
}

t_philo	*init_philosopher(char **av, int ac)
{
	t_philo			*list;
	t_status		*status;
	int				i;

	i = 0;
	list = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	status = init_status(ft_atoi(av[1]));
	sem_unlink("/my_semaprint");
	g_semaprint = sem_open("/my_semaprint", O_CREAT, 0644, 1);
	while (list && i < status->philo_count)
	{
		if (ac == 6 && ft_atoi(av[5]) >= 0)
			(list + i)->count_meal = ft_atoi(av[5]);
		else if (ac == 6)
			(list + i)->count_meal = -2;
		else
			(list + i)->count_meal = -1;
		create_philosopher(list + i, i + 1, av, status);
		i++;
	}
	return (list);
}
