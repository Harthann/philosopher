#include "philo_two.h"

t_philo *init_philosopher(char **av, int ac)
{
	t_philo *list;
	t_fork	*forks;
	sem_t	*tm;
	int		i;

	errno = 0;
	if (!(list = malloc(sizeof(t_philo) * ft_atoi(av[1]))))
		return (NULL);
	if ((!(forks = malloc(sizeof(t_fork)))))
		return (NULL);
	i = 0;
	if (SEM_FAILED == (tm = sem_open("/my_fork", O_CREAT, 0644, 0)))
		return (NULL);
	forks->simu_state = 0;
	forks->count_meal = ac == 6 ? ft_atoi(av[5]) : -1;
	while (i < ft_atoi(av[1]))
	{
		create_philosopher(list + i, i + 1, av, forks);
		// if (i % 2 == 0)
			sem_post(tm);
		i++;
	}
	return (list);
}

void	take_a_fork(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	sem_wait(philo->sem_fork);
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " has taken a fork\n");
}

void		*philosopher_loop(void *philo)
{
	t_philo *philosopher;

	philosopher = philo;
	if (SEM_FAILED == (philosopher->sem_fork = sem_open("/my_fork", 0)))
		return ((void*)-1);
	while (philosopher->state != 3 && !philosopher->forks->simu_state)
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
			sem_post(philosopher->sem_fork);
			sem_post(philosopher->sem_fork);
			philosopher->state = 2;
			philosopher_sleeping(philosopher);
		}
	}
	sem_unlink("my_fork");
	sem_close(philosopher->sem_fork);
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
	// sem_unlink("my_fork");
	// sem_close(list->sem_fork);
	return (0);
}

int		main(int ac, char **av)
{
	t_philo *list;

	if (ac != 5 && ac != 6)
		return (1);
	if (!(list = init_philosopher(av, ac)))
		return (1);
	main_simu(list, ft_atoi(av[1]));
	ft_free(list, ft_atoi(av[1]));
	return (0);
}