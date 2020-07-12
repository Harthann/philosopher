/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/12 08:45:30 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		take_a_fork(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	while (is_alive(philo) && *philo->fork_left && !philo->status->simu_state)
		usleep(50);
	if (is_alive(philo))
	{
		mutex_lock(philo->mutex_left, philo->fork_left, philo);
		print_state(time, philo->number, " has taken a fork \n");
	}
	while (is_alive(philo) && *philo->fork_right && !philo->status->simu_state)
		usleep(50);
	if (is_alive(philo) && !philo->status->simu_state)
	{
		mutex_lock(philo->mutex_right, philo->fork_right, philo);
		print_state(time, philo->number, " has taken a fork \n");
	}
	else
		mutex_unlock(philo->mutex_left, philo->fork_left);
}

void		*philosopher_loop(void *philosopher)
{
	t_philo *philo;

	philo = philosopher;
	while (philo->state != 3 && !philo->status->simu_state)
	{
		if (philo->state == 2 || philo->state == 4)
			philosopher_thinking(philo);
		else if (philo->state == 0)
		{
			if (philosopher_eating(philo))
				return (NULL);
		}
		else if (philo->state == 1)
		{
			mutex_unlock(philo->mutex_right, philo->fork_right);
			mutex_unlock(philo->mutex_left, philo->fork_left);
			philosopher_sleeping(philo);
		}
	}
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
						philosopher_loop, (void*)(list + i));
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
