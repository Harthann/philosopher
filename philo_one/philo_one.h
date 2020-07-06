#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

/*
** Simu state : 0 = running, 1 : ended;
*/
/*######################################################*/
/*######################################################*/
/*####				PROGRAM PARAMS					####*/
/*####				Number of philosoph				####*/
/*####				Time to die						####*/
/*####				Time to eat						####*/
/*####				Time to sleep					####*/
/*####				Number of meal (Optional)		####*/
/*######################################################*/
/*######################################################*/

typedef struct s_status
{
	int				simu_state;
	int				count_meal;
	struct timeval	*last_meal;
	int				*philo_state;
	int				philo_count;
	struct s_philo	*list;
}				t_status;

/*
** tts = time to sleep;
** ttd = time to die;
** tte = time to eat;
** state : 0 = think, 1 = eat, 2 = sleep, 3 = dead, 4 = pending
** fork = 0 : fork unlock	fork = 1 : fork lock
*/

typedef struct s_philo
{
	long			ttd;
	long			tte;
	long			tts;
	struct timeval	think_tmst;
	int				number;
	struct timeval	timestamp;
	t_status		*status;
	pthread_mutex_t	*mutex_left;
	char			*fork_right;
	pthread_mutex_t	*mutex_right;
	char			*fork_left;
	char			state;
}				t_philo;

int					ft_atoi(char *str);
void				ft_putnbr(long nb);
char				*ft_ultoa(long int n);
void				take_a_fork(t_philo *philo, char c);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(char *str);
int					ft_count_length(long int n);
long				compare_time(struct timeval	tp, struct timeval start_t);
int					philosopher_eating(t_philo *philo);
int					philosopher_sleeping(t_philo *philo);
int					philosopher_thinking(t_philo *philo);
void				print_state(long timestamp, int number, char *str,unsigned long addr);
void				create_philosopher(t_philo *philo, int number, char **av, t_status *status);
pthread_mutex_t		*init_mutex_table(int length, char **fork_table);
void				ft_free(t_philo *list, int nb);
int 	check_priority(int number, t_philo philo, char c);

int		mutex_unlock(pthread_mutex_t *mutex, char *state);
int		mutex_lock(pthread_mutex_t *mutex, char *state, t_philo *philo);
int		is_alive(t_philo *philo);

char			*ft_ultox(unsigned long int n);

#endif