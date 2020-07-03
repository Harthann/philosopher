#ifndef PHILO_TWO_H
# define PHILO_TWO_H

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>

/*
** Simu state : 0 = running, 1 : ended;
*/

typedef struct s_fork
{
	int	simu_state;
	int	count_meal;
}				t_fork;

/*
** tts = time to sleep;
** ttd = time to die;
** tte = time to eat;
** state : 0 = think, 1 = eat, 2 = sleep, 3 = dead, 4 = pending
*/

typedef struct s_philo
{
	long			ttd;
	long			tte;
	long			tts;
	int				number;
	struct timeval	last_meal;
	struct timeval	timestamp;
	t_fork			*forks;
	char			state;
	sem_t			*sem_fork;
}				t_philo;

int		ft_atoi(char *str);
void	ft_putnbr(long nb);
char	*ft_ultoa(long int n);
void	take_a_fork(t_philo *philo);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(char *str);
int		ft_count_length(long int n);
long	compare_time(struct timeval	tp, struct timeval start_t);
int		philosopher_eating(t_philo *philo);
int		philosopher_sleeping(t_philo *philo);
int		philosopher_thinking(t_philo *philo);
void	print_state(long timestamp, int number, char *str);
void	create_philosopher(t_philo *philo, int number, char **av, t_fork *forks);
void	ft_free(t_philo *list, int nb);

#endif