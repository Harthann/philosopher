/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2020/11/17 16:00:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		take_a_fork(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	sem_wait(philo->status->semafork);
	if (philo->status->simu_state == -1)
		return (1);
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " has taken a fork \n");
	sem_wait(philo->status->semafork);
	if (philo->status->simu_state == -1)
		return (1);
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " has taken a fork \n");
	return (0);
}

void	*philosopher_vitals(void *philosopher)
{
	t_philo			*philo;
	long			time;
	struct timeval	start_t;
	struct timezone	tzp;
	int				i;

	philo = (t_philo*)philosopher;
	i = 0;
	while (philo->status->simu_state != -1)
	{
		gettimeofday(&start_t, &tzp);
		time = compare_time(start_t, philo->last_meal);
		if (time > philo->ttd)
		{
			print_state(compare_time(start_t, philo->timestamp),
									philo->number, " died\n");
			sem_wait(g_semaprint);
			philo->status->simu_state = -1;
			while (i++ < philo->status->philo_count)
				sem_post(philo->status->finished_meal);
			exit(0);
		}
		usleep(philo->ttd);
	}
	return (0);
}

void	child_killer(pid_t *pid_list, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		kill(pid_list[i], SIGQUIT);
		i++;
	}
	free(pid_list);
}

int		main_simu(t_philo *list, int nb)
{
	int			i;
	pid_t		*pid_list;
	int			status;

	status = 0;
	if (!(pid_list = malloc(sizeof(pid_t) * nb)))
		return (0);
	i = 0;
	while (i < nb)
	{
		if (!(pid_list[i] = fork()))
			return (philosopher_loop(list + i));
		i++;
	}
	i = 0;
	while (i != nb)
	{
		sem_wait(list->status->finished_meal);
		i++;
	}
	child_killer(pid_list, nb);
	return (0);
}

int		main(int ac, char **av)
{
	t_philo *list;

	if (ac != 5 && ac != 6)
		return (1);
	if (!(list = init_philosopher(av, ac)) || check_validity(list))
	{
		write(1, "initialisation failed!\n", 24);
		return (1);
	}
	main_simu(list, ft_atoi(av[1]));
	ft_free(list);
	return (0);
}
