#include "philo_one.h"

t_philo *init_philosopher(char **av, int ac)
{
	t_philo			*list;
	t_status		*status;
	pthread_mutex_t	*fork_table;
	int				i;

	errno = 0;
	if (!(list = malloc(sizeof(t_philo) * ft_atoi(av[1]))))
		return (NULL);
	if ((!(status = malloc(sizeof(t_status)))))
		return (NULL);
	if (!(fork_table = init_mutex_table(ft_atoi(av[1]))))
		return (NULL);
	i = 0;
	status->simu_state = 0;
	status->count_meal = ac == 6 ? ft_atoi(av[5]) : -1;
	while (i < ft_atoi(av[1]))
	{
		(list + i)->mutex_right = fork_table + i;
		(list + i)->mutex_left = i + 1 == ft_atoi(av[1]) ? fork_table : fork_table + i + 1;
		create_philosopher(list + i, i + 1, av, status);
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		i++;
	}
	return (list);
}

void	take_a_fork(t_philo *philo, char c)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	if (c == 'r')
		pthread_mutex_lock(philo->mutex_right);
	else
		pthread_mutex_lock(philo->mutex_left);
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	if (c == 'r')
		print_state(time, philo->number, " has taken a fork ", (unsigned long)philo->mutex_right);
	else
		print_state(time, philo->number, " has taken a fork ", (unsigned long)philo->mutex_left);
}

void		*philosopher_loop(void *philo)
{
	t_philo *philosopher;

	philosopher = philo;
	while (philosopher->state != 3 && !philosopher->status->simu_state)
	{
		if (philosopher->state == 4 || philosopher->state == 2)
		{
			philosopher->state = 0;
			philosopher_thinking(philosopher);
		}
		else if (philosopher->state == 4 || philosopher->state == 0)
		{
			philosopher->state = 1;
			philosopher_eating(philosopher);
		}
		else if (philosopher->state == 1)
		{
			pthread_mutex_unlock(philosopher->mutex_right);
			pthread_mutex_unlock(philosopher->mutex_left);
			philosopher->state = 2;
			philosopher_sleeping(philosopher);
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