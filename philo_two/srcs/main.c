/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/16 08:27:37 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	argument_validity(int ac, char **av)
{
	int	ret;

	ret = 0;
	if (ft_atoi(av[1]) <= 1)
		ret += write(2, "Not enough philosopher to start simulation\n", 44);
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		ret += write(2, "Times can't be negative or equal to zero\n", 41);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		ret += write(2,
				"Philosophers can't eat a negative number of meal\n", 49);
	return (ret);
}

int	main_simu(t_philo *list, int nb)
{
	pthread_t	*thread_list;
	int			i;

	thread_list = malloc(sizeof(pthread_t) * (2 * nb));
	if (!thread_list)
		return (0);
	i = 0;
	while (i < nb)
	{
		pthread_create(&thread_list[i], NULL,
						philosopher_nurse, (void*)(list + i));
		pthread_create(&thread_list[i + nb], NULL,
						philosopher_loop, (void*)(list + i));
		i++;
	}
	list->status->started = 1;
	while (list->status->simu_state != -1 && list->status->simu_state != nb)
		;
	free(thread_list);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*list;

	if (ac != 5 && ac != 6)
		return (0);
	if (argument_validity(ac, av))
		return (0);
	list = init_philosopher(av, ac);
	if (!list || check_validity(list))
	{
		write(1, "initialisation failed!\n", 24);
		return (1);
	}
	main_simu(list, ft_atoi(av[1]));
	ft_free(list);
	return (0);
}
