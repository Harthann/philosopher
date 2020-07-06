#include "philo_one.h"

t_philo *init_philosopher(char **av, int ac)
{
	t_philo			*list;
	t_status		*status;
	char				*fork_table;
	pthread_mutex_t	*mutex_table;
	int				i;

	i = 0;
	if (!(list = malloc(sizeof(t_philo) * ft_atoi(av[1]))))
		return (NULL);
	if ((!(status = malloc(sizeof(t_status)))))
		return (NULL);
	if (!(mutex_table = init_mutex_table(ft_atoi(av[1]), &fork_table)))
		return (NULL);
	if (!(status->philo_state = malloc(sizeof(int) * ft_atoi(av[1]))))
		return (NULL);
	status->philo_count = ft_atoi(av[1]);
	status->list = list;
	memset(status->philo_state, 4, status->philo_count);
	status->simu_state = 0;
	status->count_meal = ac == 6 ? ft_atoi(av[5]) : -1;
	if (!(status->last_meal = malloc(sizeof(struct timeval) * status->philo_count)))
		return (NULL);
	while (i < status->philo_count)
	{
		(list + i)->mutex_right = mutex_table + i;
		(list + i)->fork_right = fork_table + i;
		(list + i)->mutex_left = i + 1 == ft_atoi(av[1]) ? mutex_table : mutex_table + i + 1;
		(list + i)->fork_left = i + 1 == ft_atoi(av[1]) ? fork_table : fork_table + i + 1;
		create_philosopher(list + i, i + 1, av, status);
		i++;
	}
	return (list);
}

// void	take_a_fork(t_philo *philo, char c)
// {
// 	long			time;
// 	struct timeval	start_t;
// 	struct timezone tzp;

// 	if (c == 'r')
// 		pthread_mutex_lock(philo->mutex_right);
// 	else
// 		pthread_mutex_lock(philo->mutex_left);
// 	gettimeofday(&start_t, &tzp);
// 	time = compare_time(start_t, philo->timestamp);
// 	if (c == 'r')
// 		print_state(time, philo->number, " has taken a fork \n", (unsigned long)philo->mutex_right);
// 	else
// 		print_state(time, philo->number, " has taken a fork \n", (unsigned long)philo->mutex_left);
// }

// /*
void	take_a_fork(t_philo *philo, char c)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	if (c == 'l' && !mutex_lock(philo->mutex_left, philo->fork_left, philo))
	{
		print_state(time, philo->number, " has taken a fork \n", (unsigned long)philo->mutex_left);
		// print_state(999, philo->mutex_left->__sig, " error check\n", 0);
	}
	else if (!mutex_lock(philo->mutex_right, philo->fork_right, philo))
	{
		print_state(time, philo->number, " has taken a fork \n", (unsigned long)philo->mutex_right);
		// print_state(999, philo->mutex_right->__sig, " error check\n", 0);
	}
	c = 1;
}
// */

void		*philosopher_loop(void *philosopher)
{
	t_philo *philo;

	philo = philosopher;
	while (philo->state != 3 && !philo->status->simu_state)
	{
		if (philo->state == 2 || philo->state == 4)
		{
			philo->state = 0;
			// print_state(999, philo->number - 1, " error check\n", 0);
			philo->status->philo_state[philo->number - 1] = philo->state;
			philosopher_thinking(philo);
		}
		else if (philo->state == 0)
		{
			philo->state = 1;
			philo->status->philo_state[philo->number - 1] = philo->state;
			philosopher_eating(philo);
		}
		else if (philo->state == 1)
		{
			mutex_unlock(philo->mutex_right, philo->fork_right);
			mutex_unlock(philo->mutex_left, philo->fork_left);
			philo->state = 2;
			philo->status->philo_state[philo->number - 1] = philo->state;
			philosopher_sleeping(philo);
		}
	}
	return (NULL);
}

int		main_simu(t_philo *list, int nb)
{
	pthread_t	*thread_list;
	int			i;

	if (!(thread_list = malloc(sizeof(pthread_t) * nb)))
		return (0);
	i = 0;
	while (i < nb)
	{
		pthread_create(&thread_list[i], NULL, philosopher_loop, (void*)(list + i));
		usleep(200);
		i++;
	}
	while (i >= 0)
	{
		pthread_join(thread_list[i], NULL);
		i--;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_philo *list;

	if (ac != 5 && ac != 6)
		return (1);
	if (!(list = init_philosopher(av, ac)))
	{
		write(1, "initialisation failed!\n", 24);
		return (1);
	}
	main_simu(list, ft_atoi(av[1]));
	ft_free(list, ft_atoi(av[1]));
	return (0);
}