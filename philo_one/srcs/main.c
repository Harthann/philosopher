/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/23 10:12:27 by nieyraud         ###   ########.fr       */
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
	pthread_mutex_lock(philo->mutex_left);
	if (is_alive(philo))
	{
		gettimeofday(&start_t, &tzp);
		time = compare_time(start_t, philo->timestamp);
		print_state(time, philo->number, " has taken a fork \n");
	}

	pthread_mutex_lock(philo->mutex_right);
	if (is_alive(philo))
	{
		gettimeofday(&start_t, &tzp);
		time = compare_time(start_t, philo->timestamp);
		print_state(time, philo->number, " has taken a fork \n");
	}
}

void		*philosopher_loop(void *philosopher)
{
	t_philo *philo;

	philo = philosopher;
	// if (!(philo->number % 2))
	// 	usleep(60);
	while (!philo->status->simu_state && philo->count_meal)
	{
		if (philo->state == 2)
			philosopher_thinking(philo);
		else if (philo->state == 0)
		{
			if (philosopher_eating(philo))
				break ;
		}
		else if (philo->state == 1 || philo->state == 4)
		{
			pthread_mutex_unlock(philo->mutex_left);
			pthread_mutex_unlock(philo->mutex_right);
			if (philosopher_sleeping(philo))
				break;
		}
	}
	pthread_mutex_unlock(philo->mutex_left);
	pthread_mutex_unlock(philo->mutex_right);
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
// 