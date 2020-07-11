/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/11 10:09:50 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		take_a_fork(t_philo *philo)
{
	if (is_alive(philo) && !philo->status->simu_state)
		fork_dec(philo->semafork, &philo->status->fork_count, philo);
	while (philo->status->philo_count <= 1 && is_alive(philo)
			&& !philo->status->simu_state)
		usleep(50);
	if (is_alive(philo) && !philo->status->simu_state)
		fork_dec(philo->semafork, &philo->status->fork_count, philo);
	else
		fork_inc(philo->semafork, &philo->status->fork_count);
}

void		*philosopher_loop(void *philosopher)
{
	t_philo *philo;

	philo = philosopher;
	sem_post(philo->semafork);
	while (philo->state != 3 && !philo->status->simu_state)
	{
		if (philo->state == 2 || philo->state == 4)
			philosopher_thinking(philo);
		else if (philo->state == 0)
		{
			if (philosopher_eating(philo) == 1)
				return (NULL);
		}
		else if (philo->state == 1)
		{
			fork_inc(philo->semafork, &philo->status->fork_count);
			fork_inc(philo->semafork, &philo->status->fork_count);
			philosopher_sleeping(philo);
		}
	}
	return (NULL);
}

void		*fork_launcher(void *philosopher)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		return (philosopher_loop(philosopher));
	else
		waitpid(pid, &status, 0);
	return (NULL);
}

int			main_simu(t_philo *list, int nb)
{
	pthread_t	*thread_list;
	int			i;

	if (!(thread_list = malloc(sizeof(pthread_t) * nb)))
		return (0);
	i = 0;
	while (i < nb)
	{
		pthread_create(&thread_list[i], NULL,
						fork_launcher, (void*)(list + i));
		i++;
	}
	while (i >= 0)
	{
		pthread_join(thread_list[i], NULL);
		i--;
	}
	free(thread_list);
	return (0);
}

int			main(int ac, char **av)
{
	t_philo *list;
	int		ret;

	if (ac != 5 && ac != 6)
		return (1);
	ret = 0;
	if (!(list = init_philosopher(av, ac)) || check_validity(list))
	{
		write(1, "initialisation failed!\n", 24);
		ft_free(list);
		return (1);
	}
	ret = main_simu(list, ft_atoi(av[1]));
	ft_free(list);
	return (ret);
}
